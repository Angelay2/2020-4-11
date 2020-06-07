#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define THREADCOUNT 2

// 有面则为1
// 没有面则为0
int g_noodle = 0;

pthread_mutex_t g_mutex;
//第二个问题的点
//吃面的人条件变量
pthread_cond_t g_eat;
//做面的人的条件变量
pthread_cond_t g_make;


#if 0
void* Eat_start(void* arg)
{
    (void)arg;
    //吃面
    while(1)
    {
EAT:
        pthread_mutex_lock(&g_mutex);
        if(g_noodle == 0)
        {
            pthread_mutex_unlock(&g_mutex);
            goto EAT;
        }
        g_noodle--;
        printf("eat nondle %d\n", g_noodle);
        pthread_mutex_unlock(&g_mutex);
    }
    return NULL;
}

void* Make_start(void* arg)
{
    (void)arg;
    //做面
    while(1)
    {
MAKE:
        pthread_mutex_lock(&g_mutex);
        if(g_noodle == 1)
        {
            pthread_mutex_unlock(&g_mutex);
            goto MAKE;
        }
        g_noodle++;
        printf("make nondle %d\n", g_noodle);
        pthread_mutex_unlock(&g_mutex);
    }
    return NULL;
}
#endif

void* Eat_start(void* arg)
{
    (void)arg;
    //吃面
    while(1)
    {
        pthread_mutex_lock(&g_mutex);
        while(g_noodle == 0)
        {
            //该接口会阻塞该执行流
            //等待步骤，阻塞在pthread_cond_wait内部的实现逻辑当中
            //  1.将该执行流放到PCB等待队列
            //  2.解锁互斥锁
            //  3.等待被唤醒
            pthread_cond_wait(&g_eat, &g_mutex);
            //当唤醒之后， pthread_cond_wait就返回
            //唤醒之后有两个步骤：
            //  1.从PCB等待队列当中移除
            //  2.竞争互斥锁
        }
        g_noodle--;
        printf("eat nondle %d\n", g_noodle);
        pthread_mutex_unlock(&g_mutex);
        //如果吃完面则通知厨子来做面
        pthread_cond_signal(&g_make);
    }
    return NULL;
}

void* Make_start(void* arg)
{
    (void)arg;
    //做面
    while(1)
    {
        pthread_mutex_lock(&g_mutex);
        //第一个问题的点
        while(g_noodle == 1)
        {
            pthread_cond_wait(&g_make, &g_mutex);
        }
        g_noodle++;
        printf("make nondle %d\n", g_noodle);
        pthread_mutex_unlock(&g_mutex);
        //通知吃面的来进行吃面
        pthread_cond_signal(&g_eat);
    }
    return NULL;
}
int main()
{
    pthread_mutex_init(&g_mutex, NULL);
    pthread_cond_init(&g_eat, NULL);
    pthread_cond_init(&g_make, NULL);
    pthread_t eat_tid[THREADCOUNT], make_tid[THREADCOUNT];

    int i = 0;
    for(; i < THREADCOUNT; i++)
    {
        int ret = pthread_create(&eat_tid[i], NULL, Eat_start, NULL);
        if(ret < 0)
        {
            perror("pthread_create");
            return 0;
        }
        ret = pthread_create(&make_tid[i], NULL, Make_start, NULL);
        if(ret < 0)
        {
            perror("pthread_create");
            return 0;
        }
    }

    for(i = 0; i < THREADCOUNT; i++)
    {
        pthread_join(eat_tid[i], NULL);
        pthread_join(make_tid[i], NULL);
    }
    pthread_mutex_destroy(&g_mutex);
    pthread_cond_destroy(&g_eat);
    pthread_cond_destroy(&g_make);
    return 0;
}
