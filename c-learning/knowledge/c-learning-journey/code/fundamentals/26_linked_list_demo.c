#include <stdio.h>
#include <stdlib.h>

// 定义链表节点结构体
struct Node {
    int data;           // 数据域
    struct Node* next;  // 指针域，指向下一个节点
};

// 函数声明
struct Node* create_node(int data);
void append(struct Node** head, int data);
void insert_at_beginning(struct Node** head, int data);
void delete_node(struct Node** head, int key);
void print_list(struct Node* head);
void free_list(struct Node** head);

int main() {
    struct Node* head = NULL;  // 初始化空链表

    printf("=== C语言链表演示 ===\n\n");

    // 创建链表并添加节点
    printf("1. 创建链表并添加节点:\n");
    append(&head, 10);
    append(&head, 20);
    append(&head, 30);
    print_list(head);

    // 在开头插入节点
    printf("\n2. 在开头插入节点 5:\n");
    insert_at_beginning(&head, 5);
    print_list(head);

    // 删除节点
    printf("\n3. 删除节点 20:\n");
    delete_node(&head, 20);
    print_list(head);

    // 再次添加一些节点
    printf("\n4. 再次添加节点 25 和 35:\n");
    append(&head, 25);
    append(&head, 35);
    print_list(head);

    // 释放链表内存
    free_list(&head);
    printf("\n5. 链表已释放\n");

    return 0;
}

// 创建新节点
struct Node* create_node(int data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    if (new_node == NULL) {
        printf("内存分配失败!\n");
        exit(1);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

// 在链表末尾添加节点
void append(struct Node** head, int data) {
    struct Node* new_node = create_node(data);

    if (*head == NULL) {
        *head = new_node;
        return;
    }

    struct Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}

// 在链表开头插入节点
void insert_at_beginning(struct Node** head, int data) {
    struct Node* new_node = create_node(data);
    new_node->next = *head;
    *head = new_node;
}

// 删除指定值的节点
void delete_node(struct Node** head, int key) {
    struct Node* temp = *head;
    struct Node* prev = NULL;

    // 如果头节点就是要删除的节点
    if (temp != NULL && temp->data == key) {
        *head = temp->next;
        free(temp);
        return;
    }

    // 寻找要删除的节点
    while (temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }

    // 如果没找到
    if (temp == NULL) {
        printf("未找到值为 %d 的节点\n", key);
        return;
    }

    // 删除节点
    prev->next = temp->next;
    free(temp);
}

// 打印链表
void print_list(struct Node* head) {
    if (head == NULL) {
        printf("链表为空\n");
        return;
    }

    struct Node* current = head;
    printf("链表内容: ");
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// 释放整个链表的内存
void free_list(struct Node** head) {
    struct Node* current = *head;
    struct Node* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}