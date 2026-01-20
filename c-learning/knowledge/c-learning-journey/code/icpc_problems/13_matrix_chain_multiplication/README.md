# 🎓 Matrix Chain Multiplication

## 📊 题目元信息
- **难度等级**: ⭐⭐⭐⭐⭐ (经典DP问题)
- **年份**: 经典算法问题
- **通过率**: 高 (基础动态规划)
- **核心技术**: 区间动态规划

---

## 🎯 问题描述

**矩阵链乘法最优计算顺序**:
给出n个矩阵的维度，找到乘法顺序使得总的标量乘法次数最少。

### 📥 输入规格
```
第一行: n (矩阵数量)
第二行: n+1个整数 p[0..n] (矩阵维度)
```

### 📤 输出规格
- 最少乘法次数

---

## 🔍 难点剖析

### 🚨 三大挑战
1. **状态设计**: 如何定义DP状态表示子问题
2. **转移方程**: 找到子问题间的递推关系
3. **计算优化**: 避免重复计算相同的子问题

---

## 🧠 解题策略

### 🎯 总体思路
**区间DP: dp[i][j] = 子问题i到j的最优解**

### 📋 详细步骤

#### 阶段1: 状态定义
- dp[i][j]: 矩阵i到j的最少乘法次数
- 长度从2到n递增计算

#### 阶段2: 转移方程
- 枚举分割点k (i≤k<j)
- dp[i][j] = min(dp[i][k] + dp[k+1][j] + 代价)

#### 阶段3: 代价计算
- 代价 = p[i-1] × p[k] × p[j]
- 表示两个子矩阵的乘积计算量

---

## 💻 实现框架

```c
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 105;
const int INF = 1e9;

int dp[MAX_N][MAX_N];
int p[MAX_N]; // 矩阵维度数组

int matrix_chain_order(int n) {
    // 初始化
    for(int i = 1; i <= n; i++) {
        dp[i][i] = 0;
    }

    // 区间长度从2到n
    for(int len = 2; len <= n; len++) {
        for(int i = 1; i <= n - len + 1; i++) {
            int j = i + len - 1;
            dp[i][j] = INF;

            // 尝试所有可能的分割点k
            for(int k = i; k < j; k++) {
                int cost = dp[i][k] + dp[k+1][j] +
                          p[i-1] * p[k] * p[j];
                if(cost < dp[i][j]) {
                    dp[i][j] = cost;
                }
            }
        }
    }

    return dp[1][n];
}

int main() {
    int n;
    cin >> n;

    for(int i = 0; i <= n; i++) {
        cin >> p[i];
    }

    cout << matrix_chain_order(n) << endl;
    return 0;
}
```

---

## 📚 学习要点

### 🎨 技术要点
1. **区间DP框架**: 长度递增的计算顺序
2. **状态转移**: 分割点的枚举和代价计算
3. **最优子结构**: 子问题的最优解组合

---

## 💡 练习建议

1. 理解区间DP的基本框架
2. 练习状态转移方程的推导
3. 掌握矩阵乘法复杂度的计算

---

**这道经典DP题目是算法入门的重要里程碑！** 🎓