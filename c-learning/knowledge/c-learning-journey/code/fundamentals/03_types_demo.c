#include <stdio.h>
#include <limits.h> // 包含 INT_MAX 等常量

int main() {
    // 1. 基本数据类型的大小
    // 考试重点：sizeof 返回的是字节数 (bytes)
    printf("--- 数据类型大小 (sizeof) ---\n");
    printf("char:   %lu byte\n", sizeof(char));
    printf("short:  %lu bytes\n", sizeof(short));
    printf("int:    %lu bytes\n", sizeof(int));
    printf("long:   %lu bytes\n", sizeof(long));
    printf("float:  %lu bytes\n", sizeof(float));
    printf("double: %lu bytes\n", sizeof(double));

    // 2. 溢出 (Overflow) - 考试常见的坑
    printf("\n--- 整数溢出演示 ---\n");
    short small_num = 32767; // short 的最大值通常是 32767 (2^15 - 1)
    
    printf("当前数值: %d\n", small_num);
    small_num = small_num + 1;
    printf("加 1 后的数值: %d (发生了溢出，变成负数最小)\n", small_num);

    // 3. 字符类型其实是整数
    char ch = 'A';
    printf("\n--- 字符与整数 ---\n");
    printf("字符 '%c' 对应的 ASCII 码是: %d\n", ch, ch);
    printf("ASCII 码 66 对应的字符是: %c\n", 66);

    return 0;
}
