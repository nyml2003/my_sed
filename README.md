```bash
# readme
# 编译项目 cmake
mkdir build && cd build && cmake .. && make && cd ..
# 运行项目
## 1. 输入参数，Usage: ./build/sed <input> <output.md> <output.err> <output.ll>，但是没配置好
./build/sed
## 2. （推荐）在tests目录下按照格式编写测试用例，然后运行脚本
cd build && make test

# 清理项目
rm -rf build
```