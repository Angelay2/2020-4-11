#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sigcb(int signo){
    printf("signo = %d\n", signo);
}
int main(){
    // 自定义信号的处理函数
    signal(2, sigcb);
    signal(3, sigcb);

    while(1){
        printf("study signal\n");
        sleep(1);
    }
    return 0;
}
