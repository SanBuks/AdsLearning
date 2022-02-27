# 1. 计算机与算法
## 1.1 背景
- 1946年 ENIAC 开启了现代电子数字计算机的时代, 计算机科学诞生
- 计算机科学其核心是研究**计算方法与过程的规律和技巧**, 不仅仅是计算机本身, 其中计算机只是**帮助计算和解决问题的工具**
 
> 12段直角法的绳索 和 几何中的尺规都可视为一种计算机
> 根据问题使用工具求解问题的步骤可视为算法

## 1.2 算法
- 算法定义 : 基于特定的**计算模型**(计算工具), 为了解决某一个信息处理问题而设计的一个**指令序列** ()
- 算法的 5 种基本特性 : (注意, 算法基本特性不对结果正确负责)
    - 输入与输出
    - 确定性
    - 可行性 
    - 有穷性 (问题的可计算性)

> 针对有穷性引入 Hailstone 问题 (PTA 3N+1 问题) 尚未证明其有穷性, 因此得出 **程序 $\neq$ 算法**  
> 程序仅是一组计算机可以执行的指令, 在符合算法+数据结构的要求下才能正确解决问题

- 评价算法好坏标准 :
    - 正确性 (可以因对多种输入规模, 得出预期结果)
    - 高效型 (关键 : 关乎计算效率)
    - 健壮性 
    - 可读性
    - 可拓展性

# 2. 算法分析
## 2.1 分析手段
- 分为两个方面 :
	- 证明正确性
	- 运行时间空间的复杂度度量
> 任何一次算法中, 对内存的操作次数都不会多于基本操作次数, 所以只注重于时间的空间度量

- 使用渐进分析的原因 : 
	- 对于用算法A来解决具体事件 $p$ 的度量 $T_A(p)$ 因具体事件变化而频繁改变 
	- 用规模划分等价类, 用针对事件规模 $n$ 的度量$T_A(n)$ 因输入规模不一而改变
	- 最终引入渐进分析

## 2.2 渐进分析
- 注重时间复杂度总体的变化趋势和增长速度的分析策略与方法. 通常关注最坏情况, 其中通用 3 种记号 :
- $T(n) = O(f(n))$ : $n\rightarrow\infty,\exist c>0,有T(n)\leq c f(n)$
- $T(n) = \Omega(f(n))$ : $n\rightarrow\infty,\exist c,有 T(n)\geq c f(n)$
- $T(n) = \Theta(f(n))$ : $n\rightarrow\infty,\exist c_1,c_2,有c_1f(n)\leq T(n) \leq c_2f(n)$
- 2 种性质: 忽略常数项 忽略低次项

## 2.3 计算模型
- 定义 : 从复杂的机器和语言类型等抽象出一个理想的模型进行评价, 忽略次要因素 :
- 图灵机 : 
    - 有限长的纸带
    - 有限种类的字符表
    - 读写头
    - 状态
    - 函数 [ 条件(当前状态q, 读到字符c) => 动作(新字符d, 转向L/R, 新状态p) ]  (h为终止状态) 
- RAM(Random Access Machine) : 
    - 无限的寄存器
    - 固定的指令 如 寻址指令 判定指令 转向指令 (类似汇编指令)

# 3. 度量尺度
> 由于c++高级程序语言在一定程度上等价于RAM模型可以通过代码来大致估算时间复杂度

## 3.1 高效解
- $O(1)$ : 常数项复杂度, 与输入规模无关
- $O(ln n)$ : 对数复杂度, 不标明底是因为底可以互相转换比如
```c++
// 计算非负整数二进制位数中1的个数
// count_ones.cc
// 1. 逐位计算1的个数 O(n) = O(2^r)
// 2. 按照1的实际个数计算 O(logn) = O(r)
// 3. 通过位运算归并计算 O(loglogn) = O(logr)
int __builtin_popcount(unsigned int n); // (libc)
```

## 3.2 有效解
- $O(n)$ : 线性复杂度
- $O(n^c)$ : 多项式复杂度 比如
```c++
// 冒泡排序
// bubble_sort.cc
// 1. 利用标志符提前判断是否已经排序
// 2. 记录最后排序位置跳过局部排序元素
```

