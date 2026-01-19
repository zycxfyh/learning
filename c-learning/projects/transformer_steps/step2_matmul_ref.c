#include <stdio.h>
#include <stdlib.h>

struct Tensor {
    float* data;
    int rows;
    int cols;
};

// 工具函数：创建 Tensor
struct Tensor* create_tensor(int r, int c) {
    struct Tensor* t = (struct Tensor*)malloc(sizeof(struct Tensor));
    t->rows = r;
    t->cols = c;
    t->data = (float*)malloc(r * c * sizeof(float));
    // 初始化为 0
    for(int i = 0; i < r * c; i++) t->data[i] = 0.0f;
    return t;
}

// [核心实现] 矩阵乘法：C = A * B
// A 是左矩阵, B 是右矩阵, C 是结果矩阵
void matmul(struct Tensor* A, struct Tensor* B, struct Tensor* C) {
    // 1. 提取维度信息
    int M = A->rows; // A 的行数：决定了结果矩阵 C 有多少行
    int K = A->cols; // A 的列数（必须等于 B 的行数）：这是内积相乘的长度
    int N = B->cols; // B 的列数：决定了结果矩阵 C 有多少列

    // 2. 开始三重循环（这是矩阵乘法的标准姿势）
    
    // 第一层：i 循环 —— 负责定位 A 矩阵的每一行
    for (int i = 0; i < M; i++) {
        
        // 第二层：j 循环 —— 负责定位 B 矩阵的每一列
        for (int j = 0; j < N; j++) {
            
            // 我们现在的目标是计算结果矩阵第 i 行、第 j 列的那个数字
            float sum = 0.0f; // 准备一个累加器，先把这格的初始值设为 0
            
            // 第三层：k 循环 —— 负责“手拉手”做乘法
            // k 就像一个步兵，在 A 的第 i 行横向跑，同时在 B 的第 j 列纵向跑
            for (int k = 0; k < K; k++) {
                
                // 【关键点】计算 A 矩阵的当前的数字：行号 i，列号 k
                // 公式：行号 * 总列数 + 当前列号
                float valA = A->data[i * K + k]; 
                
                // 【关键点】计算 B 矩阵的当前的数字：行号 k，列号 j
                float valB = B->data[k * N + j];
                
                // 把对应的数字相乘，并加到累加器里
                sum += valA * valB;
            }
            
            // 三重循环跑完后，我们就得到了 C[i][j] 的最终结果
            // 把这个算好的 sum 存进结果矩阵 C 的对应位置
            C->data[i * N + j] = sum;
        }
    }
}

int main() {
    // 创建两个简单的矩阵
    // A [2x3]: 1 2 3
    //          4 5 6
    struct Tensor* A = create_tensor(2, 3);
    A->data[0]=1; A->data[1]=2; A->data[2]=3;
    A->data[3]=4; A->data[4]=5; A->data[5]=6;

    // B [3x2]: 7 8
    //          9 10
    //          11 12
    struct Tensor* B = create_tensor(3, 2);
    B->data[0]=7; B->data[1]=8;
    B->data[2]=9; B->data[3]=10;
    B->data[4]=11; B->data[5]=12;

    // C [2x2] 用于存放结果
    struct Tensor* C = create_tensor(2, 2);

    matmul(A, B, C);

    printf("--- [参考代码] MatMul 计算结果 ---\n");
    for(int i = 0; i < C->rows; i++) {
        for(int j = 0; j < C->cols; j++) {
            printf("%.1f ", C->data[i * C->cols + j]);
        }
        printf("\n");
    }

    return 0;
}
