# 1. 面试基本信息
## 1.1 介绍自己
- STAR : 简短项目背景, 自己完成的工作, 工作是怎么做的, 自己的贡献
- 其他问题 : 最大的问题是什么怎么解决, 学到了什么, 怎么解决冲突
- 换工作原因 : 方向不感兴趣, 提高能力, 弥补短板 (不说老板苛刻, 同事难相处, 加班多, 工资低)
- 介绍自己最近看的书籍和学习东西
- 最后提问与应聘职位相关的技术问题

### 1.2 基本素质
- 沟通能力 : 不要不懂装懂, 答非所问, 一定要大胆提问, 弄清问题所在
- 解决问题能力 : 数据结构算法, 具体例子分析(先找死路画图找规律), 分解复杂问题, 优化测量复杂度
- 软件工程能力 : 代码风格, 单元测试, 代码的鲁棒性, Debug能力
- 学习能力 : 迁移学习之前问题的方法

# 2. 编程基础
## 2.1 语言相关
### 四种类型转换关键字
- static\_cast : 用于不包含底层const的其他任何类型转换
- const\_cast : 用于去掉常量性质对象
- reinterpret\_cast : 改变对象数据的位解释
- dynamic\_cast : 主要用于多态类指针或引用转换为其派生类的指针或引用

### 虚表机制
- 空类大小理论为零, 为了在内存中表达这个对象一般分配1B
- 类中的数据成员与函数分离, 否则指向函数的指针会额外占据对象空间
- 只含有虚函数的类占据8B(机器字长), 会保存虚函数表的指针
- 同类的不同对象拥有指针指向相同的虚表
- 通过 `g++ -fdump-lang-class -c test.cpp` 输出相关类分配内容
```bash
(gdb) set print asm-demangle on
(gdb) set print demangle on
(gdb) x/300xb 0x400b40
# x command, which dumps memory to the screen. I ask it to print 300 bytes in hex format, starting at 0x400b40.

Vtable for Base
Base::_ZTV4Base: 4 entries
0     (int (*)(...))0      # 虚表开头 空项
8     (int (*)(...))(& _ZTI4Base)  # typeinfo 内容
16    (int (*)(...))Base::test1   # 第一个虚函数地址
24    (int (*)(...))Base::test2   # 第二个虚函数地址

# 如果虚函数被继承则保存相同的地址

Class Base
   size=24 align=8
   base size=24 base align=8
Base (0x0x7fbd7b85e960) 0
    vptr=((& Base::_ZTV4Base) + 16)  # 指向第一个虚函数

#_ZTV is a prefix for vtable
#_ZTS is a prefix for type-string (name)
#_ZTI is for type-info
```

### 常量字符串优化
```c++
const char *p1="123";
const char *p2="123";

char a1[]="123";
char a2[]="123";

assert(p2==p1);
assert(a1!=a2);
```


### 其他
- 结构体对齐问题

