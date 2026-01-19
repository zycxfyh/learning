#include <stdio.h>

// 1. 宏定义 (#define)
// 考试重点：宏只是简单的文本替换，一定要加括号！
#define SQUARE(x) x * x
#define SAFE_SQUARE(x) ((x) * (x))

// 2. static 变量
void count_calls() {
    static int count = 0; // 静态变量，只初始化一次，函数结束不销毁
    count++;
    printf("函数被调用了 %d 次\n", count);
}

int main() {
    printf("--- 1. 宏定义的陷阱 ---\n");
    int val = 5;
    // SQUARE(5+1) 替换为 5+1 * 5+1 = 5+5+1 = 11 (错误预期)
    printf("SQUARE(5+1) = %d (非预期: 11)\n", SQUARE(val + 1));
    // SAFE_SQUARE(5+1) 替换为 ((5+1)*(5+1)) = 36 (正确)
    printf("SAFE_SQUARE(5+1) = %d (预期: 36)\n", SAFE_SQUARE(val + 1));

    printf("\n--- 2. static 变量演示 ---\n");
    count_calls();
    count_calls();
    count_calls();

    return 0;
}
