- 有序型对于列表查找提升不大, 原因是 call by position 增加了基础成本
- 哨兵节点header和trailer可以有效覆盖空表插入和单节点删除的情况
- 通过调用对象实现遍历算法 :
```c++
template <typename T>
class Visit{
public:
	void operator()(const T &e){
		std::cout<<e<<" ";
	}
};
template <typename T>
class Increase{
public:
	void operator()(T &e){ ++e; }
};
Visit<int> visit;
Increase<int> increase;
```

- 数据访问局部型原理, 对于列表的访问往往集中于某一特定的子集可采取自适应列表 :  元素一旦接受访问随机移动到最前端, 新元素自动插入到最前端
```c++
T &operator[](rank r) const { // 自适应访问
    auto p=header->succ;
    while(0<r--)	p=p->succ;
    movetoFront(p);
    return p->data;
}
void movetoFront(LNP(T) p){
    if(vaild(p))
        insertAfter(header, remove(p));
}
```

- 逆序对间距不超过K则插入排序运行时间为O(nk), 一般情况下k与n成线性正比关系, 准确的来说比较次数为每个节点的逆序前驱总和I 总运行时间为O(n+I)
- selectSort()算法的改进
```c++
	void selectionSort(LNP(T) p, int n){
		LNP(T) head=p->pred; // 设定区间 
		LNP(T) tail=p;for(int i=0; i<n; ++i) tail=tail->succ;
		while(1<n){
			LNP(T) m=selectMax(head->succ, n); // 每趟第一个节点会改变 找到最大节点位置
			// if(m!=tail->pred)  // 优化次数=循环节个数总和-1=O(lnn)<O(n) 得不偿失 
			auto temp=m->data;  // 只交换数据项不涉及到内存分配
			m->data=tail->pred->data;
			tail->pred->data=temp;
			tail=tail->pred; // 更改区间
			--n; // 缩小范围
		}
	}
```

> 将最大值移动到末尾等价与该值所属的循环节长度-1

- 插入排序和归并排序的联系 : 当T(n)=T(c)+T(n-c)+O(n) c=1时, 相当于每次将最左元素插入到已排序的右边序列中
- 链表的三种reverse : 对称交换data, 交换前后驱指针的值, 改变前后驱指针的值
- 循环列表 : 约瑟夫环问题 O(n\*mod(k,n)) k为每次向后索引的次数