## 3.3 难解 
- $O(2^n)$ : 指数复杂度 随n增长极快 比如
```c++
// 计算 2^n, n 的二进制长度为 r
// power2.cc
// 1. 通过 n 的数量逐一乘以2 O(n) = O(2^r)
// 以 n 的数值为基准的复杂度为 O(n) 是 伪线性复杂度
// 以 n 的比特位数作为基准则为 O(2^r)

// 2. 利用 n 的比特位数来计算 O(logn) = O(r)
// 以 n 的数值为基准的复杂度为 O(logn) 是 伪对数复杂度
// 以 n 的比特位数作为基准则为 O(r)
```

- $NPC$问题 : 不存在多项式时间内解决的方法 比如 美国选举票数问题

## 3.4 增长速度 
$$O(1),O(loglogn),O(logn),O(\sqrt{n}),O(n),O(nloglogn),O(nlogn),O(n^2),O(n^c),O(2^n)$$ 


# 4. 算法分析手段
## 4.1 正确性分析
- 不变性 : 拿冒泡排序举例, 不变性在于经过k轮扫描, 最大的k位数必然就位
- 单调性 : 拿冒泡排序举例, 单调性在于经过k轮扫描, 问题规模必然缩减至n-k

## 4.2 迭代
- 迭代定义 ：用变量的原值推算出新的值，比如循环
- 迭代分析 : (通过计算循环中的次数)
    - 等比(几何)级数 : $\sum_{k=0}^{n}a^k = O(a^{n})$
    - 幂方级数 : $\sum_{k=0}^{n}n^k = O(n^{k+1})$
    - 等差级数 : $\sum_{k=0}^{n}kd=O(n^2)$
    - 收敛级数 : 先判断为收敛级数 , 比如 $\sum_{k=1}^{n}\frac{1}{2^k}=O(1)$
    - 调和级数 : $\sum_{k=1}^n\frac{1}{k}=\Theta(logn)$
    - 对数级数 : $\sum_{k=1}^nlog(k)=\Theta(nlogn)$
    - 或者 通过画出 x-y 轴图像来判断

## 4.3 递归
- 递归定义 :  将问题分为若干个问题调用自身来解决
- 递归类别 :
    - 减而治之 : 线性递归 如 数组求和每次将规模分为 1 和 n-1
    - 分而治之 : 将问题分成互不重合的若干个小问题如
- 基本要素 : 递归基 和 递归方向
- 减少成本 : 通过栈来模拟递归, 尾递归转换为迭代
- 分析方法 : 递归跟踪, 递归方程


## 4.4 动态规划
- 递归形式 记忆法
- 迭代形式 状态转移方程
```c++
// 求解第 n 个 fib 数
// fib
// 1. 二分法 递归版 O(2^n)
// 2.1 状态转移 迭代版 O(n)
// 2.2 状态转移 递归版 O(n)
```
> fib(n) = ($\frac{\Phi^{n} - \hat{\Phi}^{n}}{\sqrt{5}}$) = $O(\Phi^n)$

## 4.5 抽象数据类型
- ADT = 数据模型和定义在模型上的一组操作
- DS = 基于某种特定语言, 实现 ADT 得一整套算法
- 个人理解 : 
    - abstrct data type 类比 整型
    - data struct 类比 int a; 中的 a
    - 可以把数据结构称作抽象数据类型的实例化 或者 抽象数据类型称做抽象数据结构

# 5. 习题总结
## n个元素逆序对为 n ( n - 1 ) / 2

## 封底估算
- $一天 \approx 10^5s$
- $100年 \approx 3\times10^9s$
- $宇宙至今 \approx 10^{21}s$
- $10^9flo\approx 1s$

## $ln(n)$ 的渐进增长慢于任何次数的幂函数 $n^ϵ$
- $n \rightarrow \infty, \exist\epsilon > 0, lnn < \epsilon n \Rightarrow lnlnn < \epsilon lnn \Rightarrow lnn < n^\epsilon $

## 其他总结

7, 19, 20

| 文件 | 描述 |
| --- | --- |
| fib | 22. Fibonacci数列类 |
| hanoi.cc | 23. Hanoi问题 |
| cover | 24. L形积木覆盖缺口棋盘问题 |
| gcd.cpp |	25. 中华更相减损术 |
| shift.cc | 26.循环位移 |
| ackermann.cc | 27. 超限归纳法 |
| hailstone.cc | 29. 无法证明有穷非算法 |
| cycle_times.cc | 32. 计算循环次数 |