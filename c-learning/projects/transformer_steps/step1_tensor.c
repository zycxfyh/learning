#include <stdio.h>
#include <stdlib.h> // 为了使用 malloc 和 free

// 1. 定义 Tensor (张量) 结构体
// 你可以把它想象成一个“超级 Excel”，不仅可以有行和列，还可以有更多维度
struct Tensor {
    float* data;      // 指向真实数据的指针（内存里的一个连续长条）
    int rows;         // 有多少行
    int cols;         // 有多少列
};

// 2. 一个“工厂函数”，专门用来制造 Tensor
// 我们返回一个指针，这样我们就可以跨函数操作它
struct Tensor* create_tensor(int r, int c) {
    // 为结构体申请内存
    struct Tensor* t = (struct Tensor*)malloc(sizeof(struct Tensor));
    
    t->rows = r;
    t->cols = c;
    
    // 为数据申请内存 (行 * 列 * 每个 float 占的字节数)
    t->data = (float*)malloc(r * c * sizeof(float));
    
    return t;
}

// 3. 销毁 Tensor (环保卫士，还给电脑内存)
void free_tensor(struct Tensor* t) {
    free(t->data);
    free(t);
}

int main() {
    // 制造一个 2 行 3 列的矩阵
    struct Tensor* my_matrix = create_tensor(2, 3);

    // 填充一点示例数据
    // 坐标计算公式：row * cols + col
    my_matrix->data[0 * 3 + 0] = 1.1; // 第一行第一列
    my_matrix->data[1 * 3 + 2] = 9.9; // 第二行第三列

    printf("=== Transformer 第一步：张量容器 ===\n");
    printf("矩阵大小: %d 行, %d 列\n", my_matrix->rows, my_matrix->cols);
    printf("坐标 (1,2) 的值是: %.1f\n", my_matrix->data[1 * 3 + 2]);

    free_tensor(my_matrix);
    return 0;
}
