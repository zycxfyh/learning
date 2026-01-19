#include <stdio.h>

// 1. 函数的“声明”：告诉电脑有一个叫 add 的工具，它需要两个整数，最后会给回一个整数
int add(int a, int b);

// 2. 函数的“定义”：具体怎么做
int add(int a, int b) {
    int result = a + b;
    return result; // 把结果“吐”出来
}

// 3. 另一个不需要返回值的函数 (void 代表空)
void say_hello(char name[]) {
    printf("你好, %s! 欢迎学习函数模块。\n", name);
}

int main() {
    int x = 10, y = 20;
    
    // 调用函数
    int sum = add(x, y);
    
    say_hello("新同学");
    printf("%d + %d 的计算结果是: %d\n", x, y, sum);

    return 0;
}
