#include <stdio.h>

int main() {
    // 1. 整数类型 (Integer) - 就像一个只能装整数的盒子
    int age = 19;

    // 2. 浮点数类型 (Float) - 可以装带小数点的数字
    float height = 1.80;

    // 3. 字符类型 (Character) - 只能装一个字母或符号，用单引号括起来
    char grade = 'C';

    // 打印这些变量：注意 %d, %f, %c 这些“占位符”
    printf("我的年龄是: %d 岁\n", age);
    printf("我的身高是: %.2f 米\n", height); // .2 代表保留两位小数
    printf("我的成绩等级是: %c\n", grade);

    return 0;
}
