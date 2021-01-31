# 第二章 向量

### 1. 概述
- 数据结构是数据项的结构化集合，结构化可理解为数据项之间的逻辑关系，根据逻辑化关系可以分为线性结构，半线性结构和非线性结构三类。列表属于线性结构关系，根据存储位置和逻辑次序的对因关系分为 向量 和 列表。
- 数组也是一个线性数据结构，起始地址为A ，每个元素占用S个单位空间，则S[i]=A+i ，将数组类型进行抽象和泛化，形成向量，通过寻秩访问元素。
- 排序算法可按存储特点分为内部排序和外部排序，按输入特点分为离线和在线排序，按体系分为串行和并行排序。 比较式算法可根据比较树得出叶节点为n，则树高最少为log2(n)，树高即比较过程中的比较次数。在比较排序过程中存在三分支情况则树高最少为log3(n!)=O(nlog(n))，n！是可能出现的顺序结果数。


### 2. 数据部分
```c++
typedef int rank; // 规定秩即下标
const int DS=3;  // 最小容量
template<typename T> class Vector{
protected:  // 为了同类元素之间的访问 设定 protected 访问符
    T *_elem;  // 数组的指针 访问范围默认左闭右开
    int _size; // 数量
    int _capa; // 容量
};

class Fib{  // Fib数列生成对象
private:
	int g,f;
public:
	int get(){ return f; }
    Fib(int n):g(0),f(1){// f 初始化为不小于n的最小fib数或者int能表示的最大数
      	if(n>1836311902) n=1836311902; 
        while(f<n) next();}
	void next(){  // 下一个Fib数 最大为 1836311903
        f=g+f; g=f-g;
        if(f<0){ f=1836311903; g=1134903170; } // 溢出修正
	}
	void pre(){  // 上一个Fib数 最小为 1
		g=f-g; f=f-g;
		if(f<1){ f=1; g=0; }
	}
};
```

### 3. 工具函数
```c++
void copyFrom(const T *A, rank lo, rank hi); // 创建2倍或DS的空间，复制数组
void expand(); void shrink(); // 2倍扩容和1/4缩容 分摊分析 O(n)
void traverse(void (*visit)(const T &e)); // 函数指针遍历元素
typename<VST> void traverse(VST &visit); // 类对象遍历元素
```

### 4. 类相关函数
```c++
Vector(int c=DS, int s=0, T v=0); // 构造容量c 规模s 元素都是v 的向量
Vector(const T *A, rank lo, rank hi); // 调用copyFrom 复制数组来构造 
~Vector(); // 删除_elem 数组，元素默认析构
T &operator[](rank r) const; // 返回具体元素const引用
T &operator[](rank r); // 返回具体元素引用
Vector<int> &operator=(Vector<T> const &v); // 调用copyFrom 复制向量
```

### 5. 简单函数
```c++
rank size() const; // 返回当前数量
bool empty() const; // 返回是否为空
int disorder() const; // 计算紧邻逆序数
rank max(rank lo, rank hi) const; // 返回最大值的下标 如果范围非法返回-1
void unsort(rank lo, rank hi){ // **置乱**
srand((int)time(0));
T *V=_elem+lo;  // 转换为[0, hi-lo) 区间
for(int i=hi-lo; i>0; --i)
    std::swap(V[i-1], V[rand()%i]);
}
```

### 6. 增加与删除函数
```c++
rank insert(rank r, const T &e){  // 在下标前插入元素，返回下标方便循环调用
    expand();  // 首先扩容
    for(int i=_size; i>r; --i)  // 后往前移动
        _elem[i]=_elem[i-1]
    _elem[r]=e;
    _size++;
    return r;
}

T remove(rank r); // 删除下标元素，返回该元素
int remove(rank lo, rank hi){  // 删除范围元素， 返回删除个数
    while(hi<_size)  // 从后往前覆盖
        _elem[lo++]=_elem[hi++];
    _size=lo;
    shrink();  // 之后缩容
    return hi-lo;
}

rank find(const T &e, rank lo, rank hi){ // 无序范围查找，返回最后一个相等元素的下标否则返回-1
    while(lo<hi--)
        if(_elem[hi]==e)
            return hi;
    return -1;
}

int deduplicate(){  // 无序向量唯一化
    if(_size<2) return 0;
    int oldSize=_size;
    int i=1;
    while(i<_size){
        if(-1==find(_elem[i], 0, i)) ++i; // 唯一则下一个
        else remove(i, i+1);  // 停留在原地
    }
    return oldSize-_size;
}

int uniqufy(){  // 有序向量唯一化 用移动代替删除
    if(_size<2) return 0;
    int i=0, j=1;
    while(j<_size){
        if(_elem[i]!=_elem[j])  // 如果不相等直接移动到i 的后面
            _elem[++i]=_elem[j++];
        else j++;
    }
    _size=++i;
    shrink();
    return j-i;
}
```

### 7. 查找与排序
```c++
	rank binSearch(const T &e, rank lo, rank hi){  // 二分查找
		// 3分支二分 设2^(k-1)=n 可得平均比较长度为O(1.5k)即 O(1.5log2(n))
		// 3分支fib二分 平均比较长度略有提升
        // 2分支 T(n)=T(n/2)+1 可得O(log2(n))
		while(lo<hi){
			rank mi=(lo+hi)>>1;
			if(e<_elem[mi]) hi=mi;
			else lo=mi+1;
		}
		return --lo;
	}

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
	
	void bubbleSort(rank lo, rank hi){  // 冒泡排序 O(n^2)
		for(int last=hi; lo<hi; hi=last){ 
			// last 是 记录每趟扫描中最后交换落位的位置 即已经排序范围的左边界
			last=lo; // 每次默认已经排序好
			for(int i=lo; i<hi-1; ++i)
				if(_elem[i]>_elem[i+1]){
					last=i+1;
					std::swap(_elem[i],_elem[i+1]);
				}
		}
	}

	void mergeSort(rank lo, rank hi){
		if(hi-lo<2) return ;
		int mi=(lo+hi)>>1;
		mergeSort(lo, mi);
		mergeSort(mi, hi);
		merge(lo, mi, hi);
	}

	void merge(rank lo, rank mi, rank hi){
		T *A=_elem+lo; // A是存放归并后的数组

		int lb=mi-lo;  
		T *B=new T[lb]; // B是复制备份的前段数组
		for(int i=0;i<lb;B[i++]=_elem[lo++]);
		
		int lc=hi-mi;  // C是后段数组,只对前端数组复制原因是防止错乱
		T *C=_elem+mi;
		
		int i,j,k;
		for( i=j=k=0; j<lb&&k<lc;){  // 两段数组比较,最小的放入A中
			if(B[j]<=C[k]) A[i++]=B[j++];  // 为了稳定性
			if(C[k]< B[j]) A[i++]=C[k++];
		}
		while(j<lb) A[i++]=B[j++];  // 未归并完的放入A中
		while(k<lc) A[i++]=C[k++];

		/*  
		for( i=j=k=0; j<lb||k<lc;){ // 一段更简洁的写法
			if( !(k<lc)||(j<lb&&B[j]<=C[k]) ) A[i++]=B[j++];
			if( !(j<lb)||(k<lc&&C[k]< B[j]) ) A[i++]=C[k++];
		} 
		*/
		delete [] B;
	
	}

```












