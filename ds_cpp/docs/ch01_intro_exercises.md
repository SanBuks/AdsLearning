## 1-3 逆序对

- n 个元素逆序对最大为 m = n(n - 1)/2
- 完全逆序的 n 个数的数组中每个元素需要交换 2m / n 次

## 1-6 封底估算

- 1 day = 10^5s
- 100 year = 3 * 10^9s
- age of universal = 10^21s
- 10^9 flo = 1s

## 1-7 循环次数

```c++
// 1. O(2013) 分别于 2012, 4025, 6039 等数取得接近于 2013 的循环次数
for (int i = 0; i < n; i += 1 + n / 2013) { }
// 2. 算术平均, 几何平均
// 3. (n * n) % 5
// 4. 除 fib(0), fib(1), fib(2), fib(12) 都不会是平方数
```

## 1-8 O(logn) 不关注底数

- $log_{a}n = log_{a}b \times log_{b}n$

## 1-9 O(lnn) 与 O(n^c)

- lnn 的渐进增长慢于任何一个幂函数 n^ϵ
- $n \rightarrow \infty, \exist\epsilon > 0, lnn < \epsilon n \rightarrow lnlnn < \epsilon lnn \rightarrow lnn < n^\epsilon $

## 程序清单

| 问题序号       | 文件             |
|------------|----------------|
| 1-12       | #count_ones.h  |
| 1-13, 1-14 | #power2.h      |
| 1-16       | #subset.h      |
| 1-22       | #fib.h         |
| 1-23       | #hanoi.h       |
| 1-24       | #cover.h       |
| 1-25       | #gcd.h         |
| 1-26       | #shirft.h      |
| 1-32.cc    | #cycle_times.h |


- 1-19, 20, 21
- 1-27
- 1-28
- $\sum_{k=1}^{n}k2^{-k}d$ 求和