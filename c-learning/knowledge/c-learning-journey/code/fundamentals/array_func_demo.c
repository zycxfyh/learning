#include <stdio.h>

// 1. 函数声明 (Function Declaration)
// 考试重点：函数要先声明或定义，才能被调用
int add(int a, int b);
void print_array(int arr[], int size);

int main() {
    printf("--- 1. 一维数组 ---\n");
    // 定义并初始化
    int scores[5] = {90, 85, 70, 95, 80};
    printf("第三个学生的成绩 (下标2): %d\n", scores[2]);

    printf("\n--- 2. 函数调用与传值 ---\n");
    int x = 10, y = 20;
    int result = add(x, y); 
    printf("%d + %d = %d\n", x, y, result);

    printf("\n--- 3. 数组作为参数 (重要细节!) ---\n");
    // 考试点：数组传给函数时，实际上传递的是地址（指针）
    print_array(scores, 5);

    printf("\n--- 4. 二维数组 (矩阵) ---\n");
    // 定义一个 2x3 的矩阵
    int matrix[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };
    printf("第一行第二列的元素: %d\n", matrix[0][1]);

    return 0;
}

// 函数实现
int add(int a, int b) {
    return a + b;
}

void print_array(int arr[], int size) {
    printf("数组内容: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
