#include <stdio.h>
#include <stdlib.h>

// 函数声明
void print_array(int arr[], int size);
void print_array_pointer(int *arr, int size);

// ==================== 数组进阶学习 ====================

int main() {
    printf("=== C语言数组进阶学习 ===\n\n");

    // 1. 多维数组
    printf("1. 多维数组:\n");

    // 二维数组声明和初始化
    int matrix[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };

    printf("二维数组 matrix[3][4]:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%2d ", matrix[i][j]);
        }
        printf("\n");
    }

    // 访问二维数组元素
    printf("matrix[1][2] = %d\n", matrix[1][2]); // 第2行第3列

    // 2. 数组与指针的深入关系
    printf("\n2. 数组与指针的深入关系:\n");

    int arr[] = {10, 20, 30, 40, 50};
    int *ptr = arr; // 数组名就是指向第一个元素的指针

    printf("数组arr的地址: %p\n", (void*)arr);
    printf("指针ptr的值: %p\n", (void*)ptr);
    printf("arr[0]的地址: %p\n", (void*)&arr[0]);

    // 指针算术运算
    printf("通过指针访问数组元素:\n");
    for (int i = 0; i < 5; i++) {
        printf("arr[%d] = %d, 通过指针: *(ptr + %d) = %d\n",
               i, arr[i], i, *(ptr + i));
    }

    // 3. 多维数组与指针
    printf("\n3. 多维数组与指针:\n");

    int (*matrix_ptr)[4] = matrix; // 指向包含4个int的数组的指针

    printf("通过指针访问二维数组:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%2d ", *(*(matrix_ptr + i) + j));
        }
        printf("\n");
    }

    // 4. 动态数组 (使用malloc)
    printf("\n4. 动态数组:\n");

    int size;
    printf("请输入动态数组的大小: ");
    scanf("%d", &size);

    // 分配动态数组
    int *dynamic_arr = (int*)malloc(size * sizeof(int));
    if (dynamic_arr == NULL) {
        printf("内存分配失败!\n");
        return 1;
    }

    // 初始化动态数组
    printf("请输入 %d 个整数:\n", size);
    for (int i = 0; i < size; i++) {
        scanf("%d", &dynamic_arr[i]);
    }

    // 显示动态数组
    printf("动态数组内容: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", dynamic_arr[i]);
    }
    printf("\n");

    // 释放动态内存
    free(dynamic_arr);

    // 5. 动态二维数组
    printf("\n5. 动态二维数组:\n");

    int rows = 2, cols = 3;
    // 分配行指针数组
    int **dynamic_matrix = (int**)malloc(rows * sizeof(int*));
    if (dynamic_matrix == NULL) {
        printf("内存分配失败!\n");
        return 1;
    }

    // 为每一行分配内存
    for (int i = 0; i < rows; i++) {
        dynamic_matrix[i] = (int*)malloc(cols * sizeof(int));
        if (dynamic_matrix[i] == NULL) {
            printf("内存分配失败!\n");
            // 释放已分配的内存
            for (int j = 0; j < i; j++) {
                free(dynamic_matrix[j]);
            }
            free(dynamic_matrix);
            return 1;
        }
    }

    // 初始化动态二维数组
    int value = 1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            dynamic_matrix[i][j] = value++;
        }
    }

    // 显示动态二维数组
    printf("动态二维数组:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%2d ", dynamic_matrix[i][j]);
        }
        printf("\n");
    }

    // 释放动态二维数组
    for (int i = 0; i < rows; i++) {
        free(dynamic_matrix[i]);
    }
    free(dynamic_matrix);

    // 6. 数组作为函数参数的各种方式
    printf("\n6. 数组作为函数参数:\n");

    int test_arr[] = {1, 2, 3, 4, 5};
    print_array(test_arr, 5);
    print_array_pointer(&test_arr[0], 5);

    // 7. 数组大小和边界
    printf("\n7. 数组大小和边界:\n");

    int boundary_arr[5] = {1, 2, 3, 4, 5};
    printf("数组大小: %zu 字节\n", sizeof(boundary_arr));
    printf("数组元素个数: %zu\n", sizeof(boundary_arr) / sizeof(boundary_arr[0]));

    // 演示数组越界（注意：这会导致未定义行为，不应该在实际代码中这样做）
    printf("数组最后一个有效元素: arr[4] = %d\n", boundary_arr[4]);
    // printf("数组越界访问: arr[5] = %d\n", boundary_arr[5]); // 危险！

    printf("\n=== 数组进阶学习完成 ===\n");

    return 0;
}

// 函数：以数组形式接收参数
void print_array(int arr[], int size) {
    printf("以数组形式接收参数: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// 函数：以指针形式接收参数
void print_array_pointer(int *arr, int size) {
    printf("以指针形式接收参数: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", *(arr + i));
    }
    printf("\n");
}