# 这就是 Makefile！它定义了一系列规则来告诉电脑怎么编译程序。

# 1. 定义变量
# CC 表示我们要用的编译器 (C Compiler)
CC = clang
# CFLAGS 表示编译选项 (C Flags)
# -Wall: 打开所有警告 (Warning All)，帮我们发现潜在 bug
# -g:    生成调试信息 (Debug)，方便后续调试
CFLAGS = -Wall -g

# 2. 定义目标 (Target)
# 格式是：
# 目标文件: 依赖文件
# [TAB] 命令

# 默认目标：输入 'make' 时执行这个
all: mygrep

# 编译 mygrep
# 依赖 main.c
mygrep: main.c
	$(CC) $(CFLAGS) main.c -o mygrep

# 3. 清理目标
# 输入 'make clean' 时执行，用来删掉编译出来的文件
clean:
	rm -f mygrep
