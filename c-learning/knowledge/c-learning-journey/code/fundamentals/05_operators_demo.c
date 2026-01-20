#include <stdio.h>

int main() {
    printf("--- 1. 自增自减的陷阱 (考试必考!) ---\n");
    int i = 5;
    int a = i++; // “先赋值，后自增”：a得到5，i变6
    printf("a = i++ -> a: %d, i: %d\n", a, i);

    i = 5;
    int b = ++i; // “先自增，后赋值”：i变6，b得到6
    printf("b = ++i -> b: %d, i: %d\n", b, i);

    printf("\n--- 2. 算术运算符 ---\n");
    int x = 10, y = 3;
    printf("10 / 3 = %d (整数除法丢弃小数)\n", x / y);
    printf("10 %% 3 = %d (取模运算得到余数)\n", x % y);
    printf("10.0 / 3 = %.2f (有一方是浮点数则执行浮点除法)\n", 10.0 / y);

    printf("\n--- 3. 逻辑运算符与短路效应 ---\n");
    int m = 0, n = 5;
    // 短路：若 && 左边为假，右边就不执行了
    if (m && (++n)) { } 
    printf("m && (++n) 执行后，n: %d (n没变，说明++n被跳过了)\n", n);

    if (!m || (++n)) { }
    printf("!m || (++n) 执行后，n: %d (n没变，说明||右边被跳过了)\n", n);

    printf("\n--- 4. 位运算 (期末大题常客) ---\n");
    unsigned char p = 0x0F; // 0000 1111
    unsigned char q = 0xF0; // 1111 0000
    printf("0x0F & 0xF0 = 0x%02X\n", p & q); // 按位与
    printf("0x0F | 0xF0 = 0x%02X\n", p | q); // 按位或
    printf("0x0F << 2   = 0x%02X\n", p << 2); // 左移 (相当于*4)

    return 0;
}
