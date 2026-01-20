#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 定义栈结构体
struct Stack {
    int* arr;      // 存储数据的数组
    int top;       // 栈顶索引
    int capacity;  // 栈的容量
};

// 函数声明
struct Stack* create_stack(int capacity);
bool is_empty(struct Stack* stack);
bool is_full(struct Stack* stack);
void push(struct Stack* stack, int data);
int pop(struct Stack* stack);
int peek(struct Stack* stack);
void free_stack(struct Stack* stack);

int main() {
    struct Stack* stack = create_stack(5);

    printf("=== C语言栈(stack)演示 ===\n\n");

    printf("1. 入栈操作:\n");
    push(stack, 10);
    printf("入栈: 10\n");
    push(stack, 20);
    printf("入栈: 20\n");
    push(stack, 30);
    printf("入栈: 30\n");

    printf("\n2. 查看栈顶元素: %d\n", peek(stack));

    printf("\n3. 出栈操作:\n");
    while (!is_empty(stack)) {
        printf("出栈: %d\n", pop(stack));
    }

    printf("\n4. 测试栈满的情况:\n");
    push(stack, 100);
    push(stack, 200);
    push(stack, 300);
    push(stack, 400);
    push(stack, 500);
    printf("尝试入栈第6个元素: ");
    push(stack, 600);  // 应该失败

    printf("\n5. 清空栈:\n");
    while (!is_empty(stack)) {
        printf("出栈: %d\n", pop(stack));
    }

    free_stack(stack);
    printf("\n栈已释放\n");

    return 0;
}

// 创建栈
struct Stack* create_stack(int capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    if (stack == NULL) {
        printf("内存分配失败!\n");
        exit(1);
    }

    stack->capacity = capacity;
    stack->top = -1;
    stack->arr = (int*)malloc(capacity * sizeof(int));

    if (stack->arr == NULL) {
        printf("内存分配失败!\n");
        free(stack);
        exit(1);
    }

    return stack;
}

// 检查栈是否为空
bool is_empty(struct Stack* stack) {
    return stack->top == -1;
}

// 检查栈是否已满
bool is_full(struct Stack* stack) {
    return stack->top == stack->capacity - 1;
}

// 入栈操作
void push(struct Stack* stack, int data) {
    if (is_full(stack)) {
        printf("栈已满，无法入栈!\n");
        return;
    }
    stack->arr[++stack->top] = data;
}

// 出栈操作
int pop(struct Stack* stack) {
    if (is_empty(stack)) {
        printf("栈为空，无法出栈!\n");
        return -1;  // 返回错误值
    }
    return stack->arr[stack->top--];
}

// 查看栈顶元素
int peek(struct Stack* stack) {
    if (is_empty(stack)) {
        printf("栈为空!\n");
        return -1;
    }
    return stack->arr[stack->top];
}

// 释放栈内存
void free_stack(struct Stack* stack) {
    free(stack->arr);
    free(stack);
}