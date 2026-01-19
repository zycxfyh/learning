# ⚔️ 终极对决：C vs Rust

恭喜！您已经用两种系统编程语言实现了同一个工具。这是极其宝贵的经验。
让我们来看看这两者的核心区别。

## 1. 运行方式 (The Trap)
您刚才遇到了一个小坑：
*   ❌ `cargo run -i pattern file` -> Cargo 以为 `-i` 是给它自己的指令。
*   ✅ `cargo run -- -i pattern file` -> **`--`** 告诉 Cargo：“后面的参数你别管，全传给我的程序”。

## 2. 代码对比

| 维度 | C 语言 (手动挡) | Rust (自动挡) |
| :--- | :--- | :--- |
| **内存管理** | `char line[256]` (必须小心越界) | `String` (自动扩容，不用管) |
| **文件读取** | `fopen` + `expected NULL` + `fgets` | `fs::read_to_string` + `expect` |
| **错误处理** | 容易忘记检查 check return value | 编译器强迫你处理 (`Result`) |
| **代码组织** | 散落在 `main` 里 | 封装在 `struct Config` 里 |
| **编译工具** | 复杂的 `Makefile` | 一键 `cargo run` |

## 3. 核心感悟
*   **C 语言** 让你理解**底层**：什么是内存，什么是指针。
*   **Rust** 让你构建**工程**：如何安全、高效、模块化地开发。

您现在的 `c-learning-journey` 库里已经收录了这两份代码。以后无论面试还是工作，这都是您扎实基础的证明！
