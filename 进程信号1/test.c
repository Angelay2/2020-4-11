#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main()
{
    //int kill(pid_t pid, int sig);
    //   pid:想要发送信号给哪一个进程
    //   sig：给进程发送什么信号
    printf("begin~~~~\n");
    //kill(getpid(), 3);
    
    // void abort(void);
    // abort函数，谁调用谁退出
    // abort();
    //
    alarm(3);
    while(1)
    {
        printf("linux-68\n");
        sleep(1);
    }
    printf("end~~~~\n");
    return 0;
}
