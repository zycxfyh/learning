#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ==================== 练习1: 指针基础练习 ====================

void exercise_1_pointers_basics() {
    printf("练习1: 指针基础\n");
    printf("请补全代码，完成以下功能：\n\n");

    // 1.1 声明一个整数变量和指向它的指针
    int num = 42;
    int *ptr;  // 声明指针变量

    // 1.2 让指针指向变量
    ptr = &num;  // 获取num的地址

    // 1.3 通过指针修改变量的值
    *ptr = 100;  // 解引用并修改

    printf("修改后的num值: %d (应该输出: 100)\n", num);

    // 1.4 指针的指针
    int **pptr = &ptr;
    **pptr = 200;

    printf("再次修改后的num值: %d (应该输出: 200)\n\n", num);
}

// ==================== 练习2: 数组与指针 ====================

void exercise_2_arrays_pointers() {
    printf("练习2: 数组与指针\n");

    int arr[] = {10, 20, 30, 40, 50};
    int *ptr = arr;  // 数组名就是指针

    printf("使用指针遍历数组:\n");
    // 使用指针遍历数组并打印每个元素
    for (int i = 0; i < 5; i++) {
        printf("arr[%d] = %d (通过指针: %d)\n", i, arr[i], *(ptr + i));
    }

    // 修改数组元素
    *(ptr + 2) = 300;  // 修改第3个元素
    printf("\n修改后 arr[2] = %d\n\n", arr[2]);
}

// ==================== 练习3: 动态内存分配 ====================

void exercise_3_dynamic_memory() {
    printf("练习3: 动态内存分配\n");

    // 3.1 分配一个整数的内存
    int *dynamic_int = (int*)malloc(sizeof(int));
    if (dynamic_int == NULL) {
        printf("内存分配失败!\n");
        return;
    }

    *dynamic_int = 123;
    printf("动态分配的整数: %d\n", *dynamic_int);

    // 3.2 释放内存
    free(dynamic_int);
    dynamic_int = NULL;  // 避免悬挂指针
    printf("内存已释放\n\n");
}

// ==================== 练习4: 指针作为函数参数 ====================

// 4.1 实现交换两个整数的函数
void swap_integers(int *a, int *b) {
    // 请实现交换逻辑
    int temp = *a;
    *a = *b;
    *b = temp;
}

void exercise_4_pointer_parameters() {
    printf("练习4: 指针作为函数参数\n");

    int x = 10, y = 20;
    printf("交换前: x=%d, y=%d\n", x, y);

    swap_integers(&x, &y);
    printf("交换后: x=%d, y=%d\n\n", x, y);
}

// ==================== 练习5: 字符串与指针 ====================

void exercise_5_strings_pointers() {
    printf("练习5: 字符串与指针\n");

    // 5.1 动态分配字符串内存
    char *dynamic_str = (char*)malloc(50 * sizeof(char));
    if (dynamic_str == NULL) {
        printf("内存分配失败!\n");
        return;
    }

    strcpy(dynamic_str, "Hello, Dynamic World!");
    printf("动态字符串: %s\n", dynamic_str);

    // 5.2 修改字符串
    dynamic_str[7] = 'P';  // 修改第8个字符
    printf("修改后: %s\n", dynamic_str);

    // 5.3 释放内存
    free(dynamic_str);
    printf("内存已释放\n\n");
}

// ==================== 练习6: 简单的数据结构实现 ====================

// 6.1 实现一个简单的动态数组
typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} DynamicArray;

void init_dynamic_array(DynamicArray *arr, size_t initial_capacity) {
    arr->data = (int*)malloc(initial_capacity * sizeof(int));
    arr->size = 0;
    arr->capacity = initial_capacity;
}

void add_to_dynamic_array(DynamicArray *arr, int value) {
    // 检查是否需要扩容
    if (arr->size >= arr->capacity) {
        arr->capacity *= 2;
        arr->data = (int*)realloc(arr->data, arr->capacity * sizeof(int));
    }
    arr->data[arr->size++] = value;
}

void free_dynamic_array(DynamicArray *arr) {
    free(arr->data);
    arr->data = NULL;
    arr->size = 0;
    arr->capacity = 0;
}

void exercise_6_data_structures() {
    printf("练习6: 简单的数据结构实现\n");

    DynamicArray arr;
    init_dynamic_array(&arr, 4);

    // 添加元素
    for (int i = 1; i <= 8; i++) {
        add_to_dynamic_array(&arr, i * 10);
    }

    // 打印数组内容
    printf("动态数组内容: ");
    for (size_t i = 0; i < arr.size; i++) {
        printf("%d ", arr.data[i]);
    }
    printf("\n");
    printf("数组大小: %zu, 容量: %zu\n", arr.size, arr.capacity);

    free_dynamic_array(&arr);
    printf("动态数组已释放\n\n");
}

// ==================== 练习7: 内存泄漏检测 ====================

