#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(){
    // flags:
    // O_RDWR: 可读可写方式
    // O_RDONLY: 只读方式打开
    // O_WRONLY: 只写方式打开
    // 以上三个选项是必选其一项
    
    // 以下为可选项 可以选择多个
    // O_CREAT: 如果不存在 则创建文件
    // O_TRUNC: 截断文件, 清空文件
    // O_APPEND: 以追加方式打开文件
    
    int fd = open("./tmp_file", O_RDWR | O_CREAT, 0664);
    if(fd < 0){
        perror("open");
        return 0;
    }
    printf("fd = %d\n", fd);

    int writesize = write(fd, "linux-68", 8);
    if(writesize < 0){
        perror("write");
        return 0;
    }
    printf("writesize = %d\n", writesize);
    
    char buf[1024];
    memset(buf, '\0', sizeof(buf));
    int readsize = read(fd, buf, sizeof(buf - 1));
    if(readsize < 0){
        perror("read");
        return 0;
    }
    printf("readsize = %d\n", readsize);

    int lseek(fd, 0, SEEK_SET);

    close(fd);
    return 0;
}
