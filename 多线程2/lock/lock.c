#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex1;
pthread_mutex_t mutex2;

void* thread_startA(void* arg)
{
    (void)arg;
    pthread_mutex_lock(&mutex1);
    sleep(2);
    pthread_mutex_lock(&mutex2);

    pthread_mutex_unlock(&mutex2);
    pthread_mutex_unlock(&mutex1);
    return NULL;

}

void* thread_startB(void* arg)
{
    (void)arg;
    pthread_mutex_lock(&mutex2);
    sleep(2);
    pthread_mutex_lock(&mutex1);

    pthread_mutex_unlock(&mutex1);
    pthread_mutex_unlock(&mutex2);
    return NULL;

}


int main()
{
    pthread_mutex_init(&mutex1, NULL);
    pthread_mutex_init(&mutex2, NULL);
    pthread_t tid_a, tid_b;
    int ret = pthread_create(&tid_a, NULL, thread_startA, NULL);
    if(ret < 0)
    {
        perror("pthread_create");
        return 0;

    }

    ret = pthread_create(&tid_b, NULL, thread_startB, NULL);
    if(ret < 0)
    {
        perror("pthread_create");
        return 0;

    }

    pthread_join(tid_a, NULL);
    pthread_join(tid_b, NULL);

    pthread_mutex_destroy(&mutex1);
    pthread_mutex_destroy(&mutex2);
    return 0;

}
