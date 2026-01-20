#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

// 定义常量
#define MAX_HISTORY 100
#define PI 3.141592653589793
#define E  2.718281828459045

// 历史记录结构体
typedef struct {
    char expression[100];
    double result;
    time_t timestamp;
} HistoryEntry;

// 全局变量
HistoryEntry history[MAX_HISTORY];
int history_count = 0;

// 函数声明
double add(double a, double b);
double subtract(double a, double b);
double multiply(double a, double b);
double divide(double a, double b);
double power(double base, int exp);
long long factorial(int n);
double sine(double angle);
double cosine(double angle);
double tangent(double angle);
double logarithm(double x);
double square_root(double x);
double absolute(double x);
void show_menu();
int get_choice();
double get_number(const char* prompt);
void perform_calculation(int choice);
void clear_input_buffer();
void show_help();
void add_to_history(const char* expr, double result);
void show_history();
void clear_history();

int main() {
    printf("================================\n");
    printf("     🌟 高级C语言计算器 🌟\n");
    printf("================================\n");
    printf("这是您在C语言基础阶段的完整项目！\n");
    printf("支持基本运算、科学计算和历史记录！\n\n");

    int choice;

    do {
        show_menu();
        choice = get_choice();

        if (choice >= 1 && choice <= 12) {
            perform_calculation(choice);
        } else if (choice != 0) {
            printf("❌ 无效选择，请重新选择！\n\n");
        }

    } while (choice != 0);

    printf("感谢使用高级C语言计算器！再见！👋\n");
    return 0;
}

// 显示菜单
void show_menu() {
    printf("\n======== 高级计算器菜单 ========\n");
    printf("1. ➕ 加法\n");
    printf("2. ➖ 减法\n");
    printf("3. ✖️  乘法\n");
    printf("4. ➗ 除法\n");
    printf("5. 🔢 幂运算 (x^y)\n");
    printf("6. ❗ 阶乘 (n!)\n");
    printf("7. 📊 批量计算 (连续输入)\n");
    printf("8. 🧮 数学常量\n");
    printf("9. 🔬 科学计算\n");
    printf("10. 📚 帮助说明\n");
    printf("11. 📜 计算历史\n");
    printf("12. 🗑️  清空历史\n");
    printf("0. 🚪 退出\n");
    printf("================================\n");
}

// 获取用户选择
int get_choice() {
    int choice;
    printf("请选择操作 (0-12): ");
    while (scanf("%d", &choice) != 1) {
        printf("❌ 输入无效！请输入数字 (0-12): ");
        clear_input_buffer();
    }
    clear_input_buffer(); // 清除换行符
    return choice;
}

// 获取数字输入
double get_number(const char* prompt) {
    double num;
    printf("%s", prompt);
    while (scanf("%lf", &num) != 1) {
        printf("❌ 输入无效！%s", prompt);
        clear_input_buffer();
    }
    clear_input_buffer();
    return num;
}

