#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(){
    FILE* fp = fopen("tmp.file", "w+");
    if(!fp){
        perror("fopen");
        return 0;
    }
    const char* data = "linux-68";
    ssize_t writesize = fwrite(data, 1, strlen(data), fp); // strlen是算字符串长度, sizeof是计算占用的内存大小
    //ssize_t writesize = fwrite(data, 3, 4, fp); // 读越界了,``
    // 含义是写入了多少个块
    printf("writesize: %lu\n", writesize);

    fseek(fp, 2, SEEK_SET);

    // 使用
   char buf[1024];
   memset(buf, '\0', sizeof(buf));
   //ssize_t readsize = fread(buf, 2, 3, fp);
   //printf("readsize: %lu\n", readsize);
   //printf("readbuf: %s\n", buf);
   
   ssize_t readsize = fread(buf, 1, 8, fp);// 8个块 每个块字节为1
   printf("readsize: %lu\n", readsize); // lu是无符号的
   printf("readbuf: %s\n", buf);

   fclose(fp);
    return 0;
}
