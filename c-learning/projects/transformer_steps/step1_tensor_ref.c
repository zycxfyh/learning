#include <stdio.h>
#include <stdlib.h>

// 1. 定义 Tensor 结构体
struct Tensor {
    float* data;      // 存储数据的数组指针
    int rows;         // 行数
    int cols;         // 列数
};

// 2. 创建 Tensor：申请内存
struct Tensor* create_tensor(int r, int c) {
    // 首先为结构体本身申请内存
    struct Tensor* t = (struct Tensor*)malloc(sizeof(struct Tensor));
    t->rows = r;
    t->cols = c;
    
    // 然后为内部的数据数组申请内存
    // 大小 = 行 * 列 * 每一个 float 占用的字节
    t->data = (float*)malloc(r * c * sizeof(float));
    
    return t;
}

// 3. 释放 Tensor：销毁内存
void free_tensor(struct Tensor* t) {
    if (t != NULL) {
        if (t->data != NULL) {
            free(t->data); // 先释放里面的数据
        }
        free(t); // 再释放结构体本身
    }
}

int main() {
    printf("--- [参考代码] Tensor 内存管理 ---\n");
    struct Tensor* my_tensor = create_tensor(2, 2);
    
    my_tensor->data[0] = 1.0f; // 放入数据
    printf("创建成功！首个元素: %.1f\n", my_tensor->data[0]);
    
    free_tensor(my_tensor);
    printf("内存已安全释放。\n");
    
    return 0;
}
