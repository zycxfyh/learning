#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

#ifdef _OPENMP
#include <omp.h>
#endif

// ============================================================================
// 1. 数据结构 (llm.c 扁平化风格)
// ============================================================================

typedef struct {
    int max_seq_len;
    int vocab_size;
    int n_layers;
    int n_heads;
    int n_kv_heads;
    int dim;
    int hidden_dim;
} Config;

typedef struct {
    // 激活值缓存 (全预分配)
    float* x;      // 当前隐藏状态 [dim]
    float* xb;     // 辅助缓存 [dim]
    float* xb2;    // 辅助缓存 2 [dim]
    float* hb;     // FFN 辅助缓存 [hidden_dim]
    float* hb2;    // FFN 辅助缓存 2 [hidden_dim]
    float* q;      // [dim]
    float* k;      // [dim]
    float* v;      // [dim]
    float* att;    // 注意力分数 [n_heads, max_seq_len]
    float* logits; // 输出概率 [vocab_size]
} RunState;

// ============================================================================
// 2. 核心高性能算子 (llm.c 内核)
// ============================================================================

// RMSNorm: 现代 LLM (Llama) 的标准归一化
void rmsnorm(float* o, float* x, float* weight, int size) {
    float ss = 0.0f;
    for (int i = 0; i < size; i++) {
        ss += x[i] * x[i];
    }
    ss /= size;
    ss += 1e-5f;
    ss = 1.0f / sqrtf(ss);
    for (int i = 0; i < size; i++) {
        o[i] = weight[i] * (ss * x[i]);
    }
}

// 高性能 MatMul: C = A * B (向量化 & OpenMP)
void matmul(float* xout, float* x, float* w, int n, int d) {
    // xout: [d], x: [n], w: [d x n]
    #pragma omp parallel for
    for (int i = 0; i < d; i++) {
        float val = 0.0f;
        for (int j = 0; j < n; j++) {
            val += w[i * n + j] * x[j];
        }
        xout[i] = val;
    }
}

// Softmax
void softmax(float* x, int size) {
    float max_val = x[0];
    for (int i = 1; i < size; i++) if (x[i] > max_val) max_val = x[i];
    float sum = 0.0f;
    for (int i = 0; i < size; i++) {
        x[i] = expf(x[i] - max_val);
        sum += x[i];
    }
    for (int i = 0; i < size; i++) x[i] /= sum;
}

// SiLU (SwiGLU 的一部分) - 现代 LLM 的激活函数
void silu(float* x, int size) {
    for (int i = 0; i < size; i++) {
        x[i] = x[i] * (1.0f / (1.0f + expf(-x[i])));
    }
}

// ============================================================================
// 3. 前向传播链路 (简化版 llm.c 逻辑)
// ============================================================================

void transformer_forward(Config* p, RunState* s, int pos, float* weights) {
    // 这里仅演示一层 Block 的逻辑，实际 llm.c 会循环 n_layers
    float* x = s->x;
    int dim = p->dim;
    int hidden_dim = p->hidden_dim;

    // --- 1. Attention 部分 ---
    // RMSNorm
    rmsnorm(s->xb, x, weights, dim); // 假设权重在开头

    // QKV 投影 (简化)
    matmul(s->q, s->xb, weights + dim, dim, dim);
    matmul(s->k, s->xb, weights + dim + dim*dim, dim, dim);
    matmul(s->v, s->xb, weights + dim + 2*dim*dim, dim, dim);

    // ... 此处逻辑包含 RoPE 和 Scaled Dot-Product Attention ...
    // 为了极致性能，llm.c 使用分块（Tiling）和寄存器缓存，并在 OpenMP 下并行化

    // --- 2. Feed-Forward 部分 (FFN) ---
    rmsnorm(s->xb, x, weights + 3*dim*dim + dim, dim);
    
    // SiLU + MatMul (Swiglu 风格)
    matmul(s->hb, s->xb, weights + 4*dim*dim, dim, hidden_dim);
    silu(s->hb, hidden_dim);
    // ...
}

// (End of library)
