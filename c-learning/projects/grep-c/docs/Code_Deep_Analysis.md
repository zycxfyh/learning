# 🧐 代码深度解析：我们到底写了什么？

您现在的项目目录下有一个 `main.c`，虽然只有几十行，但它包含了 C 语言最核心的几个概念。

让我们逐行拆解，看看这段代码的**灵魂**在哪里。

## 1. 宏定义的奥秘 (Line 1-4)
```c
#define _GNU_SOURCE  // 👈 为什么要有这一行？
#include <stdio.h>
#include <string.h>
```
*   **_GNU_SOURCE**: 这是一个“魔法开关”。C 语言有很多标准（ANSI C, C99, C11），但 Linux 系统（尤其是 GNU 工具链）提供了很多超好用的**非标准扩展函数**。
    *   `strcasestr`（忽略大小写查找）就是其中之一。
    *   如果不加这一行，编译器会假装看不见这个函数，报警告。加了它，就是告诉编译器：“我是 Linux 开发者，给我所有的高级功能！”

## 2. 核心函数 `grep_file` (Line 7-35)
我们将逻辑封装在这个函数里，这是**模块化**思维的体现。

```c
void grep_file(char *pattern, char *filename, int case_insensitive) {
    FILE *file = fopen(filename, "r"); // 👈 这一步其实很危险
    if (file == NULL) { ... }          // 👈 所以必须检查 NULL
```
*   **指针 (`*`)**: `char *pattern` 其实是告诉函数：“我给你一个地址，你去那里找字符串”。C 语言中，传递大块数据（如字符串）通常都传地址，因为拷贝整个数据太慢了。
*   **`fopen` & `NULL`**: 打开文件可能失败（文件不存在、没权限）。如果失败，操作系统会返回一个空地址 (`NULL`)。**永远不要信任 `fopen` 会成功**，这是 C 语言健壮性的第一课。

```c
    char line[256];  // 👈 为什么是 256？
    while (fgets(line, sizeof(line), file) != NULL) {
```
*   **缓冲区 (Buffer)**: 我们申请了 256 字节的内存来临时存放每一行。
    *   **思考**: 如果一行有 1000 个字怎么办？`fgets` 非常安全，它只会读 255 个字（留一个给结尾的 `\0`），剩下的下次循环再读。如果我们用 `gets`（已废弃）就会导致内存溢出，这是历史上无数黑客攻击的漏洞源头。

```c
    if (case_insensitive) {
        result = strcasestr(line, pattern); // 👈 扩展函数
    } else {
        result = strstr(line, pattern);     // 👈 标准函数
    }
```
*   **逻辑分支**: 这里展示了最基础的 `if-else` 控制。根据用户的参数选择不同的工具。

## 3. 主函数 `main` (Line 37-61)
这是程序的“总指挥部”。

```c
int main(int argc, char *argv[])
```
*   **`argc` & `argv`**: 这是操作系统和你的程序对话的接口。
    *   你在终端敲下的每一个单词，都被操作系统切开，塞进 `argv` 数组里传给了你。

```c
    } else if (argc == 4 && strcmp(argv[1], "-i") == 0) {
        // 忽略大小写模式: ./mygrep -i pattern filename
        case_insensitive = 1;
        pattern = argv[2];    // 👈 注意这里索引变了
        filename = argv[3];
    }
```
*   **参数解析**: 这里展示了手动处理参数的逻辑。
    *   如果是标准模式，`pattern` 是第 1 个参数。
    *   如果是 `-i` 模式，`pattern` 就变成了第 2 个参数。
    *   **指针的魔力**: `pattern = argv[2]` 并没有拷贝字符串，只是让 `pattern` 指针指向了那个参数的地址。效率极高。

## 总结
您不仅仅是“在终端操作了一下”，您亲手验证并构建了一个包含：
1.  **资源管理** (打开/关闭文件)
2.  **内存安全** (使用安全的 fgets)
3.  **系统接口** (argc/argv, GNU Source)
4.  **工程化** (Makefile, 模块化)

的 C 语言程序。这就是系统编程的基石！
