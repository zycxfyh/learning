#include <stdio.h>
#include <stdlib.h>

struct Tensor {
    float* data;
    int rows;
    int cols;
};

// 使用你第一步写的代码...
struct Tensor* create_tensor(int r, int c) {
    struct Tensor* t = (struct Tensor*)malloc(sizeof(struct Tensor));
    t->rows = r;
    t->cols = c;
    t->data = (float*)malloc(r * c * sizeof(float));
    for(int i = 0; i < r * c; i++) t->data[i] = 0.0f;
    return t;
}

// TODO: 实现矩阵乘法 C = A * B
void matmul(struct Tensor* A, struct Tensor* B, struct Tensor* C) {
   int M=A->rows;
   int K=A->cols;
   int N=B->cols;
   for(int i=0;i<M;i++){
    for(int j=0;j<N;j++){
        float sum=0.0f;
        for(int k=0;k<K;k++){
            float valA = A->data[i * K + k];
            float valB = B->data[k * N + j];
            sum += valA * valB;
        }
        C->data[i*N+j]=sum;
    }
   }
    // 计算逻辑完成！
}

int main() {
    // 测试逻辑：
    // 1. 创建 A(2,2) 和 B(2,2)
    struct Tensor* A = create_tensor(2, 2);
    struct Tensor* B = create_tensor(2, 2);
    // 2. 给它们填入一些简单的数字
    A->data[0] = 1;
    A->data[1] = 2;
    A->data[2] = 3;
    A->data[3] = 4;
    B->data[0] = 5;
    B->data[1] = 6;
    B->data[2] = 7;
    B->data[3] = 8;
    // 3. 创建 C(2,2) 并调用 matmul
    struct Tensor* C = create_tensor(2, 2);
    matmul(A, B, C);
    for(int i = 0; i < C->rows; i++) {
        for(int j = 0; j < C->cols; j++) {
            printf("%.1f ", C->data[i * C->cols + j]);
        }
        printf("\n");
    }
    return 0;
}
