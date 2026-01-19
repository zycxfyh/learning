use std::env;
use std::fs;

// 定义一个结构体来存放配置，这样代码更清晰
struct Config {
    pattern: String,
    filename: String,
    case_insensitive: bool,
}

impl Config {
    // 构造函数：解析参数并返回一个 Config 对象
    fn new(args: &[String]) -> Config {
        if args.len() < 3 {
            panic!("not enough arguments"); // 简化处理，直接 panic
        }

        let mut pattern = args[1].clone();
        let mut filename = args[2].clone();
        let mut case_insensitive = false;

        // 如果用户输入了 4 个参数，且第二个是 -i
        if args.len() > 3 && args[1] == "-i" {
            case_insensitive = true;
            pattern = args[2].clone();
            filename = args[3].clone();
        }

        Config {
            pattern,
            filename,
            case_insensitive,
        }
    }
}

fn main() {
    let args: Vec<String> = env::args().collect();
    
    // 使用 Config::new 来整理参数
    let config = Config::new(&args);

    println!("Searching for '{}' in '{}'", config.pattern, config.filename);

    let content = fs::read_to_string(config.filename)
        .expect("Something went wrong reading the file");

    println!("-- Grep Results --");

    for (index, line) in content.lines().enumerate() {
        let line_to_check = if config.case_insensitive {
            line.to_lowercase() // 变小写
        } else {
            line.to_string()
        };

        let pattern_to_check = if config.case_insensitive {
            config.pattern.to_lowercase() // 变小写
        } else {
            config.pattern.clone()
        };

        if line_to_check.contains(&pattern_to_check) {
            println!("{}: {}", index + 1, line);
        }
    }
}
