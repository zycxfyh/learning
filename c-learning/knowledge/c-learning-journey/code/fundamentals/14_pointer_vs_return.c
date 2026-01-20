#include <stdio.h>

// 方法 1：不用指针，用“返回值” (Return Value)
// 就像是：你给医生照片，医生改好后发了一封邮件告诉你新岁数，你自己手动改了档案
int change_by_return(int n) {
    return n + 10;
}

// 方法 2：使用指针 (Pointer)
// 就像是：医生直接上门，把你档案改了
void change_by_pointer(int *p) {
    *p = *p + 10;
}

int main() {
    int money = 100;

    printf("1. 初始金额: %d\n", money);

    // --- 不用指针的方法 ---
    printf("\n[方法 1] 不用指针 (必须手动赋值给原变量):\n");
    money = change_by_return(money); // 注意这里：必须有 = 赋值
    printf("   结果: %d\n", money);

    // --- 使用指针的方法 ---
    printf("\n[方法 2] 使用指针 (函数直接“潜入”修改):\n");
    change_by_pointer(&money);       // 注意这里：直接调用，不需要 = 赋值
    printf("   结果: %d\n", money);

    return 0;
}
