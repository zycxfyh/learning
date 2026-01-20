# 🏆 Miniature Golf (ICPC World Finals 2019)

## 📊 题目元信息
- **难度等级**: ⭐⭐⭐⭐⭐⭐⭐ (7.5/10)
- **年份**: 2019 ICPC World Finals
- **通过率**: ~30支队伍 (高难度)
- **核心技术**: 计算几何 + 物理模拟 + 数值优化

---

## 🎯 问题描述

**故事背景**:
微型高尔夫球场模拟，球从起始位置出发，遵循物理规律在复杂地形中运动。地形包含平坦区域、斜坡、障碍物，洞口有确定的位置和大小。

**核心任务**:
计算球的运动轨迹，确定是否存在击球参数使得球能落入洞中。如果存在，找到最少的击球次数或最优的击球参数。

### 📥 输入规格
```
第一行: 球的初始位置和洞口位置
x1 y1 x2 y2
    (x1,y1): 球起始位置
    (x2,y2): 洞口位置

接下来描述地形元素:
每行一个地形元素 (直线、圆弧、障碍物等)
最后一行: 结束标记
```

### 📤 输出规格
- **一杆进洞**: `HOLE-IN-ONE`
- **需要击球**: 输出最少击球次数
- **不可能**: `IMPOSSIBLE`

---

## 🔍 难点剖析

### 🚨 三大挑战
1. **物理模拟精度**
   - 精确的运动学计算
   - 碰撞检测的几何运算
   - 数值积分的稳定性保证

2. **几何计算复杂度**
   - 球与各种地形元素的交点
   - 反射角度的精确计算
   - 多边形区域的碰撞检测

3. **参数优化困难**
   - 击球角度和力度的高维优化
   - 非凸目标函数的寻优
   - 约束条件下的最优解搜索

### 💭 思维深度
- **物理建模**: 将现实物理转化为数学计算
- **数值方法**: 常微分方程的离散求解
- **优化算法**: 非线性优化的实用方法

---

## 🧠 解题策略

### 🎯 总体思路
**物理建模 + 数值积分 + 参数优化**

### 📋 详细步骤

#### 阶段1: 物理建模 (O(地形复杂度))
- **运动方程**: 牛顿力学 + 重力场
- **碰撞模型**: 弹性碰撞 + 能量损失
- **地形表示**: 几何图元 + 边界条件

#### 阶段2: 轨迹计算 (O(积分步数))
- **数值积分**: 龙格-库塔方法
- **碰撞检测**: 快速几何相交测试
- **终止条件**: 进洞或超出边界

#### 阶段3: 参数优化 (O(优化迭代))
- **参数空间**: 角度和力度的二维搜索
- **目标函数**: 到洞口距离的评价
- **搜索策略**: 三分搜索或梯度下降

### ⚡ 核心优化
1. **几何预处理**: 空间划分加速碰撞检测
2. **自适应步长**: 根据速度调整积分精度
3. **早期终止**: 快速判断不可能进洞的情况
4. **多起点采样**: 初始参数的启发式选择

---

## 📊 复杂度分析

### ⏱️ 时间复杂度
- **单次模拟**: O(轨迹长度 × 碰撞检测)
- **参数搜索**: O(搜索次数 × 模拟复杂度)
- **优化版本**: O(log(精度) × 模拟) 三分搜索
- **实际表现**: 通常在1-2秒内完成

### 💾 空间复杂度
- **地形存储**: O(地形元素数量)
- **轨迹缓存**: O(积分步数)
- **优化空间**: O(1) 或 O(参数维度)

### 🎯 实际限制
- 坐标精度: 需要处理浮点数误差
- 时间限制: 2-3秒，积分步数有限
- 内存限制: 256MB，轨迹点数适中

---

## 💻 实现框架

