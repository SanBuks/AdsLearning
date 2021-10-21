# 第三章 列表
### 1. 概述
### 2. 数据部分
```c++
// 1. ListNode
typedef int rank;
# define LNP(T) ListNode<T>*
template<typename T>
class ListNode{
	friend class List<T>;
private:
	T data;  // 存取数据
	LNP(T) pred;  // 前驱指针
	LNP(T) succ;  // 后继指针
public:
	ListNode(){}
	ListNode(T e, LNP(T) p=nullptr, LNP(T) s=nullptr):
		data(e), pred(p), succ(s){}
	
	LNP(T) insertAsPred(const T &e); // 前方插入
	LNP(T) insertAsSucc(const T &e); // 后方插入
};

// 2. List
template<typename T>
class List{
private:
	LNP(T) header;  // 记录头部哨兵结点的指针
	LNP(T) trailer;  // 记录尾部哨兵节点的指针
	int _size; // 记录总大小

	void init();// 初始化 首尾哨兵 首前和尾后都为nullptr
	void copyNodes(LNP(T) p, int n);  // 自p指针所指开始 复制n个节点
public:
	List(){ init(); }
	List(const List<T> &L, rank r, int n); // 复制自L[r] 起的n项
    ~List();
	T remove(LNP(T) p);  // 删除p所指的节点
	int clear(); // 清空节点返回个数

// 简单接口
	rank size()const { return _size; }
	bool empty() const { return _size<=0; }
	LNP(T) first()const { return header->succ; }
	LNP(T) last() const { return trailer->pred; }
	bool vaild(LNP(T) p){ return p&&(trailer!=p)&&(header!=p); } // 判断p是否在显示范围内
	LNP(T) insertAsFirst(const T &e){ ++_size; return header->insertAsSucc(e); }
	LNP(T) insertAsLast(const T &e){ ++_size; return trailer->insertAsPred(e); }
	LNP(T) insertBefore(LNP(T) p, const T &e){ ++_size; return p->insertAsPred(e); }
	LNP(T) insertAfter(LNP(T) p, const T &e){ ++_size; return p->insertAsSucc(e); }

// 一般信息查询
	T &operator[](rank r);  // 返回下标 O(n) 
	const T &operator[](rank r) const;  // 对对象是否为const进行重载
    void traverse(void (*visit)(const T &e)); // 遍历
	int disorder() const; // 返回紧邻无序对的数量
	LNP(T) selectMax(LNP(T) p, int n);// 返回 包括p在内的后n个节点中最大值位置

	LNP(T) find(const T &e, int n, LNP(T) p) const; // 在 p 的n个真前驱中寻找e的位置 找不到返回nullptr
	LNP(T) find(const T &e) const; // 全局查找
	LNP(T) search(const T &e, int n, LNP(T) p) const; // 在p的n个真前驱且包括左边界查找<=e的最大秩节点
	LNP(T) search(const T &e);  // 全局区间查找
};
```

### 3. 唯一化
```c++
	int deduplicate(){  // 无序唯一化 最好:O(n) 最坏:O(n^2)
		if(_size<2) return 0;
		int oldSize=_size;
		LNP(T) p=header; // 通过p遍历一边list 
		rank r=0; // p 的真前驱个数 
		while((p=p->succ)!=trailer){
			LNP(T) q=find(p->data, r, p);
			if(q){ // 找到了则删除
				remove(q); 
				--r; 
				p=p->pred;  // 为了保留在原地
			}
			else ++r; // 没找到则前驱数+1
		}
		return oldSize-_size;
	}
	int uniqufy(){  // 有序唯一化
		if(_size<2) return 0;
		int oldSize=_size;
		LNP(T) p=first(); // p q 分别指向前后相邻节点
		LNP(T) q=p->succ;
		for(; q!=trailer; p=q,q=q->succ){ // 边历一边list
			if(q->data==p->data){ // 如果值相同删除q所指节点
				remove(q);
				q=p;  // 让p停留一步
			} 
		}
		return oldSize-_size;
	}
```

### 4. 排序
```c++
	void insertSort(LNP(T) p, int n){ // 对 包括p在内的 n各节点排序
		for(int r=0; r<n; ++r){ 
			insertAfter(search(p->data, r, p), p->data); // 在以排序范围内先插入再删除
			p=p->succ;  // 移动到下一个
			remove(p->pred); // 删除多余前驱
		}
	}
	void selectionSort(LNP(T) p, int n){
		LNP(T) head=p->pred; // 设定区间 
		LNP(T) tail=p;for(int i=0; i<n; ++i) tail=tail->succ;
		while(1<n){
			LNP(T) m=selectMax(head->succ, n); // 每趟第一个节点会改变 找到最大节点位置
			insertBefore(tail, remove(m));  // 移动
			tail=tail->pred; // 更改区间
			--n; // 缩小范围
		}
	}
	void mergeSort(LNP(T) &p, int n){
		if(n<2) return ;
		int m=n>>1; 
		LNP(T) q=p; for(int i=0; i<m; ++i) q=q->succ; 
		// p 指向前半段第一个 q指向后半段第一个 前半段一共m个 后半段一共n-m个
		mergeSort(p, m);
		mergeSort(q, n-m);
		merge(p, m, *this, q, n-m);
	}
	void mergeSort(){ auto h=header->succ; mergeSort(h, _size); } //注意是header->succ的副本
	void merge(LNP(T) &p, int n, List<T> &L, LNP(T) q, int m){
		LNP(T) pp=p->pred;
		while(0<m){
			if( 0<n && (p->data<=q->data)){
				if( q==(p=p->succ)) break;
				n--;
			}else{
				q=q->succ;
				insertBefore(p, L.remove(q->pred));
				m--;
			}
		}
		p=pp->succ;
	}
```

### 4. 习题总结
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

