#include <stdio.h>
#include <string.h>

int main() {
    char *haystack = "I am learning C language";
    char *needle = "learn";
    
    // strstr 在 haystack 中寻找 needle
    char *result = strstr(haystack, needle);

    if (result != NULL) {
        printf("找到了！\n");
        printf("原来字符串: %s\n", haystack);
        // result 是一个指针，指向找到的位置
        printf("找到的位置: %s\n", result); 
    } else {
        printf("没找到。\n");
    }

    return 0;
}
