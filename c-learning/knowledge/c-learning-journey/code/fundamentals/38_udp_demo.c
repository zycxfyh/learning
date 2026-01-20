#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8081
#define BUFFER_SIZE 1024

// UDP服务器函数
void udp_server() {
    int server_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];
    int bytes_read;

    printf("UDP服务器启动...\n");

    // 创建UDP socket
    server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_socket < 0) {
        perror("UDP socket创建失败");
        return;
    }

    // 设置服务器地址
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // 绑定socket
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("UDP bind失败");
        close(server_socket);
        return;
    }

    printf("UDP服务器监听端口 %d\n", PORT);

    while (1) {
        // 接收数据
        bytes_read = recvfrom(server_socket, buffer, BUFFER_SIZE - 1, 0,
                            (struct sockaddr*)&client_addr, &client_addr_len);

        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';
            printf("收到来自 %s:%d 的消息: %s",
                   inet_ntoa(client_addr.sin_addr),
                   ntohs(client_addr.sin_port), buffer);

            // 处理消息
            char response[BUFFER_SIZE];
            if (strcmp(buffer, "quit\n") == 0 || strcmp(buffer, "exit\n") == 0) {
                strcpy(response, "再见!\n");
            } else if (strcmp(buffer, "ping\n") == 0) {
                strcpy(response, "pong\n");
            } else {
                sprintf(response, "UDP服务器收到: %s", buffer);
            }

            // 发送响应
            sendto(server_socket, response, strlen(response), 0,
                  (struct sockaddr*)&client_addr, client_addr_len);
        }
    }

    close(server_socket);
}

// UDP客户端函数
void udp_client(const char* server_ip) {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    char message[BUFFER_SIZE];

    printf("UDP客户端启动...\n");

    // 创建UDP socket
    client_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_socket < 0) {
        perror("UDP socket创建失败");
        return;
    }

    // 设置服务器地址
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0) {
        perror("无效的IP地址");
        close(client_socket);
        return;
    }

    printf("连接到UDP服务器 %s:%d\n", server_ip, PORT);

    // 发送和接收循环
    while (1) {
        printf("请输入消息 (quit/exit 退出): ");
        fflush(stdout);

        if (fgets(message, BUFFER_SIZE, stdin) == NULL) {
            break;
        }

        // 发送消息
        sendto(client_socket, message, strlen(message), 0,
              (struct sockaddr*)&server_addr, sizeof(server_addr));

        // 如果是退出命令，直接退出
        if (strcmp(message, "quit\n") == 0 || strcmp(message, "exit\n") == 0) {
            break;
        }

        // 接收响应
        int bytes_read = recvfrom(client_socket, buffer, BUFFER_SIZE - 1, 0, NULL, NULL);
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';
            printf("服务器响应: %s", buffer);
        } else {
            perror("接收失败");
            break;
        }
    }

    close(client_socket);
}

int main(int argc, char* argv[]) {
    printf("=== C语言UDP网络编程演示 ===\n\n");

    if (argc < 2) {
        printf("用法:\n");
        printf("  服务器模式: %s server\n", argv[0]);
        printf("  客户端模式: %s client <服务器IP>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "server") == 0) {
        udp_server();
    } else if (strcmp(argv[1], "client") == 0) {
        if (argc < 3) {
            printf("客户端模式需要指定服务器IP地址\n");
            return 1;
        }
        udp_client(argv[2]);
    } else {
        printf("无效的模式。使用 'server' 或 'client <IP>'\n");
        return 1;
    }

    return 0;
}