#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE 1024
#define MAX_ARGS 64
#define DELIMITERS " \t\r\n\a"

void type_prompt() {
    printf("myshell> ");
}

char **split_line(char *line) {
    int position = 0;
    char **tokens = malloc(MAX_ARGS * sizeof(char*));
    char *token;

    if (!tokens) {
        fprintf(stderr, "myshell: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, DELIMITERS);
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= MAX_ARGS) {
            fprintf(stderr, "myshell: too many arguments\n");
            exit(EXIT_FAILURE);
        }

        token = strtok(NULL, DELIMITERS);
    }
    tokens[position] = NULL;
    return tokens;
}

int launch_process(char **args) {
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0) {
        // Child process
        if (execvp(args[0], args) == -1) {
            perror("myshell");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("myshell");
    } else {
        // Parent process
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}

// === Built-in Commands ===

int myshell_cd(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "myshell: expected argument to \"cd\"\n");
    } else {
        // chdir 是系统调用，改变当前进程的工作目录
        if (chdir(args[1]) != 0) {
            perror("myshell");
        }
    }
    return 1; // 继续运行
}

int myshell_exit(char **args) {
    return 0; // 返回 0，告诉 main 函数停止循环
}

// 调度器：区分是内置命令还是外部程序
int execute(char **args) {
    if (args[0] == NULL) {
        return 1;
    }

    // 检查是否是内置命令
    if (strcmp(args[0], "cd") == 0) {
        return myshell_cd(args);
    }
    if (strcmp(args[0], "exit") == 0) {
        return myshell_exit(args);
    }

    // 都不是，那就启动新进程
    return launch_process(args);
}

int main() {
    char line[MAX_LINE];
    char **args;
    int status = 1;

    while (status) {
        type_prompt();
        
        if (fgets(line, MAX_LINE, stdin) == NULL) {
            printf("\nBye!\n");
            break;
        }

        args = split_line(line);

        if (args[0] != NULL) {
            // 用 execute 替代 launch_process
            status = execute(args);
        }

        free(args);
    }
    return 0;
}
