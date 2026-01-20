#include <stdio.h>

int main() {
    printf("--- 1. 选择结构 (switch-case) ---\n");
    int grade = 'B';
    switch (grade) {
        case 'A': printf("优秀\n"); break; 
        case 'B': 
        case 'C': printf("良好/合格\n"); break; // 故意不写B的break，会落到C
        default: printf("未知状态\n");
    }
    // 考试提醒：switch 里的 case 必须是常量表达式！

    printf("\n--- 2. 循环结构 (求 1 到 100 之和) ---\n");
    int i = 1, sum = 0;
    while (i <= 100) {
        sum += i;
        i++;
    }
    printf("while 循环求和: %d\n", sum);

    sum = 0;
    for (int j = 1; j <= 100; j++) {
        if (j % 2 == 0) continue; // 跳过偶数
        sum += j;
        if (sum > 1000) break; // 超过1000就提前退出
    }
    printf("for 循环 (仅奇数且和<1000): %d\n", sum);

    printf("\n--- 3. do-while 唯一特性 ---\n");
    int k = 10;
    do {
        printf("这段话至少会打印一次，即使条件一开始就不满足 (k=10 > 5)\n");
    } while (k < 5);

    return 0;
}
