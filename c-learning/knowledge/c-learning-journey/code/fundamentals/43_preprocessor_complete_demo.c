#include <stdio.h>

// 1. 宏定义 - 简单的文本替换
#define PI 3.14159265359
#define SQUARE(x) ((x) * (x))
#define MAX(a,b) ((a) > (b) ? (a) : (b))

// 2. 条件编译
#define DEBUG_MODE 1
#define VERSION "2.0"

// 3. 平台相关的条件编译
#ifdef __linux__
    #define OS_NAME "Linux"
#elif defined(_WIN32)
    #define OS_NAME "Windows"
#else
    #define OS_NAME "Unknown"
#endif

int main() {
    printf("=== 预处理器完整演示 ===\n\n");

    // 宏定义演示
    printf("1. 宏定义常量: PI = %.2f\n", PI);
    printf("2. 宏定义函数: SQUARE(5) = %d\n", SQUARE(5));
    printf("3. 复杂宏: MAX(10,20) = %d\n", MAX(10,20));

    // 条件编译演示
#ifdef DEBUG_MODE
    printf("4. 调试模式已启用 (VERSION: %s)\n", VERSION);
#endif

    printf("5. 操作系统: %s\n", OS_NAME);

    // 文件信息（预处理器内置宏）
    printf("6. 当前文件: %s\n", __FILE__);
    printf("7. 当前行号: %d\n", __LINE__);
    printf("8. 编译日期: %s\n", __DATE__);
    printf("9. 编译时间: %s\n", __TIME__);

    return 0;
}