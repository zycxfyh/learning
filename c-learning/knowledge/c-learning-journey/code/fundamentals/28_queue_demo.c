#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 定义队列结构体
struct Queue {
    int* arr;       // 存储数据的数组
    int front;      // 队头索引
    int rear;       // 队尾索引
    int capacity;   // 队列容量
    int size;       // 当前元素个数
};

// 函数声明
struct Queue* create_queue(int capacity);
bool is_empty(struct Queue* queue);
bool is_full(struct Queue* queue);
void enqueue(struct Queue* queue, int data);
int dequeue(struct Queue* queue);
int front(struct Queue* queue);
void free_queue(struct Queue* queue);

int main() {
    struct Queue* queue = create_queue(5);

    printf("=== C语言队列(queue)演示 ===\n\n");

    printf("1. 入队操作:\n");
    enqueue(queue, 10);
    printf("入队: 10\n");
    enqueue(queue, 20);
    printf("入队: 20\n");
    enqueue(queue, 30);
    printf("入队: 30\n");

    printf("\n2. 查看队头元素: %d\n", front(queue));

    printf("\n3. 出队操作:\n");
    while (!is_empty(queue)) {
        printf("出队: %d\n", dequeue(queue));
    }

    printf("\n4. 测试队列满的情况:\n");
    enqueue(queue, 100);
    enqueue(queue, 200);
    enqueue(queue, 300);
    enqueue(queue, 400);
    enqueue(queue, 500);
    printf("尝试入队第6个元素: ");
    enqueue(queue, 600);  // 应该失败

    printf("\n5. 查看当前队列状态:\n");
    printf("队头元素: %d\n", front(queue));
    printf("队列大小: %d\n", queue->size);

    printf("\n6. 出队几个元素:\n");
    printf("出队: %d\n", dequeue(queue));
    printf("出队: %d\n", dequeue(queue));

    printf("\n7. 再次入队:\n");
    enqueue(queue, 700);
    enqueue(queue, 800);

    printf("\n8. 清空队列:\n");
    while (!is_empty(queue)) {
        printf("出队: %d\n", dequeue(queue));
    }

    free_queue(queue);
    printf("\n队列已释放\n");

    return 0;
}

// 创建队列
struct Queue* create_queue(int capacity) {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    if (queue == NULL) {
        printf("内存分配失败!\n");
        exit(1);
    }

    queue->capacity = capacity;
    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
    queue->arr = (int*)malloc(capacity * sizeof(int));

    if (queue->arr == NULL) {
        printf("内存分配失败!\n");
        free(queue);
        exit(1);
    }

    return queue;
}

// 检查队列是否为空
bool is_empty(struct Queue* queue) {
    return queue->size == 0;
}

// 检查队列是否已满
bool is_full(struct Queue* queue) {
    return queue->size == queue->capacity;
}

// 入队操作
void enqueue(struct Queue* queue, int data) {
    if (is_full(queue)) {
        printf("队列已满，无法入队!\n");
        return;
    }

    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->arr[queue->rear] = data;
    queue->size++;
}

// 出队操作
int dequeue(struct Queue* queue) {
    if (is_empty(queue)) {
        printf("队列为空，无法出队!\n");
        return -1;
    }

    int data = queue->arr[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return data;
}

// 查看队头元素
int front(struct Queue* queue) {
    if (is_empty(queue)) {
        printf("队列为空!\n");
        return -1;
    }
    return queue->arr[queue->front];
}

// 释放队列内存
void free_queue(struct Queue* queue) {
    free(queue->arr);
    free(queue);
}