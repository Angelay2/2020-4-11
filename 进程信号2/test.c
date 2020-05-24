#include <stdio.h>
#include <unistd.h>
#include <signal.h>

struct sigaction oldact;

void sigcb(int signo){
    printf("signo = %d\n", signo);
    sigaction(2, &oldact, NULL); // 这里又将信号原来的处理方式给传进去了
}
int main(){
    struct sigaction newact;
    newact.sa_handler = sigcb;// 填充函数地址
    sigemptyset(&newact.sa_mask);// 所有比特位清0
    newact.sa_flags = 0;

    sigaction(2, &newact, &oldact);// 第二次再调用信号时, 就恢复到正常的处理方式了
    while(1){
        printf("linux-68\n");
        sleep(1);
    }

    return 0;
}
