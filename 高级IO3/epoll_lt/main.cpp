/*================================================================
*   
*   文件名称：main.cpp
*   创 建 者：Angela
*   创建日期：2020年07月30日
*   描    述：
*
================================================================*/

#include "EpollSvr.hpp"

#define CHECK_RET(p) if(p != true){return -1;}
int main(){
    // 创建tcp类对象
    TcpSvr listen_ts;
    CHECK(listen_ts.CreateSocket());
    CKECK(listen_ts.Bind("0.0.0.0", 19999));
    CHECK(listen_ts.listen());
    // 让epoll监控 先不直接调用Accept, 没有新连接到来是 会阻塞
    EpollSvr es;
    CHECK_RET(es.InitSvr());
    es.Addfd(listen_ts.Getfd());

    while(1){
        // 监控到了, 就是由事件产生的 再去接收
        std.vector<TcpSvr> vec;// 所有元素都是就绪的
        es.EpollWait(&vec);// 如果返回不是false, 则去判断这个文件描述符是谁
        if(!es.EpollWait(&vec)){
            continue;
        }
        // 
        for(size_t i = 0; i < vec.size(); i++){
            // 区分一下文件描述符是否是侦听套接字. 对比vec中的Sockfd, 如果不是就是新创建出来的
            if(vec[i].Getfd() == listen_ts.Getfd()){
                // 说明是侦听套接字, 则获取新连接
                // 调用accept
                TcpSvr peerts;
                struct sockaddr_in peeraddr;/// 用来接收客户端地址信息
                listen_ts.Accept(&peerts, &peeraddr);
                printf("Have a new connection : [ip] = [%]s, port = [%d]\n", inet_ntoa(peeraddr, sin_addr), ntohs(peeraddr, sin_port));
                // 将新连接对应的文件描述符添加到epoll中
                es.Addfd(peerts.Getfd());//关心这个文件描述符的
            }
            else{
                std::string data;
                bool ret = vec[i].Recv(&data);
                if(!ret){
                    es.DeleteFd(vec[i].Getfd())// epoll对应的事件结构还跑着呢, 关了
                    vec[i].Close();//
                }
                printf("client say: %s\n", data);
            }
        }

    }

    return 0;
}
