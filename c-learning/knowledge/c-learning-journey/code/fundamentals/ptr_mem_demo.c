#include <stdio.h>
#include <stdlib.h> // malloc/free 在这里

int main() {
    printf("--- 1. 指针运算与数组 ---\n");
    int arr[3] = {10, 20, 30};
    int *p = arr; // p 指向数组首元素

    printf("p   指向的值: %d\n", *p);
    printf("p+1 指向的值: %d (自动移动到下一个 int 的地址)\n", *(p + 1));

    printf("\n--- 2. 动态内存分配 (Heap) ---\n");
    // 考试点：malloc 返回 void*，通常需要强制类型转换
    int *dynamic_arr = (int *)malloc(3 * sizeof(int));
    
    if (dynamic_arr == NULL) {
        printf("内存分配失败！\n");
        return 1;
    }

    dynamic_arr[0] = 100;
    dynamic_arr[1] = 200;
    dynamic_arr[2] = 300;

    printf("动态数组第二个值: %d\n", dynamic_arr[1]);

    // 考试点：必须 free，否则内存泄漏
    free(dynamic_arr);
    dynamic_arr = NULL; // 养成好习惯：free后置NULL防止野指针

    return 0;
}