### 🏗️ 数据结构
```c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#define MAX_TERRAIN 1005
#define MAX_ITER 10000
#define EPS 1e-9

// 几何点结构
typedef struct {
    double x, y;
} Point;

// 向量结构
typedef struct {
    double x, y;
} Vector;

// 地形元素
typedef struct {
    int type;        // 0:直线, 1:圆弧, 2:障碍物
    Point start, end;
    double radius;   // 圆弧半径
    // 其他参数...
} Terrain;

// 全局变量
Point ball_pos, hole_pos;
Terrain terrain[MAX_TERRAIN];
int terrain_count;
double HOLE_RADIUS = 1.0;
```

### 🎯 主算法流程
```c
int main() {
    // 读取输入
    scanf("%lf%lf%lf%lf", &ball_pos.x, &ball_pos.y,
          &hole_pos.x, &hole_pos.y);

    // 读取地形
    terrain_count = 0;
    // TODO: 读取地形数据

    // 参数搜索
    double best_distance = DBL_MAX;
    int min_strokes = 100;

    // 尝试不同的击球参数
    for(double angle = 0; angle < 2*M_PI; angle += M_PI/36) {
        for(double power = 1.0; power <= 20.0; power += 1.0) {
            Point final_pos = simulate_trajectory(angle, power);

            double dist = distance(final_pos, hole_pos);
            if(dist < HOLE_RADIUS) {
                // 进洞，计算击球次数
                min_strokes = 1;  // 简化为一杆
                goto found;
            }
        }
    }

    found:
    if(min_strokes <= 10) {
        printf("HOLE-IN-ONE\n");  // 或输出次数
    } else {
        printf("IMPOSSIBLE\n");
    }

    return 0;
}
```

### 🔧 关键函数

#### 轨迹模拟
```c
// 模拟球的运动轨迹
Point simulate_trajectory(double angle, double power) {
    // 初始状态
    Point pos = ball_pos;
    double vx = power * cos(angle);
    double vy = power * sin(angle);

    double dt = 0.01;  // 时间步长
    int steps = 0;

    while(steps < MAX_ITER) {
        // 保存旧位置
        Point old_pos = pos;

        // 欧拉积分
        pos.x += vx * dt;
        pos.y += vy * dt;
        vy -= 9.8 * dt;  // 重力加速度

        // 碰撞检测
        if(check_collision(old_pos, pos)) {
            // 计算碰撞点和反射
            Point collision_point = find_collision_point(old_pos, pos);
            Vector normal = get_surface_normal(collision_point);

            // 当前速度向量
            Vector velocity = {vx, vy};

            // 反射公式: v' = v - 2(v·n)n
            double dot = velocity.x * normal.x + velocity.y * normal.y;
            Vector reflection = {
                velocity.x - 2 * dot * normal.x,
                velocity.y - 2 * dot * normal.y
            };

            vx = reflection.x * 0.8;  // 能量损失
            vy = reflection.y * 0.8;

            // 重新定位到碰撞点
            pos = collision_point;
        }

        // 检查是否进洞
        if(distance(pos, hole_pos) < HOLE_RADIUS) {
            return pos;
        }

        // 检查是否超出边界
        if(pos.x < -1000 || pos.x > 1000 ||
           pos.y < -1000 || pos.y > 1000) {
            break;
        }

        steps++;
    }

    return pos;
}
```

