#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sigcb(int signo){
    printf("signo = %d\n", signo);

    for(int i = 0; i < 4; i++){
        printf("print %d\n", i);
        sleep(1);
    }
}
int main(){
    // 自定义信号的处理函数
    signal(SIGINT, sigcb);
    signal(SIGKILL, sigcb);
    signal(20, sigcb);
    signal(19, sigcb);
    signal(2, sigcb);
    signal(3, sigcb);

    while(1){
        printf("study signal\n");
        sleep(1);
    }
    return 0;
}
