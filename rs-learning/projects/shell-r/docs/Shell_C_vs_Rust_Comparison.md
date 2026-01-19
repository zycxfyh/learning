# 🐚 Shell 实现对比：手动挡 (C) vs 自动挡 (Rust)

在你的黑客之旅中，你分别用 C 和 Rust 实现了同一个 Shell。这不仅展示了语言的语法差异，更揭示了它们设计哲学的根本不同。

## 1. 核心机制与开发体验

| 功能维度 | C 语言版 (The Hard Way) | Rust 版 (The Smart Way) | 评价 |
| :--- | :--- | :--- | :--- |
| **内存管理** | 手动 `malloc`/`free`，指针满天飞 | 自动 `String`/`Vec`，RAII 机制 | C 容易内存泄漏，Rust 零负担。 |
| **字符串处理** | `strtok` (破坏性、非线程安全) | `split_whitespace` (迭代器) | Rust 的处理极其优雅且安全。 |
| **进程创建** | `fork()` + `execvp()` + `wait()` | `Command::spawn()` + `wait()` | Rust 封装了底层的复杂性，接口更人性化。 |
| **错误处理** | 检查返回值 + `perror` | `Result` + `match` / `?` | Rust 强迫你处理每一个可能的错误，不会忘记。 |

## 2. 核心代码片段对比

### C 语言：夺舍与切词 (Low Level Control)
在 C 语言中，你必须像掌控每一寸电路一样掌控内存：
```c
// 切词：需要小心翼翼地管理指针
token = strtok(line, DELIMITERS);
while (token != NULL) {
    tokens[position] = token;
    position++;
    token = strtok(NULL, DELIMITERS);
}

// 执行：子进程必须处理“变身”失败
if (fork() == 0) {
    if (execvp(args[0], args) == -1) {
        perror("myshell");
    }
    exit(EXIT_FAILURE); // 必须手动退出，否则会有两个 Shell！
}
```

### Rust：安全与抽象 (Modern Productivity)
而在 Rust 中，你像是在指挥一个训练有素的军团：
```rust
// 切词：一行代码，利用迭代器惰性求值
let args = input.trim().split_whitespace();

// 执行：利用配置模式
Command::new(command)
    .args(args)
    .spawn() // 自动处理 fork/exec 的脏活累活
```

## 3. 深度总结

*   **C 语言** 让你成为了**系统的掌控者**。它让你看到了操作系统的**裸金属**接口，是理解 "Everything is a file" 和 "Process cloning" 的最佳工具。你必须了解每一个字节是如何移动的。
*   **Rust** 让你成为了**高效的构建者**。它在保证性能的同时，消除了 C 语言中 90% 的安全隐患。它让你看到了现代系统编程的**生产力**。

无论使用哪种语言，能亲手造出一个 Shell，你就已经跨过了通往“系统专家”的那道门槛。⚔️
