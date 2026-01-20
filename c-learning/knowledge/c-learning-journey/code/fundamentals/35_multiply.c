#include <stdio.h>

// 声明函数 (函数的“名片”)
int multiply(int a, int b);

// 定义函数 (算命具体的乘法逻辑)
int multiply(int a, int b) {
    return a * b; // 直接返回 a 乘以 b 的结果
}

int main() {
    int a, b;
    
    // 增加提示语，让程序更友好
    printf("请输入两个要相乘的整数（用空格隔开）: ");
    
    // scanf 接收输入，存入 a 和 b 的地址
    if (scanf("%d %d", &a, &b) == 2) {
        int result = multiply(a, b);
        printf("计算结果: %d * %d = %d\n", a, b, result);
    } else {
        printf("输入错误，请输入整数。\n");
    }
    
    return 0;
}