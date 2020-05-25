#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>


#define shm_key 0x88888888 //标识
int main()
{
    int shmid = shmget(shm_key, 1024, IPC_CREAT | 0664); // 创建
    if(shmid < 0)
    {
        perror("shmget");
        return 0;
    }

    void* addr = shmat(shmid, NULL, 0); // 附加 地址通过返回值得到
    if(!addr)
    {
        perror("shmat");
        return 0;
    }

    int count = 0;
    // 每隔几秒去写一下, 操作地址来往共享区进去写
    while(1)
    {
        snprintf((char*)addr, 1024, "%s-%d", "linux68", count); // 写到共享区, 映射到物理内存 
        count++;
        sleep(2); // 覆盖写
    }

    shmdt(addr);// 分离
    shmctl(shmid, IPC_RMID, NULL);// 删除掉addr
    return 0;
}
