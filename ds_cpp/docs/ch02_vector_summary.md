## 2.1 数据结构概念
- 数据结构 : 数据项的结构化集合，结构化可理解为数据项之间的逻辑关系
- 逻辑关系分类 : 
    - 线性结构 : 列表向量 (寻位置访问) 和 向量 (寻秩访问)
    - 半线性结构 : 二叉树
    - 非线性结构 : 图
## 2.2 分摊时间复杂度 & 平均时间复杂度
- 分摊时间(amortized running time): 纵观连续的足够多次操作，并将其间总体所需的运行时间分摊至各次操作
- 平均时间(average running time): 假定各种输入实例的出现符合某种概率分布之后, 进而估算出的加权复杂度均值
- 分摊和平均的区别:
```text

```
- Vector 加倍扩容的时间复杂度:
```text
翻倍扩容:
默认 为 N 个空间, 扩容 n 次 为 capacity(n) = 2^nN, 分配的内存总次数满足下式:
2N + 4N + ... + capacity(n) < 2 * capacity(n)
分配内存总次数分摊到最后分配的空间为:
2 * capacity(n) / capacity(n) = O(1) 

递增扩容:
默认 为 N 个空间, 扩容 n 次 为 capacity(n) = (n+1)N, 分配的内存总次数满足下式:
2N + 3N + ... + capacity(n) < (n - 1) capacity(n)
分配内存总次数分摊到最后分配的空间为:
(n - 1) capacity(n) / capacity(n) = O(n)
```

# 2. 查找
- 二分查找 ( 三分支 ) 所有元素查找长度 : C(k) = 3 * (k - 1) * 2^(k -1) + 1 (某次查找元素个数为 2 ^ k - 1)
- 斐波那契数查找
```c++
rank fibSearch(const T &e, rank lo, rank hi){
    Fib fib(hi-lo); // 获取不小于 hi-lo的 第一个fib数
    while(lo<hi){
        while(hi-lo<fib.get()) fib.pre(); // 使fib数<= hi-lo 最多循环两次 
        int mi=lo+fib.get()-1;  // 以 fib数为中点下标
        if(e<_elem[mi]) hi=mi;
        else lo=mi+1;
    }
    return --lo;	
}
```

# 3. 排序
- 排序算法 ： 
    - 按存储特点分为内部排序和外部排序
    - 按输入特点分为离线和在线排序
    - 按体系分为串行和并行排序
- 比较式算法可根据 比较树 得出叶节点为 n，则树高最少为log2(n)，树高即比较过程中的比较次数。在比较排序过程中存在三分支情况则树高最少为 h >= log3(n!) = log3e∙ln(n!) >= nlogn (斯特林公式)