#include <stdio.h>
#include <stdlib.h>

// 搜索算法
int linear_search(int arr[], int n, int target);
int binary_search(int arr[], int low, int high, int target);

// 递归算法
int factorial(int n);
int fibonacci(int n);
void tower_of_hanoi(int n, char from_rod, char to_rod, char aux_rod);
int gcd(int a, int b);
void print_array_recursive(int arr[], int n);

int main() {
    printf("=== C语言搜索算法和递归演示 ===\n\n");

    // 搜索算法测试
    int arr[] = {2, 5, 8, 12, 16, 23, 38, 45, 56, 72};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 23;

    printf("测试数组: ");
    print_array_recursive(arr, n);
    printf("\n");

    printf("1. 线性搜索 (Linear Search) - 查找 %d:\n", target);
    int result = linear_search(arr, n, target);
    if (result != -1) {
        printf("找到! 索引位置: %d\n", result);
    } else {
        printf("未找到\n");
    }

    printf("\n2. 二分搜索 (Binary Search) - 查找 %d:\n", target);
    result = binary_search(arr, 0, n-1, target);
    if (result != -1) {
        printf("找到! 索引位置: %d\n", result);
    } else {
        printf("未找到\n");
    }

    // 递归算法测试
    printf("\n=== 递归算法演示 ===\n");

    printf("\n3. 阶乘 (Factorial):\n");
    for (int i = 0; i <= 5; i++) {
        printf("%d! = %d\n", i, factorial(i));
    }

    printf("\n4. 斐波那契数列 (Fibonacci):\n");
    for (int i = 0; i <= 10; i++) {
        printf("F(%d) = %d\n", i, fibonacci(i));
    }

    printf("\n5. 汉诺塔 (Tower of Hanoi) - 3层:\n");
    tower_of_hanoi(3, 'A', 'C', 'B');

    printf("\n6. 最大公约数 (GCD):\n");
    printf("gcd(48, 18) = %d\n", gcd(48, 18));
    printf("gcd(100, 75) = %d\n", gcd(100, 75));

    return 0;
}

// 线性搜索 - O(n)
int linear_search(int arr[], int n, int target) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}

// 二分搜索 - O(log n) - 要求数组已排序
int binary_search(int arr[], int low, int high, int target) {
    if (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            return mid;
        }

        if (arr[mid] > target) {
            return binary_search(arr, low, mid - 1, target);
        }

        return binary_search(arr, mid + 1, high, target);
    }

    return -1;
}

// 递归计算阶乘
int factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

// 递归计算斐波那契数列
int fibonacci(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// 汉诺塔递归解法
void tower_of_hanoi(int n, char from_rod, char to_rod, char aux_rod) {
    if (n == 1) {
        printf("移动盘子 1 从 %c 到 %c\n", from_rod, to_rod);
        return;
    }

    tower_of_hanoi(n-1, from_rod, aux_rod, to_rod);
    printf("移动盘子 %d 从 %c 到 %c\n", n, from_rod, to_rod);
    tower_of_hanoi(n-1, aux_rod, to_rod, from_rod);
}

// 递归计算最大公约数 (欧几里得算法)
int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

// 递归打印数组
void print_array_recursive(int arr[], int n) {
    if (n == 0) {
        return;
    }
    printf("%d ", arr[0]);
    print_array_recursive(arr + 1, n - 1);
}