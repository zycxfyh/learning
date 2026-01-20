#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main(int argc, char* argv[]) {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    char message[BUFFER_SIZE];

    if (argc != 2) {
        printf("用法: %s <服务器IP地址>\n", argv[0]);
        printf("例如: %s 127.0.0.1\n", argv[0]);
        return 1;
    }

    printf("=== C语言TCP客户端演示 ===\n\n");

    // 创建socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("socket创建失败");
        exit(1);
    }

    // 设置服务器地址
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    // 将字符串IP地址转换为网络字节序
    if (inet_pton(AF_INET, argv[1], &server_addr.sin_addr) <= 0) {
        perror("无效的IP地址");
        close(client_socket);
        exit(1);
    }

    // 连接到服务器
    printf("正在连接到 %s:%d...\n", argv[1], PORT);
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("连接失败");
        close(client_socket);
        exit(1);
    }

    printf("连接成功!\n\n");

    // 接收服务器的欢迎消息
    int bytes_read = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';
        printf("%s", buffer);
    }

    // 主循环：发送和接收消息
    while (1) {
        printf("请输入消息 (quit/exit 退出): ");
        fflush(stdout);

        if (fgets(message, BUFFER_SIZE, stdin) == NULL) {
            break;
        }

        // 发送消息到服务器
        if (send(client_socket, message, strlen(message), 0) < 0) {
            perror("发送失败");
            break;
        }

        // 如果是退出命令，直接退出
        if (strcmp(message, "quit\n") == 0 || strcmp(message, "exit\n") == 0) {
            break;
        }

        // 接收服务器响应
        bytes_read = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';
            printf("服务器响应: %s", buffer);
        } else if (bytes_read == 0) {
            printf("服务器断开连接\n");
            break;
        } else {
            perror("接收失败");
            break;
        }
    }

    printf("客户端退出\n");
    close(client_socket);
    return 0;
}