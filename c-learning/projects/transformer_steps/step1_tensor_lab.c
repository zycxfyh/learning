#include <stdio.h>
#include <stdlib.h>

// TODO: 1. 定义一个名为 Tensor 的结构体
// 它应该包含：一个 float 指针 (data)，一个 int (rows)，一个 int (cols)
struct Tensor {
    float* data;
    int rows;
    int cols;
};

// TODO: 2. 实现创建 Tensor 的函数
// 功能：使用 malloc 申请两块内存（结构体本身和数据数组），并返回指针
struct Tensor* create_tensor(int r, int c) {
    struct Tensor* t =(struct Tensor*)malloc(sizeof(struct Tensor));
    t->rows = r;
    t->cols = c;
    t->data = (float*)malloc(r * c * sizeof(float));
    return t;
}

// TODO: 3. 实现释放 Tensor 的函数
// 功能：使用 free 归还内存，注意释放的顺序（先里面，再外面）
void free_tensor(struct Tensor* t) {
    if (t != NULL) {
        if (t->data != NULL) {
            free(t->data);
        }
        free(t);
    }
}

int main() {
    printf("--- [实验室] 开始你的 Tensor 尝试 ---\n");

    // 1. 调用你写好的 create_tensor 造一个 3x3 的矩阵
    struct Tensor* my_tensor = create_tensor(3, 3);
    
    // 2. 打印确认一下，看看 rows 是否真的是 3
    printf("我的张量行数是: %d\n", my_tensor->rows);
    
    // 3. 往第一个格子 (0, 0) 里放一个数字 100.0f
    my_tensor->data[0] = 100.0f;
    printf("成功存入数据: %.1f\n", my_tensor->data[0]);
    
    // 4. 打完收工！调用你的 free_tensor 释放内存
    free_tensor(my_tensor);
    printf("内存回收成功，下班！\n");
    
    return 0;
}