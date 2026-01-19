#define _DEFAULT_SOURCE
#define _USE_MATH_DEFINES
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

// TODO: 实现针对每一行的 Softmax
// 提示：为了数值安全，先减去行最大值
void softmax(struct Tensor* t) {
    for (int i = 0; i < t->rows; i++) {
        // 1. 找最大值
        float max_val = t->data[i * t->cols];
        for (int j = 1; j < t->cols; j++) {
            if (t->data[i * t->cols + j] > max_val) {
                max_val = t->data[i * t->cols + j];
            }
        }
        // 2. 计算 exp 并求和
        float sum = 0.0f;
        for (int j = 0; j < t->cols; j++) {
            t->data[i * t->cols + j] = exp(t->data[i * t->cols + j] - max_val);
            sum += t->data[i * t->cols + j];
        }
        // 3. 归一化
        for (int j = 0; j < t->cols; j++) {
            t->data[i * t->cols + j] /= sum;
        }
    }
}

// TODO: 实现 GELU 激活函数
// 公式参见 step3_task.md
void gelu(struct Tensor* t) {
    int size = t->rows * t->cols;
    for (int i = 0; i < size; i++) {
        float x = t->data[i];
        t->data[i] = 0.5 * x * (1 + tanh(sqrt(2 / M_PI) * (x + 0.044715 * x * x * x)));
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
    fflush(stdout);
}

int main() {
    printf("Starting Combat Mission Verification...\n");
    fflush(stdout);
    struct Tensor* t = create_tensor(1, 3);
    t->data[0] = 1.0f;
    t->data[1] = 2.0f;
    t->data[2] = 3.0f;

    print_tensor(t, "Before Softmax");
    softmax(t);
    print_tensor(t, "After Softmax");

    struct Tensor* t2 = create_tensor(1, 3);
    t2->data[0] = -1.0f;
    t2->data[1] = 0.0f;
    t2->data[2] = 1.0f;
    
    gelu(t2);
    print_tensor(t2, "After GELU");

    printf("Verification Finished.\n");
    fflush(stdout);
    return 0;
}
