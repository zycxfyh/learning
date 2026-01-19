#include <stdio.h>

int main() {
    printf("--- 1. 写入文件 ---\n");
    FILE *fp = fopen("test.txt", "w"); // "w" 表示写入模式
    if (fp == NULL) {
        printf("无法打开文件！\n");
        return 1;
    }
    fprintf(fp, "Hello C Language!\n");
    fprintf(fp, "123 456\n");
    fclose(fp);
    printf("文件写入完成。\n");

    printf("\n--- 2. 读取文件 ---\n");
    int a, b;
    char word[20];
    fp = fopen("test.txt", "r"); // "r" 表示读取模式
    if (fp == NULL) {
        printf("文件不存在！\n");
        return 1;
    }
    
    // 跳过第一行，读第二行
    fscanf(fp, "%*s %*s %*s"); // 跳过 Hello C Language!
    fscanf(fp, "%d %d", &a, &b);
    
    printf("从文件读取到的数字: %d 和 %d\n", a, b);
    fclose(fp);

    return 0;
}
