#ifndef TRANSFORMER_CORE_H
#define TRANSFORMER_CORE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdint.h>

/**
 * @brief 扁平化数据结构
 * 模拟 llm.c 中的组织方式：将所有权重和状态存储在连续的内存中
 */
typedef struct {
    float* data;
    int rows;
    int cols;
} Tensor;

// 全局计算配置
typedef struct {
    int seq_len;
    int d_model;
    int d_ff;
    int n_heads;
    int head_dim;
} Config;

// 预分配的推理状态（激活值等）
typedef struct {
    float* buffer;     // 整个前向传播过程中使用的单一连续内存块
    size_t size;
    // 关键中间变量的偏移指针
    float* x_norm;
    float* qkv;
    float* attn_scores;
    float* attn_out;
    float* ffn_h;
} InferenceState;

// 核心优化算子
void matmul(float* out, float* a, float* b, int n, int k, int m);
void layernorm(float* out, float* x, float* weight, float* bias, int n, int d);
void softmax(float* x, int n);
void relu(float* x, int n);
void rope(float* q, float* k, int head_dim, int pos, int d_model);

// 模型结构
void forward(Config* config, InferenceState* state, float* input, float* weights);

#endif // TRANSFORMER_CORE_H
