#include <stdio.h>

int main() {
    // 1. 标识符 (Identifiers)
    // 合法的标识符
    int age = 18;
    int _count = 10;   // 下划线开头是合法的
    int score2 = 90;   // 数字不能在开头，但在中间或结尾可以

    // 非法的标识符 (如果取消注释，编译会报错)
    // int 2ndPlace = 2; // 错误：不能以数字开头
    // int my-name = 5;  // 错误：不能包含连字符 '-'，只能用下划线 '_'
    // int float = 3.14; // 错误：不能使用关键字 'float' 作为变量名

    printf("Age: %d, Count: %d, Score: %d\n", age, _count, score2);

    // 2. 进制 (Number Systems)
    // 考试重点：如何表示不同进制的数
    int decimal = 10;       // 十进制: 10
    int binary = 0b1010;    // 二进制 (以 0b 开头): 1*8 + 0*4 + 1*2 + 0*1 = 10
    int octal = 012;        // 八进制 (以 0 开头): 1*8 + 2*1 = 10
    int hex = 0xA;          // 十六进制 (以 0x 开头): A=10

    printf("\n--- 进制演示 ---\n");
    printf("十进制 10 显示为 %%d: %d\n", decimal);
    printf("二进制 0b1010 显示为 %%d: %d\n", binary);
    printf("八进制 012    显示为 %%d: %d\n", octal);
    printf("十六进制 0xA  显示为 %%d: %d\n", hex);

    // 以不同进制输出同一个数
    int number = 255;
    printf("\n--- 输出格式 ---\n");
    printf("数字 255 的十进制 (%%d): %d\n", number);
    printf("数字 255 的八进制 (%%o): %o\n", number);
    printf("数字 255 的十六进制 (%%x): %x\n", number);
    printf("数字 255 的十六进制大写 (%%X): %X\n", number);

    return 0;
}
