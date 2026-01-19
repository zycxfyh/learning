# 🎯 任务书：第四步 - 深度模型的稳定性 (LayerNorm)

## 目标
实现 `layernorm` (层归一化)。这是防止深度神经网络在训练和推理过程中梯度爆炸或消失的关键。

## 任务背景
在 Transformer 的每一个 Block 之前/之后，都要进行 LayerNorm。
它不像 BatchNorm 那样依赖 Batch，它是对**每一行（每个 Token 的所有维度）**独立进行的。

## 数学公式
对于每一行 $x$：
1. **均值 (Mean)**： $\mu = \frac{1}{n} \sum x_i$
2. **方差 (Variance)**： $\sigma^2 = \frac{1}{n} \sum (x_i - \mu)^2$
3. **归一化 (Normalize)**： $\hat{x}_i = \frac{x_i - \mu}{\sqrt{\sigma^2 + \epsilon}}$
   - 其中 $\epsilon$ 是一个极小的数（通常是 $1e-5$），防止除以零。
4. **缩放与偏移 (Scale & Shift)**： $y_i = \hat{x}_i \cdot \gamma + \beta$
   - 这里的 $\gamma$ (Weight) 和 $\beta$ (Bias) 是可学习的参数。

## 算法 Spec
对每一行进行：
1. 计算均值。
2. 计算方差。
3. 对每个元素应用归一化公式。
4. 应用对应的 Weights ($\gamma$) 和 Bias ($\beta$)。

---
## 检查标准
1. 对 `[1.0, 2.0, 3.0]` 进行归一化（假设 gamma=1, beta=0），结果的均值应该接近 0，方差接近 1。
2. 运行测试：
```bash
gcc step4_layernorm_lab.c -o lab4 -lm && ./lab4
```
