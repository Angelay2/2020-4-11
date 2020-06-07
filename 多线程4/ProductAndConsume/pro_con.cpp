#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <iostream>
#include <queue>

#define THREADCOUNT 2

class BlockQueue
{
    public:
        BlockQueue(size_t capacity = 1)
        {
            capacity_ = capacity;
            pthread_mutex_init(&mutex_, NULL);
            pthread_cond_init(&consume_cond_, NULL);
            pthread_cond_init(&product_cond_, NULL);
        }

        ~BlockQueue()
        {
            pthread_mutex_destroy(&mutex_);
            pthread_cond_destroy(&consume_cond_);
            pthread_cond_destroy(&product_cond_);
        }

        //data 是一个出参
        void Pop(int* data)
        {
            pthread_mutex_lock(&mutex_);
            while(que_.empty())
            {
                pthread_cond_wait(&consume_cond_, &mutex_);
            }
            *data = que_.front();
            que_.pop();
            pthread_mutex_unlock(&mutex_);

            pthread_cond_signal(&product_cond_);
        }

        void Push(int& data)
        {
            pthread_mutex_lock(&mutex_);
            while(que_.size() >= capacity_)
            {
                pthread_cond_wait(&product_cond_, &mutex_);
            }
            que_.push(data);
            printf("Product_start [%p]:[%d]\n", pthread_self(), data);
            pthread_mutex_unlock(&mutex_);
            pthread_cond_signal(&consume_cond_);
        }
    private:
        //线程不安全的
        std::queue<int> que_;
        //限制queue的容量
        size_t capacity_;

        //互斥
        pthread_mutex_t mutex_;

        //同步
        pthread_cond_t consume_cond_;
        pthread_cond_t product_cond_;
};


void* Consuem_start(void* arg)
{
    BlockQueue* bq = (BlockQueue*)arg;
    while(1)
    {
        sleep(1);
    }
    while(1)
    {
        int i;
        bq->Pop(&i);

        printf("Consuem_start [%p]:[%d]\n", pthread_self(), i);
    }
    return NULL;
}

int i = 0;
void* Product_start(void* arg)
{
    BlockQueue* bq = (BlockQueue*)arg;
    while(1)
    {
        bq->Push(i);
        i++;
    }
    return NULL;
}

int main()
{
    BlockQueue* bq = new BlockQueue(100);

    pthread_t con_tid[THREADCOUNT], pro_tid[THREADCOUNT];
    int i = 0;
    for(; i < THREADCOUNT; i++)
    {
        int ret = pthread_create(&con_tid[i], NULL, Consuem_start, (void*)bq);
        if(ret < 0)
        {
            perror("pthread_create");
            return 0;
        }

        ret = pthread_create(&pro_tid[i], NULL, Product_start, (void*)bq);
        if(ret < 0)
        {
            perror("pthread_create");
            return 0;
        }
    }

    for(i = 0; i < THREADCOUNT; i++)
    {
        pthread_join(con_tid[i], NULL);
        pthread_join(pro_tid[i], NULL);
    }
    delete bq;
    return 0;
}
