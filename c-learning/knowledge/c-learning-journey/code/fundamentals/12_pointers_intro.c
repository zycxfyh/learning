#include <stdio.h>

int main() {
    int age = 20;    // 声明并定义一个变量 age
    int *p;          // 声明一个“指针变量” p (准备装地址的盒子)

    p = &age;        // 把 age 的地址取出来，放进 p 里面

    printf("=== 指针基础实验 ===\n");
    printf("1. 变量 age 的值是: %d\n", age);
    printf("2. 变量 age 的内存地址是: %p\n", (void*)&age); // %p 用来打印地址
    printf("3. 指针变量 p 里面装的数值是: %p\n", (void*)p);
    
    printf("\n=== 跨空取物 (解引用) ===\n");
    // *p 就像是顺着 p 里的门牌号去敲门，看看里面住的是谁
    printf("4. 通过指针 p 找到的值是: %d\n", *p);

    // 改变 *p 就像是改变了那个房间里住的人
    *p = 25;
    printf("5. 修改后，age 的值由于通过指针被改成了: %d\n", age);

    return 0;
}
