SEP 2 - IR设计
=======================

## allocate

allocate [scope] [name] 

```
allocate global c
```
对应
```c
int c;
```


```
allocate f a
```
```c
int f(){
    int a;
}
```


## assign

assign [scope] [name] [value]

```
assign global c 1
```
对应
```c
int c = 1;
```
