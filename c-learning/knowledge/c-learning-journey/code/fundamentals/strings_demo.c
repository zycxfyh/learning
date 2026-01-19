#include <stdio.h>
#include <string.h>

int main() {
    // 1. 字符串的本质：以 \0 结尾的字符数组
    // 方式 A: 字符数组 (需要手动或自动包含 \0)
    char str1[] = {'H', 'e', 'l', 'l', 'o', '\0'}; 
    
    // 方式 B: 字符串字面量 (编译器自动加 \0)
    char str2[] = "Hello";

    printf("--- 字符串基础 ---\n");
    printf("str1: %s\n", str1);
    printf("str2: %s\n", str2);

    // 2. \0 的重要性 (考试必考!)
    // 如果没有 \0，printf 会继续打印内存中的垃圾数据，直到遇到一个 случайно 的 0
    char no_zero[] = {'H', 'i'}; // 危险！不是合法的 C 字符串
    
    printf("\n--- 危险演示 (\0 缺失) ---\n");
    // printf("no_zero: %s\n", no_zero); // 取消注释这行可能会看到乱码

    // 3. sizeof vs strlen
    // sizeof: 数组占用的总字节数 (包含 \0)
    // strlen: 字符串的逻辑长度 (不包含 \0)
    printf("\n--- sizeof vs strlen ---\n");
    printf("str2 (\"Hello\") sizeof: %lu (5个字符 + 1个\\0)\n", sizeof(str2));
    printf("str2 (\"Hello\") strlen: %lu (实际字符数)\n", strlen(str2));

    // 4. 字符串修改
    str2[0] = 'h'; // 修改第一个字符
    printf("\n修改后 str2: %s\n", str2);

    return 0;
}
