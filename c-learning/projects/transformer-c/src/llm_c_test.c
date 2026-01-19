#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 声明外部 llm.c 算子
void rmsnorm(float* o, float* x, float* weight, int size);
void matmul(float* xout, float* x, float* w, int n, int d);

int main() {
    printf("=== LLM.C 社区标准算子基准测试 ===\n");

    int d = 1024;
    int n = 1024;
    float* x = (float*)malloc(n * sizeof(float));
    float* w = (float*)malloc(d * n * sizeof(float));
    float* out = (float*)malloc(d * sizeof(float));

    for(int i=0; i<n; i++) x[i] = 1.0f;
    for(int i=0; i<d*n; i++) w[i] = 0.01f;

    clock_t start = clock();
    matmul(out, x, w, n, d);
    clock_t end = clock();

    printf("MatMul (%d x %d) 耗时: %.2f ms\n", n, d, (double)(end - start) * 1000.0 / CLOCKS_PER_SEC);
    printf("输出验证 (前 3 位): %.2f %.2f %.2f\n", out[0], out[1], out[2]);

    free(x); free(w); free(out);
    return 0;
}
