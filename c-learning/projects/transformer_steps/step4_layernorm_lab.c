#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Tensor {
    float* data;
    int rows;
    int cols;
};

struct Tensor* create_tensor(int r, int c) {
    struct Tensor* t = (struct Tensor*)malloc(sizeof(struct Tensor));
    t->rows = r;
    t->cols = c;
    t->data = (float*)malloc(r * c * sizeof(float));
    for(int i = 0; i < r * c; i++) t->data[i] = 0.0f;
    return t;
}

// TODO: 实现针对每一行的 LayerNorm
// 参数：
// t: 需要归一化的数据
// weight: 缩放参数 (gamma), 长度等于 t->cols
// bias: 偏移参数 (beta), 长度等于 t->cols
void layernorm(struct Tensor* t, float* weight, float* bias) {
    float eps = 1e-5f;
    for (int i = 0; i < t->rows; i++) {
        // 指向当前行的指针
        float* row = t->data + i * t->cols;
        
        // 1. 计算均值 (Mean)
        
        // 2. 计算方差 (Variance)
        
        // 3. 归一化并进行缩放偏移
        // Formula: y = ((x - mean) / sqrt(var + eps)) * weight + bias
        
    }
}

void print_tensor(struct Tensor* t, const char* label) {
    printf("--- %s ---\n", label);
    for(int i = 0; i < t->rows; i++) {
        for(int j = 0; j < t->cols; j++) {
            printf("%.4f ", t->data[i * t->cols + j]);
        }
        printf("\n");
    }
}

int main() {
    int dim = 3;
    struct Tensor* t = create_tensor(1, dim);
    t->data[0] = 1.0f;
    t->data[1] = 2.0f;
    t->data[2] = 3.0f;

    float weight[] = {1.0f, 1.0f, 1.0f};
    float bias[] = {0.0f, 0.0f, 0.0f};

    print_tensor(t, "Before LayerNorm");
    layernorm(t, weight, bias);
    print_tensor(t, "After LayerNorm");

    return 0;
}
