#ifndef TRANSFORMER_H
#define TRANSFORMER_H

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief 基础张量结构
 * LLM 处理的所有数据本质上都是多维数组。
 * 为了简化，我们暂时使用数据指针 + 形状数组。
 */
typedef struct {
    float* data;      // 数据指针 (一维展开存储，即 "Row-Major")
    int num_elements; // 元素总数
    int rows;         // 行数 (如果是矩阵)
    int cols;         // 列数 (如果是矩阵)
} Tensor;

/**
 * @brief 预分配内存池 (社区最佳实践)
 * 避免在推理过程中反复 malloc/free
 */
typedef struct {
    float* buffer;
    size_t offset;
    size_t capacity;
} MemoryPool;

MemoryPool* pool_create(size_t capacity);
void pool_reset(MemoryPool* pool);
Tensor* pool_alloc_tensor(MemoryPool* pool, int rows, int cols);
void pool_free(MemoryPool* pool);

// 张量操作
Tensor* tensor_create(int rows, int cols);
void tensor_free(Tensor* t);
void tensor_fill(Tensor* t, float val);
void tensor_print(Tensor* t, const char* name);

// 核心数学运算
/**
 * @brief 矩阵乘法：C = A * B
 * A 的列数必须等于 B 的行数。
 * C 的形状将是 [A.rows, B.cols]
 */
void matmul(Tensor* A, Tensor* B, Tensor* C);

// 第二阶段：激活与归一化
void softmax(Tensor* t);
void relu(Tensor* t);
void layernorm(Tensor* t, Tensor* gamma, Tensor* beta); // 简化版，每个样本归一化

// 第三阶段：注意力机制
void matmul_transb(Tensor* A, Tensor* B, Tensor* C); // C = A * B^T
void attention(Tensor* Q, Tensor* K, Tensor* V, Tensor* output);

// 第四阶段：组装 Transformer Block
void tensor_add(Tensor* A, Tensor* B, Tensor* C); // C = A + B
void ffn(Tensor* input, Tensor* W1, Tensor* B1, Tensor* W2, Tensor* B2, Tensor* output);
void transformer_block(Tensor* input, 
                       Tensor* Q_w, Tensor* K_w, Tensor* V_w, 
                       Tensor* W1, Tensor* B1, Tensor* W2, Tensor* B2,
                       Tensor* output);

// 第五阶段：高级特性
void rope(Tensor* q, Tensor* k, int head_dim, int pos);

#endif // TRANSFORMER_H
