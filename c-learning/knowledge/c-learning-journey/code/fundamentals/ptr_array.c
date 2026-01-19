#include <stdio.h>

int main() {
    int nums[3] = {10, 20, 30}; // 声明一个包含 3 个整数的数组
    int *p;

    // 核心秘密：数组名 nums，其实就是数组第一个元素的“地址”！
    p = nums; // 这句话等价于 p = &nums[0];

    printf("=== 指针与数组的秘密协议 ===\n");
    printf("1. 数组第一个元素的地址 (&nums[0]): %p\n", (void*)&nums[0]);
    printf("2. 数组名 nums 代表的值        : %p\n", (void*)nums);
    printf("   (你看！它们是一模一样的！)\n");

    printf("\n=== 使用指针“走楼梯” ===\n");
    // p 是第一个盒子的地址，p+1 就是第二个盒子的地址
    printf("3. *p     (第一个盒子): %d\n", *p);
    printf("4. *(p+1) (第二个盒子): %d\n", *(p+1));
    printf("5. *(p+2) (第三个盒子): %d\n", *(p+2));

    return 0;
}
