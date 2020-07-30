/*================================================================
*   
*   文件名称：EpollSvr.hpp
*   创 建 者：Angela
*   创建日期：2020年07月30日
*   描    述：
*
================================================================*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <vector>
#include "tcp_svr.hpp"
class EpollSvr{
    public:
        EpollSvr(){
            epoll_fd_ = -1;
        }
        ~EpollSvr(){

        }
        bool InitSvr(){
            // 创建操作句柄
            epoll_fd_ = epoll_create(10);
            if(epoll_fd_  == 0) {
                perror("epoll_create!");
                return false;
            }
            return true;
        }
        bool Addfd(){
            // 添加文件描述符
            struct epoll_event ev;
            ev.events = EPOLLIN;
            ev.data.fd = fd;
            int ret = epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, fd, &ev);
            if(ret < 0){
                return false;
            }
            return true;
        }
        bool DeleteFd(){
            // 删除文件描述符
            int ret = epoll_ctl(epoll_fd_, EPOLL_CTL_DEL, fd, NULL);
            if(ret < 0){
                return false;
            }
            return true;
        }
        bool EpollWait(){
            // 定义一事件结构数组
            struct epoll_event fd_arr[10];
            int ret = epoll_wait(epoll_fd_, fd_arr, sizeof(fd_arr)/sizeof(fd_arr[0]), -1);// -1阻塞监控, 如果没有就绪 就一直阻塞等待
            if(ret < 0){
                return false;
            }
            else if(ret == 0){
                // 只有带有超时时间的时候, epoll_wait超过超时时间才会有该返回值, 否则不会有
                return false;
            }
            // 真正监控到了, ret是返回就绪的文件描述符的个数, 
            if(ret > sizeof(fd_arr)/sizeof(fd_arr[0])){
                // 刚才传入的数组全部满了
                ret = sizeof(fd_arr)/sizeof(fd_arr[0]);
            }
            // 传入的数组大小是10, 有可能会存在几种情况
            // 1. 就绪的文件描述符小于数组大小(10), ret = 就绪的文件描述符个数, 按照数组元素来遍历可能会遍历到无效元素, 导致奔溃
            // 2. 就绪的文件描述符个数大于数组大小, 为了防止在使用ret进行遍历的时候,出现访问数组越界导致程序崩溃的问题, 所以我们将数组大小和返回值大小比较
            for(int i = 0; i < ret; i++){
                // 把文件描述符返回给上层使用者
                TcpSvr ts;
                fd_arr[i].data.fd = ;// 如果就绪,就是EPOLLIN事件

            }
        } 

    private:
        int epoll_fd_;// 如果在堆上 就一定要析构释放资源

};
