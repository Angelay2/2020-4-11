#include <stdio.h>
#include <unistd.h>

// 三中方式获取环境变量

// 1. main函数的参数获取环境变量
#if 0
int main(int argc, char* argv[], char* env[]){
    // argc --> 命令行参数个数
    // argv --> 命令行参数具体内容
    // env --> 环境变量
    
    //  如何获取命令行参数
    for(int i = 0; i < argc; i++){
        printf("%s\n", argv[i]);
    }

    // 如何获取环境变量参数
    for(int i = 0; env[i]; i++){
        printf("%s\n", env[i]);
    }
    return 0;
}
#endif

// 第二种方法 (libc库中提供的变量来获取)
#if 0
int main(){

    // environ这个变量是在libc库中维护的, 直接可以拿来用 像env[]一样 最后一个元素也是以NULL结尾
    extern char** environ;
    for(int i = 0; environ[i]; i++){

        printf("%s\n", environ[i]);
    }
    return 0;
}
#endif 


// 第三种方式(使用libc库中提供的函数来获取某一个具体的环境变量的值)
#include <stdlib.h>

int main(){
    
    // getenv库函数(在3号手册)
    // char* getenv(const char* name);
    //      name: 环境变量的名称
    //      返回值: 具体环境变量所对应的值
     char* PATH = getenv("PATH");
     // 打印PATH
     printf("PATH=%s\n", PATH);
    return 0;
}
