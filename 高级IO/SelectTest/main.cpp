/*================================================================
*   
*   文件名称：main.cpp
*   创 建 者：Angela
*   创建日期：2020年07月12日
*   描    述：
*           1. 监控0号(标准输入)文件描述符的可读事件
*           2. 当0号文件描述符产生可读事件后
*           3. 处理可读事件
*
*           怎么做?
*           1. 将0号文件描述符添加到可读事件集合中
*           2. 监控
*           3. 判断文件描述符是否还在集合当中
*           4. 处理文件描述符对应的可读事件
*
================================================================*/
#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>

int main(){
    fd_set readfds;
    // 1. 清空
    FD_ZERO(&readfds);
    // 2. 添加
    FD_SET(0, &readfds);

    // 3. 监控
    while(1){
begin:
        struct timeval tv;
        tv.tv_sec = 3;
        tv.tv_usec = 0;
        int ret = select(0 + 1, &readfds, NULL, NULL, &tv);
        if(ret < 0){
            perror("select");
            return 0;
        }
        else if(ret == 0){
            printf("timeout\n");
            // 如果超时了, 意味着0号文件描述符没有就绪, 在select返回的时候,就会从集合中去除掉
            if(FD_ISSET(0, &readfds) == 0){
                printf("0 fd is not in readfds");
            }
            FD_SET(0, &readfds);
            goto begin;
        }
        // ret 大于0
        if(FD_ISSET(0, &readfds) != 0){
            char buf[1024] = {0};
            read(0, buf, sizeof(buf) - 1);
            printf("buf: %s", buf);
        }
    }
    FD_CLR(0, &readfds);
    return 0;
}


