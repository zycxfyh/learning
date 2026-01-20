#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 函数声明
int is_prime(int n);
int fibonacci(int n);
void print_multiplication_table(int n);
int calculate_factorial(int n);
void swap_values(int* a, int* b);
int find_max_in_array(int arr[], int size);

int main() {
    printf("=== C语言基础阶段复习与巩固 ===\n\n");

    // 1. 基本数据类型和运算符练习
    printf("1. 基本数据类型和运算符:\n");

    // 计算并显示不同类型的大小
    printf("数据类型大小:\n");
    printf("  char: %lu bytes\n", sizeof(char));
    printf("  int: %lu bytes\n", sizeof(int));
    printf("  float: %lu bytes\n", sizeof(float));
    printf("  double: %lu bytes\n\n", sizeof(double));

    // 运算符练习
    int a = 15, b = 4;
    printf("运算符练习 (a=%d, b=%d):\n", a, b);
    printf("  a + b = %d\n", a + b);
    printf("  a - b = %d\n", a - b);
    printf("  a * b = %d\n", a * b);
    printf("  a / b = %d (整数除法)\n", a / b);
    printf("  a %% b = %d (取余)\n", a % b);
    printf("  a > b = %s\n", a > b ? "true" : "false");
    printf("  a & b = %d (按位与)\n", a & b);
    printf("  a | b = %d (按位或)\n", a | b);
    printf("  a ^ b = %d (按位异或)\n", a ^ b);
    printf("  a << 1 = %d (左移)\n", a << 1);

    // 2. 流程控制练习
    printf("\n2. 流程控制练习:\n");

    // if-else 练习：判断成绩等级
    int score = 85;
    printf("成绩 %d 的等级: ", score);
    if (score >= 90) {
        printf("优秀\n");
    } else if (score >= 80) {
        printf("良好\n");
    } else if (score >= 70) {
        printf("中等\n");
    } else if (score >= 60) {
        printf("及格\n");
    } else {
        printf("不及格\n");
    }

    // switch-case 练习：判断星期
    int day = 3;
    printf("数字 %d 对应的星期: ", day);
    switch (day) {
        case 1: printf("星期一\n"); break;
        case 2: printf("星期二\n"); break;
        case 3: printf("星期三\n"); break;
        case 4: printf("星期四\n"); break;
        case 5: printf("星期五\n"); break;
        case 6: printf("星期六\n"); break;
        case 7: printf("星期日\n"); break;
        default: printf("无效的星期数\n");
    }

    // 循环练习：打印乘法表
    printf("\n九九乘法表:\n");
    print_multiplication_table(9);

    // 3. 函数练习
    printf("\n3. 函数练习:\n");

    // 质数判断
    int test_numbers[] = {7, 15, 23, 29, 100};
    printf("质数判断:\n");
    for (int i = 0; i < 5; i++) {
        int num = test_numbers[i];
        printf("  %d %s质数\n", num, is_prime(num) ? "是" : "不是");
    }

    // 斐波那契数列
    printf("\n斐波那契数列前10项:\n");
    for (int i = 1; i <= 10; i++) {
        printf("  F(%d) = %d\n", i, fibonacci(i));
    }

    // 阶乘计算
    printf("\n阶乘计算:\n");
    for (int i = 1; i <= 5; i++) {
        printf("  %d! = %d\n", i, calculate_factorial(i));
    }

    // 4. 数组和指针练习
    printf("\n4. 数组和指针练习:\n");

    int arr[] = {12, 45, 78, 23, 56, 89, 34};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("数组内容: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // 寻找最大值
    int max_val = find_max_in_array(arr, size);
    printf("数组中的最大值: %d\n", max_val);

    // 指针交换值
    int x = 100, y = 200;
    printf("交换前: x=%d, y=%d\n", x, y);
    swap_values(&x, &y);
    printf("交换后: x=%d, y=%d\n", x, y);

    // 5. 随机数和时间
    printf("\n5. 随机数生成:\n");
    srand(time(NULL)); // 设置随机种子

    printf("10个随机数 (1-100):\n");
    for (int i = 0; i < 10; i++) {
        int random_num = rand() % 100 + 1;
        printf("  %d", random_num);
        if ((i + 1) % 5 == 0) printf("\n");
    }

    printf("\n=== 基础阶段复习完成 ===\n");
    printf("恭喜你掌握了C语言的核心基础概念！\n");

    return 0;
}

// 判断是否为质数
int is_prime(int n) {
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0 || n % 3 == 0) return 0;

    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return 0;
    }
    return 1;
}

// 计算斐波那契数列
int fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// 打印乘法表
void print_multiplication_table(int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            printf("%d×%d=%-2d ", j, i, i * j);
        }
        printf("\n");
    }
}

// 计算阶乘
int calculate_factorial(int n) {
    if (n == 0 || n == 1) return 1;
    return n * calculate_factorial(n - 1);
}

// 交换两个值 (使用指针)
void swap_values(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 在数组中寻找最大值
int find_max_in_array(int arr[], int size) {
    int max_val = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }
    return max_val;
}