# 🎯 任务书：第三步 - 概率与非线性 (Softmax & GELU)

## 目标
实现 `softmax` 和 `GELU` 激活函数。这是 Transformer 能够“注意”到重点和处理复杂模式的关键。

## 任务背景
- **Softmax**：将一组得分转为概率分布。在 Attention 里，我们要用它来算出不同词的权重。
- **GELU (Gaussian Error Linear Unit)**：现代大模型（如 GPT）的标准激活函数，比 ReLU 更平滑。

## 关键挑战：精度与指数爆炸
- `softmax` 的公式是 $P_i = \frac{e^{x_i}}{\sum e^{x_j}}$。
- **坑**：如果 $x_i$ 很大，$e^{x_i}$ 会溢出 (NaN)。
- **解决**：使用 "Safe Softmax"，即所有项都减去当前行的最大值。

## 算法 Spec
### 1. Softmax (Row-wise)
对每一行进行：
1. 找到行最大值 `max_val`。
2. 计算每个元素的 $exp(x - max\_val)$。
3. 求和。
4. 每个元素除以和。

### 2. GELU (近似公式)
$GELU(x) = 0.5x(1 + tanh(\sqrt{2/\pi}(x + 0.044715x^3)))$

---
## 检查标准
1. 对 `[1.0, 2.0, 3.0]` 进行 Softmax，结果应该是 `[0.09, 0.24, 0.67]` 左右。
2. 运行测试：
```bash
gcc step3_activate_lab.c -o lab3 -lm && ./lab3
```
