#include <stdio.h>

// 这个函数收到的只是一个数字的备份 (照片)
void fail_to_change(int n) {
    n = n + 10; 
    printf("  [函数内部] 备份被改成了: %d\n", n);
}

// 这个函数收到的地址变量 (门牌号)
void real_change(int *p) {
    // *p 意味着：找到这个地址对应的那个原始变量
    *p = *p + 10; 
    printf("  [函数内部] 通过指针成功修改了原始值！\n");
}

int main() {
    int money = 100;

    printf("1. 初始金额: %d\n", money);

    printf("\n执行 fail_to_change (传值)...\n");
    fail_to_change(money); 
    printf("2. 结果: %d (原件没变)\n", money);

    printf("\n执行 real_change (传址)...\n");
    real_change(&money); // 这里必须送地址过去
    printf("3. 结果: %d (原件竟然变了！)\n", money);

    return 0;
}