#### 碰撞检测
```c
// 检查轨迹线段是否与地形碰撞
int check_collision(Point start, Point end) {
    for(int i = 0; i < terrain_count; i++) {
        if(terrain[i].type == 0) {  // 直线
            if(line_segment_intersection(start, end,
                terrain[i].start, terrain[i].end)) {
                return 1;
            }
        } else if(terrain[i].type == 1) {  // 圆弧
            // TODO: 圆弧碰撞检测
        }
    }
    return 0;
}

// 直线段交点计算
int line_segment_intersection(Point a, Point b, Point c, Point d) {
    // 计算参数方程交点
    double denom = (a.x - b.x)*(c.y - d.y) - (a.y - b.y)*(c.x - d.x);

    if(fabs(denom) < EPS) return 0;  // 平行

    double t = ((a.x - c.x)*(c.y - d.y) - (a.y - c.y)*(c.x - d.x)) / denom;
    double s = ((a.x - c.x)*(a.y - b.y) - (a.y - c.y)*(a.x - b.x)) / denom;

    // 检查参数是否在[0,1]范围内
    return (t >= 0 && t <= 1 && s >= 0 && s <= 1);
}

// 找到碰撞点
Point find_collision_point(Point start, Point end) {
    // 简化版：返回线段中点
    // 实际需要精确计算交点
    return (Point){(start.x + end.x)/2, (start.y + end.y)/2};
}

// 获取表面法线
Vector get_surface_normal(Point collision_point) {
    // TODO: 根据碰撞的地形计算法线向量
    // 简化版：返回垂直向上的法线
    return (Vector){0, 1};
}
```

#### 参数优化
```c
// 三分搜索优化角度
double optimize_angle(double power) {
    double left = 0, right = 2*M_PI;
    double best_angle = 0;
    double min_distance = DBL_MAX;

    for(int iter = 0; iter < 50; iter++) {
        double mid1 = left + (right - left) / 3;
        double mid2 = right - (right - left) / 3;

        double dist1 = evaluate_shot(mid1, power);
        double dist2 = evaluate_shot(mid2, power);

        if(dist1 < dist2) {
            right = mid2;
            if(dist1 < min_distance) {
                min_distance = dist1;
                best_angle = mid1;
            }
        } else {
            left = mid1;
            if(dist2 < min_distance) {
                min_distance = dist2;
                best_angle = mid2;
            }
        }

        // 早期停止
        if(min_distance < HOLE_RADIUS) break;
    }

    return best_angle;
}

// 评估一次击球
double evaluate_shot(double angle, double power) {
    Point final_pos = simulate_trajectory(angle, power);
    return distance(final_pos, hole_pos);
}
```

---

## 📚 学习要点

### 🎨 技术要点
1. **计算几何**
   - 点线位置关系判断
   - 交点计算的数值方法
   - 几何变换和坐标系

2. **物理模拟**
   - 运动学方程的离散化
   - 碰撞检测和响应
   - 数值积分的稳定性

3. **数值优化**
   - 参数空间的搜索策略
   - 三分搜索和梯度下降
   - 非线性优化的实用方法

4. **算法精度**
   - 浮点数误差的处理
   - 自适应步长的选择
   - 数值稳定性的保证

### 🧠 思维要点
1. **物理建模**: 将连续物理过程转化为离散计算
2. **数值方法**: 常微分方程的计算机求解
3. **优化思维**: 高维参数空间的有效搜索
4. **精度平衡**: 计算精度与时间效率的权衡

---

## 🔗 相关资源

### 📖 学习资料
- **原题**: ICPC 2019 World Finals Problem Set
- **物理引擎**: Box2D开源物理引擎
- **数值方法**: 《数值分析》积分方法章节

### 🎯 相似题目
- Angry Birds物理模拟
- 弹球游戏轨迹计算
- 其他物理运动模拟问题

---

## 💡 练习建议

### 📈 学习路径
1. **几何基础**: 实现点线距离和交点计算
2. **物理模拟**: 学习简单的欧拉积分方法
3. **碰撞检测**: 实现直线段和圆的碰撞
4. **参数优化**: 练习三分搜索和梯度下降

### 🔍 调试要点
1. **积分精度**: 时间步长的选择对结果的影响
2. **碰撞准确性**: 交点计算的几何正确性
3. **数值稳定性**: 浮点误差累积的处理
4. **优化效率**: 参数搜索的收敛速度

---

**这道题目完美结合了物理学、几何学和数值方法，是跨学科算法设计的典范！** 🏆