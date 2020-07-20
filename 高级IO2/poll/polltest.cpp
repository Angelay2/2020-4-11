/*================================================================
*   
*   文件名称：polltest.cpp
*   创 建 者：Angela
*   创建日期：2020年07月20日
*   描    述：
*
================================================================*/

#include <stdio.h>
#include <unistd.h>
#include <poll.h>

int main(){
    struct pollfd fd_arr[10];// 定义事件结构数组
    fd_arr[0].fd = 0;
    fd_arr[0].events = POLLIN;

    while(1){
        int ret = poll(fd_arr, 1, 1000);
        if(ret < 0){
            perror("poll");
            return -1;
        }
        else if(ret == 0){
            printf("poll timeout\n");
            continue;
        }
        // 遍历判断是哪个文件描述符就绪了
        for(int i = 0; i < ret; i++){
            if(fd_arr[i].revents == POLLIN){
                char buf[1024] = {0};
                read(fd_arr[i].fd, buf, sizeof(buf) -1);
                printf("buf: %s\n", buf); 
            }
        }
    }
    return 0;
}
