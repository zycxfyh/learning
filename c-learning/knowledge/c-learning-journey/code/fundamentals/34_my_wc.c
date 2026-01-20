#include <stdio.h>
#include <ctype.h> // 使用 isspace 函数

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("用法: %s <文件名>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("错误");
        return 1;
    }

    int ch;
    long characters = 0;
    long words = 0;
    long lines = 0;
    int in_word = 0; // 状态标志：是否正在读取一个单词

    while ((ch = fgetc(fp)) != EOF) {
        characters++;

        if (ch == '\n') {
            lines++;
        }

        // 单词统计逻辑
        if (isspace(ch)) {
            in_word = 0;
        } else if (in_word == 0) {
            in_word = 1;
            words++;
        }
    }

    fclose(fp);

    printf("文件: %s\n", argv[1]);
    printf("行数: %ld\n", lines);
    printf("单词: %ld\n", words);
    printf("字符: %ld\n", characters);

    return 0;
}
