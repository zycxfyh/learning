#include "transformer_core.h"

int main() {
    printf("=== Transformer-C: 2026 重构版 (高性能扁平化架构) ===\n");

    Config config = {2, 4, 8, 1, 4}; // seq_len, d_model, d_ff, n_heads, head_dim
    
    // 分配连续权重空间
    size_t weights_size = (config.d_model * config.d_model * 3) + (config.d_model * config.d_ff) + (config.d_ff * config.d_model);
    float* weights = (float*)calloc(weights_size, sizeof(float));
    for(int i=0; i<weights_size; i++) weights[i] = 0.1f; // 初始化权重

    // 分配推理状态空间
    InferenceState state;
    state.size = config.seq_len * config.d_ff * 2; // 足够容纳中间变量
    state.buffer = (float*)calloc(state.size, sizeof(float));
    state.x_norm = state.buffer;
    state.qkv = state.x_norm + config.seq_len * config.d_model;
    state.ffn_h = state.qkv + config.seq_len * config.d_model;
    state.attn_out = state.ffn_h + config.seq_len * config.d_ff;

    // 输入数据
    float input[] = {1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 2.0f, 2.0f, 2.0f};

    printf("执行前向传播...\n");
    forward(&config, &state, input, weights);

    printf("输出结果 (前 4 个元素): %.2f %.2f %.2f %.2f\n", input[0], input[1], input[2], input[3]);

    free(weights);
    free(state.buffer);
    printf("重构验证完成。\n");
    return 0;
}
