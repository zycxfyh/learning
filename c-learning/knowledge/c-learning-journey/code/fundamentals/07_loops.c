#include <stdio.h>

int main() {
    printf("=== 1. For 循环: 固定次数的任务 ===\n");
    // 任务：打印 1 到 5
    // for(初始化; 条件; 变化)
    for (int i = 1; i <= 5; i++) {
        printf("这是第 %d 次报数\n", i);
    }

    printf("\n=== 2. While 循环: 只要满足条件就一直做 ===\n");
    int count = 5;
    while (count > 0) {
        printf("倒计时: %d\n", count);
        count--; // 每次减 1，直到不满足 count > 0
    }

    printf("\n发射！🚀\n");
    return 0;
}
