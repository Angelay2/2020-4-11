#include <stdio.h>
#include <unistd.h>
#include <string.h>
// 保存的是字符的ASCII码值
#include <ctype.h>
#include <sys/

char g_command[1024];

int GetCommand(){
    // 字符数组
    // 第一步: 清空字符数组, sizeof是计算占用内存大小的
    memset(g_command, '\0', sizeof(g_command));
    printf("[test@localhost minishell]$ ");
    fflush(stdout);
    // 从标准输入读取一行数据 放到字符数组中
    // gets(), 有bug, 不会控制到底读多少字节, 全部读取, 可能会造成内存越界
    // 如果读的大小为sizeof(g_command), 比如后面用printf()访问字符串的时候, 可能会越界, C语言中判读字符串到末尾的标志是'\0'
    // -1的目的是为了预留'\0'的位置, 防止越界
    if(fgets(g_command, sizeof(g_command) - 1, stdin) == NULL){
        printf("fgets error!\n");
        return -1;
    }
    
    return 0;
}

int ExecCommand(char* argv[]){
    if(argv[0] == NULL){
        printf("ExecCommand pram error!\n");
        return -1;
    }
    pid_t pid = fork();
    if(pid < 0){
        printf("create subprocess failed!\n");
        return -1;
    }
    else if(pid == 0){
        //child
        // argv[0]为替换的可执行程序, argv为命令行参数
        execvp(argv[0], argv);
        // 需要注意万一替换失败了, 一定要杀掉这个子进程 否则 他也会去getpid()
        exit(0);
    }
    else{
        //father
        waitpid(pid, NULL, 0)
    }
    return 0;

}
int DealCommand(char* command){
    // 差错控制, 若传入NULL(排除无效参数)
    // 工厂当中程序员对于差错处理时非常看重的
    if(!command || *command == '\0'){
        printf("command error!\n");
        return -1;
    }

    // 拆分命令
    // 1. 需要保存命令行参数
    int argc = 0; // 命令行参数个数 argv的下标, 0号下标就是他的可执行程序名称
    char* argv[1024] = {0};
    // 遍历字符串
    while(*command){
        // 不是空白字符 且不为0
        if(!isspace(*command) && *command != '\0'){
           argv[argc] = command;
           argc++;
           
            // 把空白字符用'\0'替换,argc[0] = ls\0-l
           while(!isspace(*command) && *command != '\0'){
                command++;
           }
           *command = '\0';
        }
        command++;
    }
    argv[argc] = NULL;
    
    for(int i = 0; i < argc; i++){
        printf("argv[%d] = %s\n", i, argv[i]);
    }
    // 创建子进程程序替换
    ExecCommand(argv);
    return 0;
}
int main(){
    while(1){
    // 从标准输入当中读取命令
    //
        if(GetCommand() == -1){
            // 需要循环读
            continue;
        }
        // 拆分字符串, 创建子进程, 子进程程序替换
        DealCommand(g_command);
    }
    return 0;
}
