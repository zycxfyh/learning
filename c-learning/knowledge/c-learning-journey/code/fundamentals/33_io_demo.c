#include <stdio.h>

int main() {
    int age;
    char name[20];

    printf("--- 1. scanf 的基本用法 ---\n");
    printf("请输入年龄: ");
    // 考试点：基本类型变量前面要加 & 地址符
    scanf("%d", &age); 

    printf("请输入姓名: ");
    // 考试点：数组（字符串）名本身就是地址，不用加 &
    scanf("%s", name); 

    printf("你好, %s, 你今年 %d 岁。\n", name, age);

    printf("\n--- 2. scanf 的陷阱: 空格与缓冲区 ---\n");
    // scanf %s 遇到空格、回车、制表符会停止
    // 如果你在控制台输入 "Steve Jobs"，name 只会得到 "Steve"
    
    printf("\n--- 3. printf 格式化控制 ---\n");
    float pi = 3.1415926;
    printf("保留两位小数: %.2f\n", pi);
    printf("占位5格右对齐: [%5d]\n", 123);
    printf("占位5格补零: [%05d]\n", 123);

    return 0;
}
