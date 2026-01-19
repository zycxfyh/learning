# 使用轻量级的 Alpine Linux 作为基础镜像
# Alpine 非常小（只有几 MB），但功能足够强大
FROM alpine:latest

# 安装构建工具
# build-base 包含了 gcc, make, libc-dev 等核心开发工具
RUN apk add --no-cache build-base clang vim

# 设置工作目录
WORKDIR /app

# 把容器当成一个一直运行的虚拟机
# 这样我们就可以随时进入容器写代码
CMD ["/bin/sh"]
