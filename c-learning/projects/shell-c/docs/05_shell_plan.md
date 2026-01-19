# Build Your Own Shell (C 语言版) - 实施计划

Grep 让我们学会了文件 IO，现在我们要挑战更底层的**进程控制**。
为了确保系统安全（毕竟我们要写一个能“夺舍”的 Shell），我们将在**容器 (Container)** 内进行开发。

## 0. 安全沙箱 (Safety First)
*   **工具**: 使用 `Podman` (Linux 原生容器引擎，兼容 Docker)。
*   **机制**: 我们会创建一个隔离的开发环境。哪怕你在 Shell 里写了 `rm -rf /`，也只会删掉容器里的东西，不会炸掉您的电脑。

## 核心概念 (系统调用)

这一关全是硬核知识：

1.  **`fork()` (分身术)**
    *   Shell 本身是一个进程。为了运行 `ls`，它不能把自己变没了。
    *   所以它必须先复制出一个一模一样的自己（子进程）。
2.  **`execvp()` (夺舍)**
    *   子进程虽然也是 Shell，但它现在的任务是变成 `ls`。
    *   它调用 `exec`，把自己的脑子（内存）换成 `ls` 的代码。
3.  **`waitpid()` (在此等候)**
    *   父进程（原来的 Shell）必须暂停，等待子进程运行结束，然后再弹出下一个提示符 `> `。

## 阶段规划

### 第一阶段：安全接入 (Container Setup)
*   **目标**: 编写 `Dockerfile`，构建一个包含 GCC/Clang 的开发镜像。
*   **指令**: `podman build -t c-shell-dev .` 和 `podman run -it -v $(pwd):/app c-shell-dev`。

### 第二阶段：无限循环 (The Loop)
*   **目标**: 打印 `myshell> `，读取用户输入，直到用户按 Ctrl+D。

### 第三阶段：大卸八块 (Parsing)
*   **目标**: 这里没有 Rust 的 `split_whitespace()`。我们用 `strtok` 切割字符串。

### 第四阶段：生死轮回 (Execution)
*   **目标**: 实现 `fork` + `exec` + `wait` 的标准三部曲。这是本项目的核心。

### 第五阶段：内置命令 (Builtins)
*   **目标**: 实现 `cd`。
