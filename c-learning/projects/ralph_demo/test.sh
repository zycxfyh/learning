#!/bin/bash
# 编译并运行 main.c
gcc main.c -o main 2>/dev/null
if [ $? -ne 0 ]; then
    echo "编译失败！"
    exit 1
fi

./main
exit $?