void exercise_7_memory_leaks() {
    printf("练习7: 内存泄漏检测\n");
    printf("分析以下代码是否有内存泄漏:\n\n");

    printf("代码片段1:\n");
    printf("```c\n");
    printf("void func1() {\n");
    printf("    int *ptr = (int*)malloc(sizeof(int));\n");
    printf("    *ptr = 42;\n");
    printf("    // 这里没有free(ptr);\n");
    printf("}\n");
    printf("```\n");
    printf("❓ 有内存泄漏吗？为什么？\n\n");

    printf("代码片段2:\n");
    printf("```c\n");
    printf("void func2() {\n");
    printf("    int *arr = (int*)malloc(10 * sizeof(int));\n");
    printf("    for(int i = 0; i < 10; i++) arr[i] = i;\n");
    printf("    free(arr);\n");
    printf("    arr = NULL;\n");
    printf("}\n");
    printf("```\n");
    printf("❓ 这个代码安全吗？\n\n");

    printf("代码片段3:\n");
    printf("```c\n");
    printf("void func3() {\n");
    printf("    char *str = \"Hello\";  // 字符串字面量\n");
    printf("    str[0] = 'h';  // 修改\n");
    printf("}\n");
    printf("```\n");
    printf("❓ 这个代码会发生什么？为什么？\n\n");
}

// ==================== 挑战练习: 实现字符串分割函数 ====================

// 实现一个简单的字符串分割函数
// 例如: split("hello,world,test", ",") 应该返回 ["hello", "world", "test"]
char** split_string(const char* str, const char* delimiter, int* count) {
    // 这是一个挑战练习，需要实现字符串分割逻辑
    // 提示：使用strtok函数或手动实现
    // 返回分割后的字符串数组

    // 简单的实现，使用strtok
    char* str_copy = strdup(str);  // 复制字符串
    char** result = NULL;
    *count = 0;

    char* token = strtok(str_copy, delimiter);
    while (token != NULL) {
        (*count)++;
        result = (char**)realloc(result, *count * sizeof(char*));
        result[*count - 1] = strdup(token);
        token = strtok(NULL, delimiter);
    }

    free(str_copy);
    return result;
}

void exercise_8_challenge() {
    printf("挑战练习8: 字符串分割函数\n");

    const char* test_str = "apple,banana,orange,grape";
    const char* delimiter = ",";
    int count = 0;

    char** parts = split_string(test_str, delimiter, &count);

    printf("原始字符串: %s\n", test_str);
    printf("分割结果 (%d 部分):\n", count);

    for (int i = 0; i < count; i++) {
        printf("  部分%d: %s\n", i + 1, parts[i]);
        free(parts[i]);  // 释放每个字符串
    }

    free(parts);  // 释放数组
    printf("\n");
}

// ==================== 综合自测 ====================

void self_test() {
    printf("=== 指针与内存管理自测 ===\n");

    // 问题1: 指针声明
    printf("问题1: 以下哪个是指针声明的正确语法？\n");
    printf("A) int ptr;\n");
    printf("B) int *ptr;\n");
    printf("C) *int ptr;\n");
    printf("D) ptr int;\n");
    printf("答案: B) int *ptr;\n\n");

    // 问题2: 动态内存
    printf("问题2: 以下哪个函数用于释放动态分配的内存？\n");
    printf("A) malloc\n");
    printf("B) calloc\n");
    printf("C) realloc\n");
    printf("D) free\n");
    printf("答案: D) free\n\n");

    // 问题3: 内存泄漏
    printf("问题3: 什么是内存泄漏？\n");
    printf("答案: 动态分配的内存没有被释放，导致程序占用的内存越来越多\n\n");

    // 问题4: 指针运算
    printf("问题4: 如果ptr是一个int指针，ptr+1指向什么？\n");
    printf("答案: 下一个int位置（地址增加sizeof(int)字节）\n\n");
}

// ==================== 主函数 ====================

int main() {
    printf("🎯 C语言指针与内存管理练习集\n");
    printf("================================\n\n");

    printf("这个练习集将帮助您巩固指针和内存管理的核心概念。\n");
    printf("每个练习都包含详细的说明和示例代码。\n\n");

    // 运行所有练习
    exercise_1_pointers_basics();
    exercise_2_arrays_pointers();
    exercise_3_dynamic_memory();
    exercise_4_pointer_parameters();
    exercise_5_strings_pointers();
    exercise_6_data_structures();
    exercise_7_memory_leaks();
    exercise_8_challenge();
    self_test();

    printf("🎉 所有练习完成！\n");
    printf("如果您在练习过程中遇到困难，建议：\n");
    printf("1. 回顾理论知识\n");
    printf("2. 查看示例代码\n");
    printf("3. 尝试调试运行\n");
    printf("4. 与他人讨论思路\n");
    printf("5. 多做类似的练习\n\n");

    printf("准备好进入下一个阶段了吗？数据结构与算法！\n");

    return 0;
}