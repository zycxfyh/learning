#include "transformer_core.h"

void forward(Config* config, InferenceState* state, float* input, float* weights) {
    int seq_len = config->seq_len;
    int d_model = config->d_model;
    int d_ff = config->d_ff;
    int n_heads = config->n_heads;
    int head_dim = config->head_dim;

    // 此处简化权重布局：假设 weights 数组依次存储了 QW, KW, VW, W1, W2
    float* QW = weights;
    float* KW = QW + d_model * d_model;
    float* VW = KW + d_model * d_model;
    float* W1 = VW + d_model * d_model;
    float* W2 = W1 + d_model * d_ff;

    // 1. LayerNorm (Pre-Norm)
    layernorm(state->x_norm, input, NULL, NULL, seq_len, d_model);

    // 2. Attention (简化版)
    // 线性映射 Q, K, V
    matmul(state->qkv, state->x_norm, QW, seq_len, d_model, d_model); // 简写
    // ... 此处逻辑暂略，模拟计算流程 ...

    // 3. 残差连接 1
    for (int i = 0; i < seq_len * d_model; i++) {
        state->attn_out[i] += input[i]; 
    }

    // 4. 第二个 LayerNorm
    layernorm(state->x_norm, state->attn_out, NULL, NULL, seq_len, d_model);

    // 5. FFN
    matmul(state->ffn_h, state->x_norm, W1, seq_len, d_model, d_ff);
    relu(state->ffn_h, seq_len * d_ff);
    matmul(state->attn_out, state->ffn_h, W2, seq_len, d_ff, d_model);

    // 6. 残差连接 2
    for (int i = 0; i < seq_len * d_model; i++) {
        input[i] += state->attn_out[i]; // 直接写回 input 作为输出
    }
}
