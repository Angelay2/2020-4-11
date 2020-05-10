#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
    // 0 1 2
    int fd = open("./tmpfile", O_RDWR | O_CREAT, 0664);
    if(fd < 0){
        perror("open");
        return 0;
    }
    printf("fd = %d\n", fd);

    // int dup2(int oldfd, int newfd);
    dup2(3,1);
    printf("hello-linux68\n"); // 本来是输出到标准输出的, 现在输出到了tmpfile
    return 0;

}

