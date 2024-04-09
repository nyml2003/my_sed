# 编译项目 cmake
```
mkdir build && cd build && cmake .. && make && cd ..
```
# 运行项目
```
./build/sed
```
# 清理项目
```
rm -rf build
```

# 用例

## 变量声明
**type**
- **int** : 32位整数
- **float** : 32位浮点数
- **bool** : 布尔值

```
[type] [variable] ;
```
```
example,其中>>代表输入
>>int i1=1,i_2____321312=100;
>>int i5=31232+21312;
>>bool b1= i1 == i5;
>>bool b2= i1 !=i5;
>>float f1=1.002,f2=f1+133.0;
>>list;
---Variable List---

name: b1
value: false

name: b2
value: true

name: f1
value: 1.002

name: f2
value: 134.002

name: i1
value: 1

name: i5
value: 52544

name: i_2____321312
value: 100

-----------
```
## 赋值表达式

右结合，有副作用的表达式，值为最后一个表达式的值

```
[variable] = [value] ;
```

```
example,其中>>代表输入
>>int a,b,c,d,e;
>>a=b=c=d=e=100;
100
>>list;
---Variable List---

name: a
value: 100

name: b
value: 100

name: c
value: 100

name: d
value: 100

name: e
value: 100

-----------
```

## 表达式计算
```
example,其中>>代表输入
>>(1 + 2) * 3 == 3 * (2 + 1) ;
true
```

## 类型检查
```
example,其中>>代表输入
>>int a = (1 + 2) * 3 == 3 * (2 + 1);
INFO: the type of variable a is int
INFO: the type of value is bool
Warning: type mismatch,the statement will be ignored
>>int a;
>>int a;
Warning: Variable a already exists,the statement will be ignored
>>a=true;
INFO: the type of variable a is int
INFO: the type of value is bool
Warning: type mismatch,the statement will be ignored
>>a+true;
Warning: Invalid operation: int + bool,the statement will be ignored
>>a==1;
false
```

## 其余报错
```
example,其中>>代表输入
>>b;
INFO: Variable: b
Warning: Variable b not found,the statement will be ignored
>>b=1;
Warning: the identifier b is not declared,the statement will be ignored
1
```