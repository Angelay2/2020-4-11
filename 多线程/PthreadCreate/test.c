#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

volatile int g_is_quit = 1;

void sigcb(int signum)
{
    g_is_quit = 0;
}

typedef struct thread_info
{
    int thread_num_;
}THREAD_INFO;

void* thread_start(void* arg)
{
    pthread_detach(pthread_self());
    THREAD_INFO* ti = (THREAD_INFO*)arg;
    while(g_is_quit)
    {
        printf("i am thread, %d\n", ti->thread_num_);
        sleep(1);
    }
    // 当线程访问完毕之后，主动释放内存，否则对于主线程并不知道工作线程什么时候使用完
    if(ti->thread_num_ == 0)
    {
        //pthread_exit(NULL);
        pthread_cancel(pthread_self());
    }

    //while(1)
    {
        printf("i am thread linux----, %d\n", ti->thread_num_);
        sleep(1);
    }
    delete ti;
    return NULL;
}

int main()
{
    signal(SIGQUIT, sigcb);

    pthread_t tid[4];
    int i = 0;
    for(i = 0; i < 4; i++)
    {
        THREAD_INFO* ti = new thread_info();
        ti->thread_num_ = i;
        int ret  = pthread_create(&tid[i], NULL, thread_start, (void*)ti);
        if(ret < 0)
        {
            perror("pthread_create");
            return 0;
        }
        //pthread_cancel(tid[i]);
        //???? 这个位置千万不要释放内存，否则在线程入口函数当中访问非法的空间
        //delete ti;
    }


    //for(i = 0; i < 4; i++)
    //{
    //    pthread_join(tid[i], NULL);
    //}

    //1:认为程序退出的扣1    
    //2.认为程序没有退出的扣0
    //pthread_exit(NULL);
    i = 0;
    while(1)
    {
        printf("heheheheh, %p\n", tid[i % 4]);
        i++;
        usleep(1000000);
    }
    return 0;
}
