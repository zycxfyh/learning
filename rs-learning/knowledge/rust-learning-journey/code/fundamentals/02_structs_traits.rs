struct User {
    username: String,
    email: String,
    active: bool,
}

// 类似于 C++ 的 Class 方法，但在 Rust 中叫 impl
impl User {
    // 构造函数 (不仅仅是 malloc)
    fn new(name: &str, email: &str) -> User {
        User {
            username: String::from(name),
            email: String::from(email),
            active: true,
        }
    }

    // 方法 (即 self 参数)
    fn introduce(&self) {
        println!("Hi, I am {} ({})", self.username, self.email);
    }
}

// Trait 类似于 Java 的 Interface 或 C++ 的 Abstract Base Class
trait Printable {
    fn format(&self) -> String;
}

impl Printable for User {
    fn format(&self) -> String {
        format!("[User: {}]", self.username)
    }
}

fn main() {
    println!("=== 2. 结构体与方法 (Structs & Impl) ===");
    
    // C 语言风格：先定义，再赋值
    // Rust 风格：表达式构造
    let user1 = User::new("Hacker", "admin@linux.com");
    user1.introduce();

    println!("Trait Output: {}", user1.format());
}