// 执行计算
void perform_calculation(int choice) {
    double a, b, result;
    int exp, n;
    char expr[100];

    switch (choice) {
        case 1: // 加法
            a = get_number("请输入第一个数: ");
            b = get_number("请输入第二个数: ");
            result = add(a, b);
            sprintf(expr, "%.2f + %.2f", a, b);
            add_to_history(expr, result);
            printf("✅ %.2f + %.2f = %.2f\n", a, b, result);
            break;

        case 2: // 减法
            a = get_number("请输入被减数: ");
            b = get_number("请输入减数: ");
            result = subtract(a, b);
            sprintf(expr, "%.2f - %.2f", a, b);
            add_to_history(expr, result);
            printf("✅ %.2f - %.2f = %.2f\n", a, b, result);
            break;

        case 3: // 乘法
            a = get_number("请输入第一个数: ");
            b = get_number("请输入第二个数: ");
            result = multiply(a, b);
            sprintf(expr, "%.2f × %.2f", a, b);
            add_to_history(expr, result);
            printf("✅ %.2f × %.2f = %.2f\n", a, b, result);
            break;

        case 4: // 除法
            a = get_number("请输入被除数: ");
            b = get_number("请输入除数: ");
            if (b == 0) {
                printf("❌ 错误：除数不能为零！\n");
                return;
            }
            result = divide(a, b);
            sprintf(expr, "%.2f ÷ %.2f", a, b);
            add_to_history(expr, result);
            printf("✅ %.2f ÷ %.2f = %.2f\n", a, b, result);
            break;

        case 5: // 幂运算
            a = get_number("请输入底数: ");
            exp = (int)get_number("请输入指数 (整数): ");
            result = power(a, exp);
            sprintf(expr, "%.2f ^ %d", a, exp);
            add_to_history(expr, result);
            printf("✅ %.2f ^ %d = %.2f\n", a, exp, result);
            break;

        case 6: // 阶乘
            n = (int)get_number("请输入一个非负整数: ");
            if (n < 0) {
                printf("❌ 错误：阶乘只能计算非负整数！\n");
                return;
            }
            if (n > 20) {
                printf("❌ 错误：阶乘结果太大，无法计算！\n");
                return;
            }
            long long fact_result = factorial(n);
            sprintf(expr, "%d!", n);
            add_to_history(expr, (double)fact_result);
            printf("✅ %d! = %lld\n", n, fact_result);
            break;

        case 7: // 批量计算
            printf("📊 批量计算模式 (输入 'q' 退出)\n");
            char operation;
            while (1) {
                printf("请输入运算 (如: 2 + 3): ");
                if (scanf("%lf %c %lf", &a, &operation, &b) != 3) {
                    clear_input_buffer();
                    char quit_check[10];
                    scanf("%s", quit_check);
                    if (strcmp(quit_check, "q") == 0 || strcmp(quit_check, "Q") == 0) {
                        printf("退出批量计算模式\n");
                        break;
                    }
                    printf("❌ 输入格式错误！请使用格式: 数 运算符 数\n");
                    continue;
                }

                switch (operation) {
                    case '+':
                        result = add(a, b);
                        sprintf(expr, "%.2f + %.2f", a, b);
                        add_to_history(expr, result);
                        printf("✅ %.2f\n", result);
                        break;
                    case '-':
                        result = subtract(a, b);
                        sprintf(expr, "%.2f - %.2f", a, b);
                        add_to_history(expr, result);
                        printf("✅ %.2f\n", result);
                        break;
                    case '*':
                    case 'x':
                    case 'X':
                        result = multiply(a, b);
                        sprintf(expr, "%.2f × %.2f", a, b);
                        add_to_history(expr, result);
                        printf("✅ %.2f\n", result);
                        break;
                    case '/':
                        result = divide(a, b);
                        sprintf(expr, "%.2f ÷ %.2f", a, b);
                        add_to_history(expr, result);
                        printf("✅ %.2f\n", result);
                        break;
                    default:
                        printf("❌ 不支持的运算符！\n");
                        result = 0; // 避免未初始化
                }
                clear_input_buffer();
            }
            break;

        case 8: // 数学常量
            printf("🧮 常用数学常量:\n");
            printf("  π (圆周率) ≈ %.8f\n", PI);
            printf("  e (自然对数) ≈ %.8f\n", E);
            printf("  √2 (2的平方根) ≈ %.8f\n", sqrt(2));
            printf("  φ (黄金比例) ≈ %.8f\n", (1 + sqrt(5)) / 2);
            printf("  ln(2) ≈ %.8f\n", log(2));
            break;

        case 9: // 科学计算
            printf("🔬 科学计算器\n");
            printf("  1. sin(x)   2. cos(x)   3. tan(x)\n");
            printf("  4. log(x)   5. √x       6. |x|\n");
            printf("  0. 返回主菜单\n");
            int sci_choice;
            printf("请选择科学函数: ");
            sci_choice = get_choice();
            if (sci_choice >= 1 && sci_choice <= 6) {
                double input = get_number("请输入数值: ");
                char expr[50];
                switch (sci_choice) {
                    case 1:
                        result = sine(input);
                        sprintf(expr, "sin(%.2f°)", input);
                        add_to_history(expr, result);
                        printf("✅ sin(%.2f°) = %.6f\n", input, result);
                        break;
                    case 2:
                        result = cosine(input);
                        sprintf(expr, "cos(%.2f°)", input);
                        add_to_history(expr, result);
                        printf("✅ cos(%.2f°) = %.6f\n", input, result);
                        break;
                    case 3:
                        result = tangent(input);
                        sprintf(expr, "tan(%.2f°)", input);
                        add_to_history(expr, result);
                        printf("✅ tan(%.2f°) = %.6f\n", input, result);
                        break;
                    case 4:
                        if (input <= 0) {
                            printf("❌ 错误：对数函数的输入必须为正数！\n");
                            return;
                        }
                        result = logarithm(input);
                        sprintf(expr, "log(%.2f)", input);
                        add_to_history(expr, result);
                        printf("✅ log(%.2f) = %.6f\n", input, result);
                        break;
                    case 5:
                        if (input < 0) {
                            printf("❌ 错误：平方根的输入不能为负数！\n");
                            return;
                        }
                        result = square_root(input);
                        sprintf(expr, "√%.2f", input);
                        add_to_history(expr, result);
                        printf("✅ √%.2f = %.6f\n", input, result);
                        break;
                    case 6:
                        result = absolute(input);
                        sprintf(expr, "|%.2f|", input);
                        add_to_history(expr, result);
                        printf("✅ |%.2f| = %.6f\n", input, result);
                        break;
                }
            }
            break;

        case 10: // 帮助说明
            show_help();
            break;

        case 11: // 计算历史
            show_history();
            break;

        case 12: // 清空历史
            clear_history();
            break;
    }
}

