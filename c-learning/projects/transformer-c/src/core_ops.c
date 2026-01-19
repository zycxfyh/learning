#include "transformer_core.h" // 包含核心定义，如常量和函数声明

/**
 * @brief 高性能矩阵乘法 C = A * B
 * A: [n x k] 矩阵, B: [k x m] 矩阵, out (C): [n x m] 矩阵
 * 核心优化：采用 i-k-j 循环顺序，通过“行优先”访问极大地提高 CPU 缓存利用率
 */
void matmul(float* out, float* a, float* b, int n, int k, int m) {
    // 1. 安全初始化：将输出缓冲区全部清零，因为后面的操作是累加 (+=)
    // memset 是底层高度优化的内存填充函数，比 for 循环更快
    memset(out, 0, n * m * sizeof(float));

    // 2. 外层循环：遍历 A 矩阵和结果矩阵 C 的每一行 (共 n 行)
    for (int i = 0; i < n; i++) {
        // 3. 中层循环：遍历 A 的每一列，也就是 B 的每一行 (共 k 个累加项)
        // 重点：我们将 k 循环提到了 j 循环外面，这是性能飞跃的关键
        for (int p = 0; p < k; p++) {
            // 4. “锁死点”：获取 A[i][p] 的值，并存入寄存器变量 val 中
            // 这样在接下来的内层循环里，CPU 就不需要反复去内存里读这同一个数了
            float val = a[i * k + p]; 

            // 5. 内层循环：顺着 B 矩阵的第 p 行，横向扫过所有列 (共 m 列)
            // 魔法发生在这里：j 循环走的时候，out[i][j] 和 b[p][j] 都是连续在内存里移动的
            // 这让 CPU 可以开启“预取”机制，且能使用 SIMD 指令实现“一炮打四/八个”的并行计算
            for (int j = 0; j < m; j++) {
                // 核心计算逻辑：结果(i,j) 累加 A(i,p) * B(p,j)
                out[i * m + j] += val * b[p * m + j];
            }
        }
    }
}

/**
 * @brief 层归一化 (Layer Normalization)
 * 将每一行的数据强行拉回到均值为 0、方差为 1 的分布，并进行缩放与偏移
 */
void layernorm(float* out, float* x, float* weight, float* bias, int n, int d) {
    // 遍历每一行 (n 表示 Token 数量或 Batch 大小)
    for (int i = 0; i < n; i++) {
        float* row_x = x + i * d;      // 指向当前行输入的起始位置
        float* row_out = out + i * d;  // 指向当前行输出的起始位置

        // 1. 计算当前行的元素之和，用于求均值
        float mean = 0.0f;
        for (int j = 0; j < d; j++) mean += row_x[j];
        mean /= d; // 得到当前行的统计平均值

        // 2. 计算方差 (每个数与均值差的平方的平均值)
        float var = 0.0f;
        for (int j = 0; j < d; j++) {
            float diff = row_x[j] - mean;
            var += diff * diff; // 累加平方差
        }
        var /= d; // 得到方差

        // 3. 计算标准差的倒数，预先算好以减少循环内的除法开销 (除法比乘法慢很多)
        // 1e-5f 是微小的 epsilon 值，防止在分母为 0 时发生崩溃
        float inv_std = 1.0f / sqrtf(var + 1e-5f);

        // 4. 执行归一化操作：(x - mean) * inv_std，并应用可选的权重权重 gamma (weight) 和偏置 beta (bias)
        for (int j = 0; j < d; j++) {
            float val = (row_x[j] - mean) * inv_std; // 核心归一化
            if (weight) val *= weight[j];           // 缩放操作 (如果参数存在)
            if (bias) val += bias[j];               // 偏移操作 (如果参数存在)
            row_out[j] = val;                       // 写入结果
        }
    }
}

/**
 * @brief ReLU 激活函数：负数切零，正数保留
 */
void relu(float* x, int n) {
    for (int i = 0; i < n; i++) {
        // 如果 x[i] 是负数，则将其设为 0；若是正数则保持不变
        if (x[i] < 0) x[i] = 0;
    }
}

/**
 * @brief 数值安全的 Softmax：将向量转为概率分布，且和为 1
 */
void softmax(float* x, int n) {
    // 1. 寻找向量中的最大值，用于数值安全处理
    float max_val = x[0];
    for (int i = 1; i < n; i++) if (x[i] > max_val) max_val = x[i];

    // 2. 计算指数 e^(x - max)，并累加求和
    // 提示：减去最大值后，指数项最大为 e^0 = 1，有效防止了浮点数溢出 (NaN)
    float sum = 0.0f;
    for (int i = 0; i < n; i++) {
        x[i] = expf(x[i] - max_val); // 使用单精度指数函数 expf 以提高性能
        sum += x[i];                 // 计算分母的总和
    }

    // 3. 归一化：每个元素除以总和，使结果落在 0-1 之间且总和为 1
    for (int i = 0; i < n; i++) x[i] /= sum;
}
