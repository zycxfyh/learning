#!/bin/bash
# Ralph Loop 控制脚本
# 它会不断运行测试，直到代码修复通过

PROJECT_DIR=$(pwd)
TEST_SCRIPT="./test.sh"
AI_TOOL="ollama" # 默认使用本地 Ollama

echo "🚀 Ralph Loop 已启动..."

while true; do
    echo "------------------------------------------"
    echo "🔎 正在运行测试..."
    
    # 运行测试并捕获输出和状态
    TEST_OUTPUT=$($TEST_SCRIPT 2>&1)
    TEST_STATUS=$?
    
    if [ $TEST_STATUS -eq 0 ]; then
        echo "✅ 测试通过！Ralph Loop 任务完成。"
        break
    else
        echo "❌ 测试失败。准备调用 AI 进行修复..."
        echo "错误信息: $TEST_OUTPUT"
        
        # 记录到 Git，这样 AI 可以看到之前的“业”
        git add .
        git commit -m "Ralph Loop: 测试失败，准备修复" --allow-empty
        
        # 构造给 AI 的 Prompt
        PROMPT="你是一个 C 语言专家。项目中的 main.c 测试失败了。
报错信息如下：
$TEST_OUTPUT

请分析 main.c 的代码并修复它。只输出修复后的完整代码，不要有其他解释。
代码路径：main.c"

        # 这里模拟调用本地模型 (如果用户有 Ollama)
        if command -v ollama >/dev/null 2>&1; then
            echo "🤖 正在调用本地 Ollama (qwen2.5-coder)..."
            # 这是一个简化的调用示例
            FIXED_CODE=$(curl -s -X POST http://localhost:11434/api/generate -d "{
                \"model\": \"qwen2.5-coder\",
                \"prompt\": \"$PROMPT\",
                \"stream\": false
            }" | python3 -c "import sys, json; print(json.load(sys.stdin)['response'])")
            
            if [ ! -z "$FIXED_CODE" ]; then
                echo "$FIXED_CODE" > main.c
                echo "♻️ 代码已更新，进入下一轮循环。"
            else
                echo "⚠️ AI 返回内容为空，循环中止。"
                break
            fi
        else
            echo "❌ 未检测到 Ollama。请手动执行修复或配置 AI 工具。"
            echo "当前为演示环境，你可以让 Antigravity 帮你完成修复循环。"
            break
        fi
    fi
    
    sleep 2
done
