#include <stdio.h>
#include <string.h>

int main() {
    // 1. 字符串的本质：字符数组
    // 注意：C 语言会自动在末尾加上一个隐藏的 '\0' (空字符)，代表字符串结束
    char greeting[] = "Hello"; 

    printf("=== 字符串本质探索 ===\n");
    printf("字符串内容: %s\n", greeting);
    
    // 2. 像操作数组一样操作字符串
    printf("第 1 个字母: %c\n", greeting[0]);
    printf("第 4 个字母: %c\n", greeting[3]);

    // 3. 证明 '\0' 的存在
    // "Hello" 看起来只有 5 个字母，但数组大小其实是 6
    printf("数组占用的内存大小: %zu 字节\n", sizeof(greeting));

    // 4. 指针与字符串
    // 既然字符串是数组，那我们也可以用指针来指向它
    char *p = greeting;
    printf("通过指针打印: %s\n", p);
    printf("通过指针+1 打印: %s\n", p + 1); // 会从第二个字母开始打印到结束

    return 0;
}
