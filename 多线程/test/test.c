#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* thread_start(void* arg)
{
    (void)arg;
    while(1)
    {
        printf("i am thrad\n");
        sleep(1);
    }
    return NULL;
}

int main()
{
    pthread_t tid;
    pthread_create(&tid, NULL, thread_start, NULL);
    while(1)
    {
        printf("linux-68\n");
        sleep(1);
    }
    return 0;
}