// 数学运算函数
double add(double a, double b) { return a + b; }
double subtract(double a, double b) { return a - b; }
double multiply(double a, double b) { return a * b; }
double divide(double a, double b) { return a / b; }

// 幂运算 (使用循环实现)
double power(double base, int exp) {
    if (exp == 0) return 1.0;
    if (exp < 0) return 1.0 / power(base, -exp);

    double result = 1.0;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}

// 阶乘 (递归实现，使用long long防止溢出)
long long factorial(int n) {
    if (n == 0 || n == 1) return 1;
    return n * factorial(n - 1);
}

// 科学计算函数
double sine(double angle) { return sin(angle * PI / 180.0); } // 角度制
double cosine(double angle) { return cos(angle * PI / 180.0); } // 角度制
double tangent(double angle) { return tan(angle * PI / 180.0); } // 角度制
double logarithm(double x) { return log10(x); }
double square_root(double x) { return sqrt(x); }
double absolute(double x) { return fabs(x); }

// 帮助说明
void show_help() {
    printf("\n📚 计算器使用帮助\n");
    printf("================================\n");
    printf("基本运算:\n");
    printf("  1-4: 加减乘除运算\n");
    printf("  5: 幂运算 (底数^指数)\n");
    printf("  6: 阶乘 (n! ，n≤20)\n");
    printf("\n高级功能:\n");
    printf("  7: 批量计算 - 连续输入表达式\n");
    printf("  8: 数学常量 - 显示常用常数\n");
    printf("  9: 科学计算 - 三角函数、对数等\n");
    printf("  10: 帮助说明 - 显示此帮助\n");
    printf("  11: 计算历史 - 查看历史记录\n");
    printf("  12: 清空历史 - 清除所有历史\n");
    printf("\n输入格式:\n");
    printf("  批量计算: 2 + 3 或 5 * 2\n");
    printf("  退出批量: 输入 q 或 Q\n");
    printf("  角度单位: 科学计算使用角度制\n");
    printf("================================\n");
}

// 历史记录功能
void add_to_history(const char* expr, double result) {
    if (history_count < MAX_HISTORY) {
        strcpy(history[history_count].expression, expr);
        history[history_count].result = result;
        history[history_count].timestamp = time(NULL);
        history_count++;
    }
}

void show_history() {
    if (history_count == 0) {
        printf("📜 暂无计算历史\n");
        return;
    }

    printf("\n📜 计算历史记录\n");
    printf("================================\n");
    for (int i = 0; i < history_count; i++) {
        printf("%d. %s = %.6f\n", i + 1,
               history[i].expression, history[i].result);
    }
    printf("================================\n");
}

void clear_history() {
    history_count = 0;
    printf("✅ 计算历史已清空\n");
}

// 清除输入缓冲区
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}