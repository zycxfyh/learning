#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8080
#define MAX_CLIENTS 5
#define BUFFER_SIZE 1024

// 客户端处理函数
void* handle_client(void* arg) {
    int client_socket = *(int*)arg;
    char buffer[BUFFER_SIZE];
    int bytes_read;

    printf("新客户端连接 (socket: %d)\n", client_socket);

    // 发送欢迎消息
    char* welcome_msg = "欢迎连接到C语言TCP服务器!\n请输入消息:\n";
    send(client_socket, welcome_msg, strlen(welcome_msg), 0);

    while ((bytes_read = recv(client_socket, buffer, BUFFER_SIZE - 1, 0)) > 0) {
        buffer[bytes_read] = '\0';
        printf("收到消息: %s", buffer);

        // 简单的回声服务器
        char response[BUFFER_SIZE];
        if (strcmp(buffer, "quit\n") == 0 || strcmp(buffer, "exit\n") == 0) {
            strcpy(response, "再见!\n");
            send(client_socket, response, strlen(response), 0);
            break;
        } else if (strcmp(buffer, "time\n") == 0) {
            time_t now = time(NULL);
            strcpy(response, ctime(&now));
            send(client_socket, response, strlen(response), 0);
        } else if (strcmp(buffer, "hello\n") == 0) {
            strcpy(response, "你好！我是C语言编写的服务器。\n");
            send(client_socket, response, strlen(response), 0);
        } else {
            sprintf(response, "服务器收到: %s", buffer);
            send(client_socket, response, strlen(response), 0);
        }
    }

    if (bytes_read == 0) {
        printf("客户端断开连接 (socket: %d)\n", client_socket);
    } else if (bytes_read < 0) {
        perror("接收数据失败");
    }

    close(client_socket);
    free(arg);
    return NULL;
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    pthread_t thread_id;

    printf("=== C语言TCP服务器演示 ===\n\n");

    // 创建socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("socket创建失败");
        exit(1);
    }

    // 设置服务器地址
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;  // 监听所有网络接口
    server_addr.sin_port = htons(PORT);

    // 绑定socket
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind失败");
        close(server_socket);
        exit(1);
    }

    // 监听连接
    if (listen(server_socket, MAX_CLIENTS) < 0) {
        perror("listen失败");
        close(server_socket);
        exit(1);
    }

    printf("服务器启动成功，监听端口 %d...\n", PORT);
    printf("支持的命令:\n");
    printf("  hello  - 问候\n");
    printf("  time   - 获取服务器时间\n");
    printf("  quit/exit - 断开连接\n");
    printf("  其他消息 - 回声响应\n\n");

    while (1) {
        // 接受客户端连接
        client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_len);
        if (client_socket < 0) {
            perror("accept失败");
            continue;
        }

        printf("接受来自 %s:%d 的连接\n",
               inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        // 为每个客户端创建新线程
        int* client_sock_ptr = malloc(sizeof(int));
        *client_sock_ptr = client_socket;

        if (pthread_create(&thread_id, NULL, handle_client, (void*)client_sock_ptr) != 0) {
            perror("线程创建失败");
            close(client_socket);
            free(client_sock_ptr);
        }

        // 分离线程，让它自行清理
        pthread_detach(thread_id);
    }

    close(server_socket);
    return 0;
}