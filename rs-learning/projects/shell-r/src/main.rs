use std::io::{self, Write};
use std::process::Command;

fn main() {
    println!("Welcome to Rusty Shell!");

    loop {
        print!("myshell> ");
        io::stdout().flush().expect("Failed to flush stdout");

        let mut input = String::new();
        match io::stdin().read_line(&mut input) {
            Ok(n) => {
                if n == 0 {
                    println!("\nBye!");
                    break;
                }

                // Phase 2: Parsing (优雅的切词)
                // trim() 去掉首尾空白
                // split_whitespace() 返回一个迭代器，自动处理多个空格
                let mut parts = input.trim().split_whitespace();
                
                // 获取第一个单词作为命令
                let command = match parts.next() {
                    Some(cmd) => cmd,
                    None => continue, // 如果用户只按了回车，跳过
                };

                // 剩下的就是参数
                let args = parts;

                match command {
                    "cd" => {
                        // 默认如果没有参数，就去根目录 (简单起见)
                        // args.next() 获取下一个参数
                        let new_dir = args.peekable().peek().map_or("/", |x| *x);
                        let root = std::path::Path::new(new_dir);
                        if let Err(e) = std::env::set_current_dir(&root) {
                            eprintln!("{}", e);
                        }
                    },
                    "exit" => return, // 退出循环，程序结束
                    command => {
                         // Phase 3: Execution (标准库的力量)
                        match Command::new(command)
                            .args(args)
                            .spawn() 
                        {
                            Ok(mut child) => {
                                child.wait().expect("Failed to wait on child");
                            }
                            Err(e) => {
                                eprintln!("myshell: {}", e);
                            }
                        }
                    }
                }
            }
            Err(error) => {
                println!("Error reading input: {}", error);
                break;
            }
        }
    }
}
