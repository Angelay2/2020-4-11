#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main (int argc, char* argv[]){
    extern char** environ;
    printf("我是test可执行程序");
    for(int i = 0; environ[i]; i++){
        printf("%s\n", environ[i]);
        printf("\n");
    }
    printf("我是test可执行程序, 打印完毕环境变量了!\n");
    for(int i = 0; i < argc; i++){
        printf("pram[%d]: %s\n", i, argv[i]);
    }
    sleep(5);
    printf("我是test可执行程序, 打印完毕命令行参数啦\n");
    execl("usr/bin/ls", "ls", "-a", NULL);
    perror("execl");

    printf("hehehehe\n");
    exit(-1);
    return 0;
}
