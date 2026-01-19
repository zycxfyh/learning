#include <stdio.h>
#include <string.h>

// 1. 定义结构体 (Structure Definition)
// 考试常考：注意分号不能丢！
struct Student {
    int id;
    char name[20];
    float score;
};

int main() {
    // 2. 初始化结构体变量
    struct Student s1 = {1001, "Alice", 92.5};
    
    // 3. 访问成员 (.)
    printf("学生1: %d, 姓名: %s, 成绩: %.1f\n", s1.id, s1.name, s1.score);

    // 修改内容
    s1.score = 95.0;
    strcpy(s1.name, "Bob"); // 字符串赋值要用 strcpy

    // 4. 结构体数组
    struct Student class_room[2] = {
        {1002, "Cindy", 88.0},
        {1003, "David", 76.5}
    };

    printf("\n--- 班级信息 ---\n");
    for (int i = 0; i < 2; i++) {
        printf("ID: %d, Name: %s\n", class_room[i].id, class_room[i].name);
    }

    return 0;
}
