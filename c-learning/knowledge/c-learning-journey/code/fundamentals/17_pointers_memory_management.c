#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ==================== 前置声明 ====================

int add(int a, int b);
int multiply(int a, int b);
void* safe_malloc(size_t size);

// ==================== 指针基础复习 ====================

void pointers_basics_demo() {
    printf("=== 指针基础复习 ===\n");

    int num = 42;
    int *ptr = &num;  // 指针指向num

    printf("1. 基本概念:\n");
    printf("   变量 num 的值: %d\n", num);
    printf("   变量 num 的地址: %p\n", (void*)&num);
    printf("   指针 ptr 的值 (地址): %p\n", (void*)ptr);
    printf("   指针 ptr 指向的值: %d\n", *ptr);

    // 修改指针指向的值
    *ptr = 100;
    printf("   修改后 num 的值: %d\n\n", num);

    // 指针的指针
    int **pptr = &ptr;
    printf("2. 指针的指针:\n");
    printf("   ptr 的地址: %p\n", (void*)&ptr);
    printf("   pptr 的值: %p\n", (void*)pptr);
    printf("   pptr 指向的值 (*pptr): %p\n", (void*)*pptr);
    printf("   pptr 指向的指针指向的值 (**pptr): %d\n\n", **pptr);
}

// ==================== 指针与数组 ====================

void pointers_arrays_demo() {
    printf("=== 指针与数组 ===\n");

    int arr[] = {10, 20, 30, 40, 50};
    int *ptr = arr;  // 数组名就是指向第一个元素的指针

    printf("1. 数组与指针的关系:\n");
    printf("   arr[0] = %d, *ptr = %d\n", arr[0], *ptr);
    printf("   arr[1] = %d, *(ptr+1) = %d\n", arr[1], *(ptr+1));
    printf("   arr[2] = %d, ptr[2] = %d\n", arr[2], ptr[2]);

    printf("\n2. 使用指针遍历数组:\n");
    for (int i = 0; i < 5; i++) {
        printf("   arr[%d] = %d (通过 *(ptr+%d) 访问)\n", i, *(ptr+i), i);
    }

    printf("\n3. 指针运算:\n");
    printf("   ptr 初始值: %p\n", (void*)ptr);
    ptr++;  // 指针向后移动一个int大小
    printf("   ptr++ 后: %p, 指向的值: %d\n", (void*)ptr, *ptr);
    ptr += 2;  // 再向后移动两个int
    printf("   ptr += 2 后: %p, 指向的值: %d\n\n", (void*)ptr, *ptr);
}

// ==================== 动态内存分配 ====================

