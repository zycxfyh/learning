fn main() {
    println!("=== 1. 所有权转移 (Move Semantics) ===");
    let s1 = String::from("Hello, Rust!");
    let s2 = s1; 
    // println!("{}", s1); // ❌ 编译报错！s1 的所有权已经“移动”给了 s2
    println!("s1 已经失效, s2 是: {}", s2);

    println!("\n=== 2. 借用 (Borrowing) ===");
    let s3 = String::from("I am Borrowed");
    let len = calculate_len(&s3); // 传入引用 (&)，这是“借”，不是“送”
    println!("'{}' 的长度是 {}", s3, len); // ✅ s3 依然有效

    println!("\n=== 3. 可变借用 (Mutable Borrow) ===");
    let mut s4 = String::from("Hello");
    change_string(&mut s4); // 借出去修改
    println!("修改后的字符串: {}", s4);
}

fn calculate_len(s: &String) -> usize {
    s.len()
} // s 离开作用域，但它只是借来的，所以原值不会被销毁

fn change_string(s: &mut String) {
    s.push_str(", World");
}
