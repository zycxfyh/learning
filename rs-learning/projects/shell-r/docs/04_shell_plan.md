# Build Your Own Shell (Rust 语言版) - 实施计划

在 C 语言中，我们接触了底层的 `fork`/`exec`。
在 Rust 中，我们要学习**抽象 (Abstraction)** 的力量。

Rust 的标准库 `std::process::Command` 封装了底层的肮脏细节，让我们能更安全、更符合人体工程学地管理进程。

## 目标
创建一个功能等同于 `shell-c` 的 Rust Shell，但代码更现代、更安全。

## 核心概念对比

| 概念 | C 语言 (手动挡) | Rust (自动挡) |
| :--- | :--- | :--- |
| **无限循环** | `while(1)` | `loop {}` |
| **输入读取** | `fgets` (要在意 buffer 大小) | `read_line(&mut string)` (自动扩容) |
| **字符串切割** | `strtok` (破坏原字符串) | `split_whitespace()` (返回迭代器) |
| **进程创建** | `fork()` + `execvp()` | `Command::new()` |
| **等待子进程** | `waitpid()` | `child.wait()` |
| **错误处理** | `perror` + `exit` | `Result<T, E>` |

## 阶段规划

### 第一阶段：Rust 风格的循环 (The Loop)
*   **挑战**: `print!` 宏不会自动刷新缓冲区，需要手动 `flush` 才能立即看到提示符。
*   **工具**: `std::io` 本地库。

### 第二阶段：优雅的解析 (Parsing)
*   **亮点**: 不需要像 C 那样数指针。Rust 的 `split_whitespace` 直接把字符串切成单词流。
*   **所有权**: 需要注意字符串的所有权问题。

### 第三阶段：Command 结构体 (Execution)
*   **核心**: 使用 `std::process::Command` 构建命令。
*   **执行**: `spawn()` (生成子进程) vs `output()` (收集输出)。我们要用 `spawn()` 并等待。

### 第四阶段：内置命令 (Builtins)
*   **实现**: `cd` 使用 `std::env::set_current_dir`。

## 准备好了吗？
这次你会发现，Rust 代码写起来像脚本语言一样行云流水，但底层依然是高性能的二进制！
