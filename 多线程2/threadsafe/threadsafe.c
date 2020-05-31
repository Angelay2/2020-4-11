#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define THREAD_COUNT 4

//用全局变量表示当前还有100张票
int g_tickets = 100;
pthread_mutex_t g_lock;

void* thread_strat(void* arg)
{
    (void)arg;
    while(1)
    {
        //加锁 1
        pthread_mutex_lock(&g_lock);
        if(g_tickets > 0)
        {
            printf("i am thread [%p], i have a ticket number is [%d]\n", pthread_self(), g_tickets);
            //减减操作并非是一个原子操作，这个操作可以被打断
            //1.线程A 100   ->  100-- 被操作系统调度了，线程A的程序计数器当中下一条指令是要减减操作了，线程A的上下文信息当中，寄存器当中保存的待减减的值为100
            //2.线程B 由于线程A并没有完成减减操作，所以内存当中g_tickets的值还是100
            //3.线程B获取到g_tickets之后，进行减减操作，剪完之后将减完的值赋值给g_tickets
            //4.线程A获取CPU资源之后，恢复现场，直接进行减减的时候，从寄存器当中拿出来的值还是100，减完毕之后，g_tickets的值还是99
            g_tickets--;
        }
        else
        {
            pthread_mutex_unlock(&g_lock);
            break;
        }
        pthread_mutex_unlock(&g_lock);
    }
    return NULL;
}

int main()
{
    pthread_mutex_init(&g_lock, NULL);
    pthread_t tid[THREAD_COUNT];
    //1.创建线程
    int i = 0;
    for(; i < THREAD_COUNT; i++)
    {
        int ret = pthread_create(&tid[i], NULL, thread_strat, NULL);
        if(ret < 0)
        {
            perror("pthread_create");
            return 0;
        }
    }
    //2.主线程进行线程等待
    for(i = 0; i < THREAD_COUNT; i++)
    {
        pthread_join(tid[i], NULL);
    }
    pthread_mutex_destroy(&g_lock);
    return 0;
}
