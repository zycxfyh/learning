#include <stdio.h>
#include <string.h>

// 1. 定义结构体：就像是设计一张“个人信息登记表模板”
struct Student {
    char name[50];
    int age;
    float score;
};

int main() {
    // 2. 根据模板创建变量（实例化）
    struct Student s1;

    // 3. 使用点号 . 来访问里面的成员
    strcpy(s1.name, "小明"); // 给字符数组赋值不能直接用 =，得用 strcpy
    s1.age = 18;
    s1.score = 95.5;

    printf("=== 学生信息登记 ===\n");
    printf("姓名: %s\n", s1.name);
    printf("年龄: %d\n", s1.age);
    printf("成绩: %.1f\n", s1.score);

    // 4. 指针与结构体（终极进阶提示）
    struct Student *ptr = &s1;
    // 当我们用指针指向结构体时，习惯用 -> 来访问成员
    printf("\n通过指针访问姓名: %s\n", ptr->name);

    return 0;
}
