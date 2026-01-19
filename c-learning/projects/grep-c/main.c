// 必须定义这个宏才能使用 strcasestr (Linux/GNU 特有扩展)
#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>

// 增加一个参数: int case_insensitive (1表示不区分大小写，0表示区分)
void grep_file(char *pattern, char *filename, int case_insensitive) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }

    char line[256];
    int line_number = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        line_number++;
        
        char *result;
        if (case_insensitive) {
            // strcasestr: 忽略大小写的版本 (Case String String)
            result = strcasestr(line, pattern);
        } else {
            // strstr: 标准版本
            result = strstr(line, pattern);
        }

        if (result != NULL) {
            printf("%d: %s", line_number, line);
        }
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    // 简单的参数解析逻辑
    // 默认情况: ./mygrep pattern filename
    int case_insensitive = 0;
    char *pattern;
    char *filename;

    if (argc == 3) {
        // 标准模式
        pattern = argv[1];
        filename = argv[2];
    } else if (argc == 4 && strcmp(argv[1], "-i") == 0) {
        // 忽略大小写模式: ./mygrep -i pattern filename
        case_insensitive = 1;
        pattern = argv[2];
        filename = argv[3];
    } else {
        printf("Usage: %s [-i] <pattern> <filename>\n", argv[0]);
        return 1;
    }

    grep_file(pattern, filename, case_insensitive);

    return 0;
}