void dynamic_memory_demo() {
    printf("=== 动态内存分配 ===\n");

    // 1. malloc - 分配内存
    printf("1. 使用 malloc 分配内存:\n");
    int *dynamic_int = (int*)malloc(sizeof(int));
    if (dynamic_int == NULL) {
        printf("   内存分配失败!\n");
        return;
    }
    *dynamic_int = 12345;
    printf("   分配的int值为: %d\n", *dynamic_int);
    printf("   地址: %p\n", (void*)dynamic_int);

    // 2. calloc - 分配并初始化为0
    printf("\n2. 使用 calloc 分配并初始化:\n");
    int *array = (int*)calloc(5, sizeof(int));  // 分配5个int，初始化为0
    if (array == NULL) {
        printf("   内存分配失败!\n");
        free(dynamic_int);
        return;
    }
    printf("   calloc分配的数组 (初始化为0): ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    // 3. realloc - 重新分配内存
    printf("\n3. 使用 realloc 重新分配内存:\n");
    array = (int*)realloc(array, 10 * sizeof(int));  // 扩大到10个int
    if (array == NULL) {
        printf("   内存重新分配失败!\n");
        free(dynamic_int);
        return;
    }
    printf("   重新分配后的大小: 10个int\n");
    printf("   新地址可能改变: %p\n", (void*)array);

    // 初始化新分配的部分
    for (int i = 5; i < 10; i++) {
        array[i] = (i + 1) * 10;
    }
    printf("   完整数组: ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    // 4. 释放内存
    printf("\n4. 释放内存:\n");
    free(dynamic_int);
    free(array);
    printf("   内存已释放\n\n");

    // ⚠️ 演示内存泄漏的风险
    printf("5. 内存泄漏演示 (危险操作):\n");
    printf("   创建一个动态数组但不释放它...\n");
    int *leaked_memory = (int*)malloc(100 * sizeof(int));
    if (leaked_memory != NULL) {
        printf("   分配了100个int的内存: %p\n", (void*)leaked_memory);
        // 这里故意不调用free()，模拟内存泄漏
        printf("   ⚠️  警告：内存泄漏！这块内存永远丢失了\n");
    }
}

// ==================== 指针与字符串 ====================

void pointers_strings_demo() {
    printf("=== 指针与字符串 ===\n");

    // 1. 字符串字面量 (存储在只读内存中)
    char *str_ptr = "Hello, World!";
    printf("1. 字符串字面量:\n");
    printf("   字符串: %s\n", str_ptr);
    printf("   地址: %p\n", (void*)str_ptr);

    // ⚠️ 危险操作：试图修改字符串字面量
    printf("\n2. 危险操作演示:\n");
    printf("   尝试修改字符串字面量...\n");
    // str_ptr[0] = 'h';  // 这会导致段错误！注释掉以避免崩溃

    // 2. 动态分配字符串内存
    printf("\n3. 动态分配字符串:\n");
    char *dynamic_str = (char*)malloc(20 * sizeof(char));
    if (dynamic_str == NULL) {
        printf("   内存分配失败!\n");
        return;
    }

    strcpy(dynamic_str, "Dynamic String");
    printf("   动态字符串: %s\n", dynamic_str);
    printf("   地址: %p\n", (void*)dynamic_str);

    // 可以安全地修改
    dynamic_str[0] = 'd';
    printf("   修改后: %s\n", dynamic_str);

    free(dynamic_str);
    printf("   内存已释放\n\n");
}

// ==================== 指针数组与数组指针 ====================

void advanced_pointers_demo() {
    printf("=== 指针数组与数组指针 ===\n");

    // 1. 指针数组：数组元素是指针
    printf("1. 指针数组:\n");
    char *names[] = {"Alice", "Bob", "Charlie", "David"};
    int num_names = 4;

    for (int i = 0; i < num_names; i++) {
        printf("   names[%d] = %s (地址: %p)\n", i, names[i], (void*)names[i]);
    }

    // 2. 数组指针：指向数组的指针
    printf("\n2. 数组指针:\n");
    int matrix[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };

    int (*array_ptr)[4] = matrix;  // 指向包含4个int的数组的指针

    printf("   使用数组指针访问二维数组:\n");
    for (int i = 0; i < 3; i++) {
        printf("   第%d行: ", i);
        for (int j = 0; j < 4; j++) {
            printf("%d ", array_ptr[i][j]);
        }
        printf("\n");
    }

    // 3. 函数指针
    printf("\n3. 函数指针:\n");
    int (*math_func)(int, int);  // 声明函数指针

    // 让函数指针指向不同的函数
    math_func = &add;  // 或直接写 math_func = add;
    printf("   add(10, 5) = %d\n", math_func(10, 5));

    math_func = &multiply;
    printf("   multiply(10, 5) = %d\n", math_func(10, 5));
}

// ==================== 辅助函数定义 ====================

int add(int a, int b) { return a + b; }
int multiply(int a, int b) { return a * b; }

void* safe_malloc(size_t size) {
    void* ptr = malloc(size);
    if (ptr == NULL) {
        fprintf(stderr, "内存分配失败！请求大小: %zu 字节\n", size);
        exit(1);
    }
    return ptr;
}

// ==================== 内存管理最佳实践 ====================

void memory_management_best_practices() {
    printf("=== 内存管理最佳实践 ===\n");

    printf("1. 黄金法则:\n");
    printf("   ✅ 每申请一次内存，就释放一次\n");
    printf("   ✅ 检查malloc/calloc返回值是否为NULL\n");
    printf("   ✅ 释放后将指针设为NULL\n");
    printf("   ✅ 避免野指针和悬挂指针\n");

    printf("\n2. 常见错误模式:\n");
    printf("   ❌ 忘记释放动态分配的内存 → 内存泄漏\n");
    printf("   ❌ 使用free()后继续访问内存 → 未定义行为\n");
    printf("   ❌ 重复释放同一块内存 → 双重释放错误\n");
    printf("   ❌ 访问未初始化的指针 → 段错误\n");

    printf("\n3. 安全内存分配函数:\n");
    printf("   推荐使用封装的分配函数来增加安全性\n\n");
}


// ==================== 综合练习项目 ====================

void memory_manager_project() {
    printf("=== 综合项目：简单内存管理器 ===\n");
    printf("这个项目将综合运用指针、动态内存分配等概念\n\n");

    // 简单的动态数组实现
    typedef struct {
        int* data;
        size_t size;
        size_t capacity;
    } DynamicArray;

    // 初始化
    DynamicArray arr;
    arr.size = 0;
    arr.capacity = 4;
    arr.data = (int*)safe_malloc(arr.capacity * sizeof(int));

    printf("1. 初始化动态数组:\n");
    printf("   容量: %zu, 大小: %zu\n", arr.capacity, arr.size);

    // 添加元素 (模拟动态扩容)
    printf("\n2. 添加元素并自动扩容:\n");
    for (int i = 0; i < 10; i++) {
        // 检查是否需要扩容
        if (arr.size >= arr.capacity) {
            arr.capacity *= 2;
            arr.data = (int*)realloc(arr.data, arr.capacity * sizeof(int));
            if (arr.data == NULL) {
                printf("   扩容失败!\n");
                return;
            }
            printf("   扩容到容量: %zu\n", arr.capacity);
        }

        arr.data[arr.size++] = (i + 1) * 10;
        printf("   添加元素: %d, 当前大小: %zu\n", arr.data[arr.size-1], arr.size);
    }

    // 显示数组内容
    printf("\n3. 数组内容:\n   ");
    for (size_t i = 0; i < arr.size; i++) {
        printf("%d ", arr.data[i]);
    }
    printf("\n");

    // 释放内存
    free(arr.data);
    arr.data = NULL;
    printf("\n4. 内存已安全释放\n");
}

int main() {
    printf("🎯 C语言指针与内存管理教学模块\n");
    printf("================================\n\n");

    // 依次演示各个主题
    pointers_basics_demo();
    pointers_arrays_demo();
    dynamic_memory_demo();
    pointers_strings_demo();
    advanced_pointers_demo();
    memory_management_best_practices();
    memory_manager_project();

    printf("🎉 指针与内存管理模块学习完成！\n");
    printf("您现在应该能够:\n");
    printf("  ✓ 理解指针的基本概念和用法\n");
    printf("  ✓ 使用动态内存分配函数\n");
    printf("  ✓ 避免常见的内存管理错误\n");
    printf("  ✓ 实现简单的内存管理结构\n");

    return 0;
}