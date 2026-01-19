# Cargo.toml - Rust 项目的身份证

如果说 `Makefile` 是手动挡（要自己写每一条编译指令），那么 `Cargo.toml` 就是自动驾驶的导航中心。

```toml
[package]
name = "grep-r"        # 项目名称
version = "0.1.0"      # 版本号
edition = "2021"       # Rust 版本 (2021 是目前主流)

# 依赖列表 (Dependencies)
# 在 C 语言里，引入第三方库非常麻烦（下载源码、编译、链接...）
# 在 Rust 里，只需要在这里加一行字。
[dependencies]
# 比如以后我们要用正则表达式，只需加：
# regex = "1.5"
```

## 核心概念：Crate
在 Rust 世界里，每一个项目（或者库）都叫一个 **Crate**（板条箱）。
Cargo 会自动处理所有的下载、编译、链接工作。你只需要关注代码本身。
