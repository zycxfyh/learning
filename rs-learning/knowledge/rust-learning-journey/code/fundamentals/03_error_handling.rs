use std::fs::File;
use std::io::ErrorKind;

fn main() {
    println!("=== 3. 错误处理 (Result & Option) ===");

    // 1. Option: 替代 C 语言中的 NULL
    let numbers = vec![10, 20, 30];
    let fourth = numbers.get(3); // 越界不会崩溃，而是返回 None

    match fourth {
        Some(val) => println!("第四个数是: {}", val),
        None => println!("第四个数不存在 (如果是 C 语言这里已经 Segmentation Fault 了)"),
    }

    // 2. Result: 替代 C 语言中的 -1 或 errno
    let f = File::open("hello.txt");

    let _f = match f {
        Ok(file) => file,
        Err(error) => match error.kind() {
            ErrorKind::NotFound => {
                println!("文件没找到，像 C 一样处理...");
                // 在这里可以创建文件
                panic!("File not found!");
            },
            other_error => panic!("Other error: {:?}", other_error),
        },
    };
    
    // 简写模式：unwrap (出错了直接崩) 或 expect (自定义崩溃信息)
    // let f2 = File::open("hello.txt").expect("Failed to open");
}

fn divide(a: f64, b: f64) -> Result<f64, String> {
    if b == 0.0 {
        Err(String::from("Division by zero"))
    } else {
        Ok(a / b)
    }
}
