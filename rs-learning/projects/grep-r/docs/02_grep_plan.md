# Build Your Own Grep (Rust 语言版) - 实施计划

从 C 语言切换到 Rust，您将体验到“从手动挡换到自动挡”的感觉，同时享受到坦克的安全性。

## 目标
构建 `grep-r`，功能与 C 版本一致，但使用 Rust 的现代特性。

## 核心差异 (C vs Rust)

| 特性 | C 语言 | Rust |
| :--- | :--- | :--- |
| **构建系统** | Makefile (手动) | Cargo (全自动) |
| **内存管理** | malloc/free (手动) | Ownership (自动回收) |
| **错误处理** | 检查 NULL/返回码 | `Result` 枚举 (必须处理) |
| **字符串** | `char*` (危险) | `String` / `&str` (安全 UTF-8) |

## 阶段规划

### 第一阶段：Cargo 起飞 (Setup)
*   **目标**: 创建项目，理解 `Cargo.toml`。
*   **知识点**: `cargo new`, `cargo run`。

### 第二阶段：参数与文件 (Input & IO)
*   **目标**: 读取用户输入的文件路径和搜索词，并读取文件内容。
*   **挑战**: Rust 的 `std::env::args()` 返回的是迭代器，文件读取可能失败（返回 Result）。我们将展示如何优雅地处理这些“可能失败”的情况。

### 第三阶段：搜索与借用 (Search & Borrowing)
*   **目标**: 实现 core search logic。
*   **知识点**: 为什么我们在搜索时可以用 `containing`？如何遍历 `lines()`？以及 Rust 核心概念：**不可变借用**。

### 第四阶段：结构化与错误处理 (Refactoring)
*   **目标**: 使用 `struct` 来组织代码，而不是把变量散落在 `main` 里。使用 `Box<dyn Error>` 统一错误类型。

## 验证计划
依然使用 `poem.txt` 进行测试，确保行为与 C 版本一致。
