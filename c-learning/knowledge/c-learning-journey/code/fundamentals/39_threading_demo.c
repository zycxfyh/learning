#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// 全局变量用于演示线程同步
int shared_counter = 0;
pthread_mutex_t mutex;
pthread_cond_t condition;

// 线程函数声明
void* simple_thread(void* arg);
void* counter_thread(void* arg);
void* producer_thread(void* arg);
void* consumer_thread(void* arg);

// 生产者-消费者模型的缓冲区
#define BUFFER_SIZE 5
int buffer[BUFFER_SIZE];
int buffer_count = 0;
int producer_idx = 0;
int consumer_idx = 0;

int main() {
    printf("=== C语言多线程编程演示 ===\n\n");

    // 1. 简单线程创建
    printf("1. 简单线程创建演示:\n");
    pthread_t thread1, thread2;

    if (pthread_create(&thread1, NULL, simple_thread, (void*)"Thread A") != 0) {
        perror("线程创建失败");
        return 1;
    }

    if (pthread_create(&thread2, NULL, simple_thread, (void*)"Thread B") != 0) {
        perror("线程创建失败");
        return 1;
    }

    // 等待线程结束
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // 2. 线程同步演示 - 互斥锁
    printf("\n2. 线程同步演示 (互斥锁):\n");

    // 初始化互斥锁
    if (pthread_mutex_init(&mutex, NULL) != 0) {
        perror("互斥锁初始化失败");
        return 1;
    }

    pthread_t counter_threads[3];
    int thread_ids[3] = {1, 2, 3};

    // 创建计数器线程
    for (int i = 0; i < 3; i++) {
        if (pthread_create(&counter_threads[i], NULL, counter_thread,
                          (void*)&thread_ids[i]) != 0) {
            perror("计数器线程创建失败");
            return 1;
        }
    }

    // 等待所有计数器线程结束
    for (int i = 0; i < 3; i++) {
        pthread_join(counter_threads[i], NULL);
    }

    printf("最终计数器值: %d\n", shared_counter);

    // 销毁互斥锁
    pthread_mutex_destroy(&mutex);

    // 3. 生产者-消费者模型 (条件变量)
    printf("\n3. 生产者-消费者模型 (条件变量):\n");

    // 初始化条件变量
    if (pthread_cond_init(&condition, NULL) != 0) {
        perror("条件变量初始化失败");
        return 1;
    }

    // 重新初始化互斥锁
    if (pthread_mutex_init(&mutex, NULL) != 0) {
        perror("互斥锁重新初始化失败");
        return 1;
    }

    pthread_t producer, consumer;

    // 创建生产者和消费者线程
    if (pthread_create(&producer, NULL, producer_thread, NULL) != 0) {
        perror("生产者线程创建失败");
        return 1;
    }

    if (pthread_create(&consumer, NULL, consumer_thread, NULL) != 0) {
        perror("消费者线程创建失败");
        return 1;
    }

    // 等待线程结束
    pthread_join(producer, NULL);
    pthread_join(consumer, NULL);

    // 清理资源
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&condition);

    printf("\n多线程演示完成!\n");
    return 0;
}

// 简单线程函数
void* simple_thread(void* arg) {
    char* thread_name = (char*)arg;
    printf("  %s 已启动\n", thread_name);

    // 模拟一些工作
    sleep(1);

    printf("  %s 已完成\n", thread_name);
    return NULL;
}

// 计数器线程函数 - 演示互斥锁
void* counter_thread(void* arg) {
    int thread_id = *(int*)arg;

    for (int i = 0; i < 5; i++) {
        // 获取互斥锁
        pthread_mutex_lock(&mutex);

        shared_counter++;
        printf("  线程 %d: 计数器 = %d\n", thread_id, shared_counter);

        // 释放互斥锁
        pthread_mutex_unlock(&mutex);

        // 短暂延迟以增加竞争条件出现的可能性
        usleep(10000); // 10毫秒
    }

    return NULL;
}

// 生产者线程函数
void* producer_thread(void* arg) {
    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&mutex);

        // 等待缓冲区有空间
        while (buffer_count == BUFFER_SIZE) {
            printf("  生产者: 缓冲区满，等待...\n");
            pthread_cond_wait(&condition, &mutex);
        }

        // 生产数据
        buffer[producer_idx] = i + 1;
        producer_idx = (producer_idx + 1) % BUFFER_SIZE;
        buffer_count++;

        printf("  生产者: 生产了 %d (缓冲区大小: %d)\n", i + 1, buffer_count);

        // 通知消费者
        pthread_cond_signal(&condition);
        pthread_mutex_unlock(&mutex);

        usleep(50000); // 50毫秒
    }

    return NULL;
}

// 消费者线程函数
void* consumer_thread(void* arg) {
    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&mutex);

        // 等待缓冲区有数据
        while (buffer_count == 0) {
            printf("  消费者: 缓冲区空，等待...\n");
            pthread_cond_wait(&condition, &mutex);
        }

        // 消费数据
        int data = buffer[consumer_idx];
        consumer_idx = (consumer_idx + 1) % BUFFER_SIZE;
        buffer_count--;

        printf("  消费者: 消费了 %d (缓冲区大小: %d)\n", data, buffer_count);

        // 通知生产者
        pthread_cond_signal(&condition);
        pthread_mutex_unlock(&mutex);

        usleep(80000); // 80毫秒
    }

    return NULL;
}