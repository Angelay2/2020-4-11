#include <stdio.h>
#include <unistd.h>

int main(){
    int a = 10;
    int b = 20;
    int c = a + b;
    printf("c = %d\n", c);
    int pid =  fork();// fork调用完毕 意味着会创建出来一个子进程(也会运行下面的代码)
    if(pid < 0){
        perror("fork");
        return 0;
    } 
    else if(pid == 0){
        // child
        printf("i am child %d\n", getpid());
    }
    else{
        // father
        printf("i am father %d\n", getpid());
    }
     while(1){
        sleep(1);
    }
    
    return 0;
}

