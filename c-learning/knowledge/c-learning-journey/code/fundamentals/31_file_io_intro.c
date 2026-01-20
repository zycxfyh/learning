#include <stdio.h>

int main() {
    // 1. 打开文件 (就像在 Excel 里点击“打开文件”)
    // "w" 代表写入模式 (write)
    FILE *fp = fopen("note.txt", "w");

    if (fp == NULL) {
        printf("打开文件失败！\n");
        return 1;
    }

    // 2. 写入内容 (就像在表格里打字)
    fprintf(fp, "你好，这是我的第一份 C 语言文件！\n");
    fprintf(fp, "学习进度：100%% 完成！\n");

    // 3. 关闭文件 (一定要记得存档！)
    fclose(fp);

    printf("文件 'note.txt' 已成功生成。你可以去左侧文件树看看它。\n");

    // 4. 下一步挑战：读取这个文件
    printf("\n=== 现在尝试读取它的内容 ===\n");
    char buffer[100];
    fp = fopen("note.txt", "r"); // "r" 代表读取模式 (read)
    
    // fgets 会读取一行内容
    while (fgets(buffer, 100, fp) != NULL) {
        printf("读取到: %s", buffer);
    }
    
    fclose(fp);

    return 0;
}
