#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[], char* env[]){
    printf("我是myexec可执行程序, 我要开始执行了!\n");
    for(int i = 0; env[i]; i++){
        printf("%s\n", env[i]);
        printf("\n");
    }
    printf("我是myexec可执行程序, 我已经打印完环境变量了\n");
    for(int i = 0; i < argc; i++){
        printf("pram[%d]: %s\n", i, argv[i]);
    }
    printf("我是myexec可执行程序, 我已经打印完毕命令行参数啦\n");
    while(1){
        printf("hello!\n");
        sleep(1);
    }
    return 0;
}
