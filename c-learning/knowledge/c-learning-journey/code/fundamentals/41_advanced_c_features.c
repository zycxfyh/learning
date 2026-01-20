#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ==================== 函数指针演示 ====================

// 简单的数学运算函数
int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }
int divide(int a, int b) { return b != 0 ? a / b : 0; }

// 函数指针类型定义
typedef int (*MathOperation)(int, int);

// 使用函数指针的计算器
int calculate(MathOperation op, int a, int b) {
    return op(a, b);
}

// ==================== 回调函数演示 ====================

// 数组处理回调函数类型
typedef void (*ArrayProcessor)(int*, int);

// 数组处理函数
void print_array(int* arr, int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) printf(", ");
    }
    printf("]\n");
}

void double_values(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] *= 2;
    }
}

void square_values(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] *= arr[i];
    }
}

// 处理数组的函数（接受回调函数）
void process_array(int* arr, int size, ArrayProcessor processor) {
    processor(arr, size);
}

// ==================== 预处理器技巧演示 ====================

// 1. 宏函数
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define SQUARE(x) ((x) * (x))
#define CUBE(x) ((x) * (x) * (x))

// 2. 字符串化操作符
#define PRINT_VAR(var) printf(#var " = %d\n", var)
#define PRINT_STR(str) printf("%s: %s\n", #str, str)

// 3. 条件编译
#define DEBUG_MODE 1
#define VERSION "1.2.3"

// 4. 宏粘合操作符
#define CONCAT(a, b) a##b
#define MAKE_FUNC_NAME(prefix, num) CONCAT(prefix, num)

// ==================== 变长参数宏 ====================

#define LOG_INFO(format, ...) printf("[INFO] " format "\n", ##__VA_ARGS__)
#define LOG_ERROR(format, ...) printf("[ERROR] " format "\n", ##__VA_ARGS__)
#define LOG_DEBUG(format, ...) do { \
    if (DEBUG_MODE) printf("[DEBUG] " format "\n", ##__VA_ARGS__); \
} while(0)

// ==================== 函数指针数组演示 ====================

// 菜单项结构体
typedef struct {
    char* name;
    MathOperation operation;
} MenuItem;

// 菜单系统
void show_menu() {
    printf("\n=== 计算器菜单 ===\n");
    printf("1. 加法\n");
    printf("2. 减法\n");
    printf("3. 乘法\n");
    printf("4. 除法\n");
    printf("0. 退出\n");
    printf("请选择: ");
}

int main() {
    printf("=== C语言高级特性演示 ===\n\n");

    // ==================== 函数指针演示 ====================
    printf("1. 函数指针演示:\n");

    MathOperation ops[] = {add, subtract, multiply, divide};
    char* op_names[] = {"加法", "减法", "乘法", "除法"};

    for (int i = 0; i < 4; i++) {
        int result = calculate(ops[i], 10, 3);
        printf("  %s: 10 ? 3 = %d\n", op_names[i], result);
    }

    // ==================== 回调函数演示 ====================
    printf("\n2. 回调函数演示:\n");

    int test_array[] = {1, 2, 3, 4, 5};
    int array_size = sizeof(test_array) / sizeof(test_array[0]);

    printf("  原始数组: ");
    print_array(test_array, array_size);

    printf("  翻倍后: ");
    process_array(test_array, array_size, double_values);
    print_array(test_array, array_size);

    printf("  平方后: ");
    process_array(test_array, array_size, square_values);
    print_array(test_array, array_size);

    // ==================== 预处理器宏演示 ====================
    printf("\n3. 预处理器宏演示:\n");

    int x = 5, y = 10;
    printf("  MAX(%d, %d) = %d\n", x, y, MAX(x, y));
    printf("  MIN(%d, %d) = %d\n", x, y, MIN(x, y));
    printf("  SQUARE(%d) = %d\n", x, SQUARE(x));
    printf("  CUBE(%d) = %d\n", x, CUBE(x));

    // 字符串化
    PRINT_VAR(x);
    PRINT_VAR(y);

    char* program_name = "Advanced C Demo";
    PRINT_STR(program_name);

    // ==================== 条件编译演示 ====================
    printf("\n4. 条件编译演示:\n");

    #ifdef DEBUG_MODE
        printf("  调试模式已启用 (版本: %s)\n", VERSION);
        LOG_DEBUG("这是一个调试信息");
    #else
        printf("  调试模式已禁用\n");
    #endif

    // ==================== 变长参数宏演示 ====================
    printf("\n5. 变长参数宏演示:\n");

    LOG_INFO("程序启动成功");
    LOG_INFO("当前时间戳: %ld", time(NULL));
    LOG_ERROR("这是一个错误示例: %s", "文件未找到");

    // ==================== 函数指针数组演示 ====================
    printf("\n6. 函数指针数组和菜单系统:\n");

    MenuItem menu[] = {
        {"加法", add},
        {"减法", subtract},
        {"乘法", multiply},
        {"除法", divide}
    };

    int choice;
    do {
        show_menu();
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 4) {
            int a, b;
            printf("请输入两个整数: ");
            scanf("%d %d", &a, &b);

            int result = calculate(menu[choice-1].operation, a, b);
            printf("结果: %d %s %d = %d\n", a, menu[choice-1].name, b, result);
        } else if (choice != 0) {
            printf("无效选择!\n");
        }
    } while (choice != 0);

    // ==================== 宏粘合演示 ====================
    printf("\n7. 宏粘合操作符演示:\n");

    // 创建动态函数名
    int (*func_ptr)(const char*, ...) = printf;
    func_ptr("  使用宏粘合创建的函数指针\n");

    printf("\n=== 演示完成 ===\n");
    return 0;
}