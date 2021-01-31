#pragma once
#include <utility>
#include <random>
#include <ctime> 
#include "Fib.h"

typedef int rank;
const int DS=3;
template<typename T>
class Vector{
protected:  // 为了同类元素之间的访问 设定protected访问符
	T *_elem;  // 存放元素数组的指针
	int _size; // 实际元素数量
	int _capa; // 存放元素容量

	void copyFrom(const T *A, rank lo, rank hi){
		(hi-lo)<DS?_capa=DS:_capa=hi-lo;// 容量至少为DS	
		_elem=new T[_capa<<=1];// 容量扩大一倍
		_size=0;
		while(lo<hi) // 逐一复制
			_elem[_size++]=A[lo++];
	}

	void expand(){ // T(n) = N+2N+4N+....+n < 2n = O(n) 
		if(_size<_capa) return ; // 未满不扩充
		if(_capa<DS) _capa=DS; // 最小容量为 DS

		T *oldElem=_elem;
		_elem=new T[_capa<<=1];// 扩充容量
		for(int i=0; i<_size; ++i) // 逐一复制
			_elem[i]=oldElem[i];
		delete [] oldElem; // 最后删除原数据
	}

	void shrink(){
		if((_capa>>2)<_size) return; // 1/4_capa<_size 则不缩容
		if((_capa>>1)<DS) return; // 缩小后的容量不能小于DS
		
		T *oldElem=_elem;  // 同上
		_elem=new T[_capa>>=1];
		for(int i=0; i<_size; ++i)
			_elem[i]=oldElem[i];
		delete [] oldElem;
	}

public:
    Vector(int c, int s, T v){ // 容量c 规模s 元素v
		if(c<DS) c=DS;  // 最小值为DS
		_elem=new T[_capa=c];
		for(_size=0; _size<s; ++_size)
			_elem[_size]=v;
	}

	explicit Vector(int c=DS){
		if(c<DS) c=DS;  // 最小值为DS
		_elem=new T[_capa=c];
		_size=0;
	}
	
	Vector(const T *A, rank lo, rank hi){
		copyFrom(A,lo,hi);
	}

	~Vector(){
		delete [] _elem; // 删除数组 元素默认有析构函数
	}

	rank size() const {
		return _size;
	}

	bool empty() const {
		return _size<=0;
	}

	int disorder() const {
		int sum=0;
		for(int i=1; i<_size; ++i) // 计算紧邻逆序数
			if(_elem[i]<_elem[i-1])
				++sum;
		return sum;
	}

	rank max(rank lo, rank hi)const{
		if(empty()||hi<=lo||lo<0||hi>_size) return -1; // 下标非法返回-1	

		rank max=lo;
		for(int i=lo+1; i<hi; ++i) // 画家算法找出最大值下标
			if(_elem[i]>_elem[max])
				max=i;
		return max;
	}

	T &operator[](rank r)const{ // 返回 const T & 元素 
		return _elem[r];
	} 
	
	T &operator[](rank r){  // 返回 T & 元素
		return _elem[r];
	}

	Vector<T> &operator=(Vector<T> const &v){
		if(_elem) delete [] _elem;
		copyFrom(v._elem, 0, v.size()); // _elem 是 protected 属性
		return *this;
	}
	
	rank insert(rank r, const T &e){
		expand();  // 插入之前扩容
		for(int i=_size; i>r; --i) // 从后往前移动
			_elem[i]=_elem[i-1];
		_elem[r]=e;
		++_size;
		return r;
	}

	rank insert(const T &e){
		expand();
		_elem[_size]=e;
		++_size;
		return _size-1;
	}
	
	int remove(rank lo, rank hi){
		while(hi<_size)
			_elem[lo++]=_elem[hi++]; // 从后向前移动完成删除
		_size=lo;
		shrink();  // 删除之后缩容
		return hi-lo;
	}

	T remove(rank r){  // 删除一个元素 
		T result=_elem[r];
		remove(r,r+1);
		return result;
	}

	int deduplicate(){ // 无序唯一化
		if(_size<2) return 0;

		int oldSize=_size;
		int i=1;
		while(i<_size){
			if(-1==find(_elem[i], 0, i)) ++i;  // 没找到则下一个
			else remove(i,i+1); // 找到则删除并停留再原地
		}
		return oldSize-_size;
	}
	
	int uniqufy(){
		if(_size<2) return 0;
		
		int i=0,j=1;
		while(j<_size){  // 在有序向量中 按子区间 移动元素删除重复元素
			if(_elem[j]==_elem[i]) ++j;
			else _elem[++i]=_elem[j++];
		}
		_size=++i;
		shrink();
		return j-_size;
	}
	
	void unsort(rank lo, rank hi){ // 范围内置乱
		srand((int)time(0));
		T *V=_elem+lo;  // 转换为[0, hi-lo) 区间
		for(int i=hi-lo; i>0; --i)
			std::swap(V[i-1], V[rand()%i]);
	}

	void bubbleSort(rank lo, rank hi){
		for(int last=hi; lo<hi; hi=last){ 
			// last 是 记录每趟扫描中最后交换落位的位置 即已经排序范围的左边界
			last=lo; // 每次默认已经排序好
			for(int i=lo; i<hi-1; ++i){
				if(_elem[i]>_elem[i+1]){
					last=i+1;
					std::swap(_elem[i],_elem[i+1]);
				}
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

		int lb=mi-lo;  // B是复制备份的前段数组
		T *B=new T[lb]; 
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

	rank find(const T &e, rank lo, rank hi){
		while(lo<hi--){ // 从后往前在无序向量中查找秩最大的下标
			if(e==_elem[hi])
				return hi;
		}
		return -1; // 没有找到就返回 -1 
	}
	
	rank binSearch(const T &e, rank lo, rank hi){
		while(lo<hi){ // 在有序向量中二分查找寻找<=e 的最大值
			int mi=(hi+lo)>>1;
			if(e<_elem[mi]) hi=mi;
			else lo=mi+1; // e >= _elem[mi]
		}
		return --lo;
	}

	rank fibSearch(const T &e, rank lo, rank hi){
		Fib fib(hi-lo); // 获取不小于 hi-lo的 第一个fib数
		while(lo<hi){
			while(hi-lo<fib.get()) fib.pre(); // 使fib数<= hi-lo 
			int mi=lo+fib.get()-1;  // 以 fib数为中点下标
			if(e<_elem[mi]) hi=mi;
			else lo=mi+1;
		}
		return --lo;	
	}

	void traverse(void (*visit)(const T &e)){
		for(int i=0; i<_size; ++i)
			visit(_elem[i]);
	}
	
	template<typename VST>
	void traverse(VST &visit){
		for(int i=0; i<_size; ++i)
			visit(_elem[i]);	
	}

};
