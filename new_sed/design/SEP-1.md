SEP 1 - 支持函数参数列表
=======================

## 1. 函数声明,定义和调用

对应的概念分别是declaration, definition和call。函数声明是指函数的原型声明，定义是指函数的实现，调用是指函数的调用。

---

### 函数声明

在进行函数声明时,需要记录函数的返回值类型,参数列表中每个参数的类型。

**feature**
一个函数可以被声明多次, 而且函数声明里的参数名可以不同或者为空, 但是参数类型必须一致。
比如
```c
int foo(int a, int b);
int foo(int, int);
int foo(int, int c);
```
都是对同一个函数的声明。

实现方案:
1. std::vector<std::map<std::string, std::vector<Enumeration::ValueType> >> functions;


int f(int a, int b);

void func_114514(int f, int a, int b);

其中func_11414是自动生成的不会重复的函数名。


f(a,b) -> f(ret,nullptr,a,b);

参数0用于记录返回值
参数1用于记录调用者

int c=1;
int f(int a, int b){
    return c+a+b;
}
int main(){
    int a = f(1,2);
}

var c in global // 分配栈上的空间
global.c = 1
Label global.f
a = %attr2
b = %attr3
c = %attr1
%10 = %attr1
%11 = %10 + b
%attr0 = %11

global:
    int c=1;
    f(int ret, void* global, int a, int b){
        return global->c+a+b; // 通过查找上下文来获取c的类型
    }
    main(int ret, void* global){
        int ret;
        f(ret,global,1,2);
    }