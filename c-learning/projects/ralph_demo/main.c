#include <stdio.h>

// 目标：计算 1 到 n 的和
// 错误：循环条件写成了 i < n，漏掉了 n 本身
int sum(int n) {
    int total = 0;
    for (int i = 1; i < n; i++) {
        total += i;
    }
    return total;
}

int main() {
    int n = 10;
    int expected = 55;
    int actual = sum(n);
    
    if (actual == expected) {
        printf("测试通过！结果为 %d\n", actual);
        return 0;
    } else {
        printf("测试失败：期望 %d，实际得到 %d\n", expected, actual);
        return 1;
    }
}
