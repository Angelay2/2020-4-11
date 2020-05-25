#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>


#define shm_key 0x88888888
int main()
{
    int shmid = shmget(shm_key, 1024, IPC_CREAT | 0664); // 如果存在就返回 不存在就创建
    if(shmid < 0)
    {
        perror("shmget");
        return 0;
    }

    void* addr = shmat(shmid, NULL, 0);
    if(!addr)
    {
        perror("shmat");
        return 0;
    }

    while(1)
    {
        printf("readshm read : \"%s\"\n", (char*)addr);// 将void*的addr强转成char*的
        sleep(2);
    }

    //shmdt(addr); // 注掉则意味着不要分离 则关系内存附加的进程还是2
    shmctl(shmid, IPC_RMID, NULL); // 删除掉这段共享内存 其他进程不能再附加, 同时状态为销毁dest状态
    // 但是让进程还活着, 若将进程退出后, 共享内存的信息也就没了
    // 描述共享内存的结构体还存在着, 但是共享内存已经释放
    while(1)
    {
        sleep(1);
    }
    return 0;
}
