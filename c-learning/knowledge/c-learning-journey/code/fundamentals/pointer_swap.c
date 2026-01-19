#include <stdio.h>

// ❌ 错误示范：没有指针，换不了
void swap_wrong(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
}

// ✅ 正确示范：使用指针，直接修改内存
void swap_right(int *pa, int *pb) {
    int temp = *pa; // 把 pa 地址里的值暂存起来
    *pa = *pb;      // 把 pb 地址里的值覆盖到 pa 地址里
    *pb = temp;     // 把暂存的值放到 pb 地址里
}

int main() {
    int x = 1, y = 99;

    printf("--- 初始状态 ---\n");
    printf("x = %d, y = %d\n", x, y);

    printf("\n1. 尝试使用普通的 swap_wrong (不传指针)...\n");
    swap_wrong(x, y);
    printf("结果: x = %d, y = %d (毫无变化，因为函数只改了备份)\n", x, y);

    printf("\n2. 尝试使用厉害的 swap_right (传入地址)...\n");
    swap_right(&x, &y); // 核心：把 x 和 y 的地址送过去
    printf("结果: x = %d, y = %d (成功交换！两口子换了房间)\n", x, y);

    return 0;
}
