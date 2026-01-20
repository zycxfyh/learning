#include <stdio.h>

int main() {
    int num1, num2;
    int sum;

    printf("=== 简易加法计算器 ===\n");

    // 1. 获取第一个数字
    printf("请输入第一个整数: ");
    scanf("%d", &num1); // 注意这里的 & 符号，它代表“地址”，告诉电脑把数放到哪个盒子里

    // 2. 获取第二个数字
    printf("请输入第二个整数: ");
    scanf("%d", &num2);

    // 3. 计算
    sum = num1 + num2;

    // 4. 输出结果
    printf("计算结果: %d + %d = %d\n", num1, num2, sum);

    return 0;
}
