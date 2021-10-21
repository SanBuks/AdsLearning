#pragma once

#include "../ch02_Vector/Vector.h"
#include "./Graph.h"

template <typename Tv>
struct Vertex{
	Tv data;
	int inDegree, outDegree;
	VStatus status;
	int dTime, fTime;  // 时间标签
	int parent, priority; // 遍历树中的父节点, 优先级
	Vertex(const Tv &d):
		data(d), inDegree(0), outDegree(0), status(UNDIS),
		dTime(-1), fTime(-1), parent(-1), priority(INT_MAX){}
	Vertex():
		data(0), inDegree(0), outDegree(0), status(UNDIS),   // data=0问题
		dTime(-1), fTime(-1), parent(-1), priority(INT_MAX){}
};

template <typename Te>
struct Edge{
	Te data;
	int weight;
	EStatus status;
	Edge(const Te &d, int w):
		data(d), weight(w), status(UNDETERMINED){}
};

template <typename Tv, typename Te>
class GraphMatrix : public Graph<Tv, Te>{
public: 
	using Graph<Tv, Te> :: n;
	using Graph<Tv, Te> :: e;
private:
	// O(n + n^2)
	Vector< Vertex<Tv> > V;
	Vector<Vector<Edge<Te> *>> E;
public:
	GraphMatrix(){ n=e=0; }
	~GraphMatrix(){
		for(int i=0; i<n; ++i)
			for(int j=0; j<n; ++j)
				delete E[i][j];
	}

	virtual Tv& vertex ( int i ) { return V[i].data; } //数据
   	virtual int inDegree ( int i ) { return V[i].inDegree; } //入度
   	virtual int outDegree ( int i ) { return V[i].outDegree; } //出度
   	virtual int firstNbr( int i ) { return nextNbr(i, n); }
	virtual int nextNbr( int i, int j ) {   // 没有找到下一个邻居则返回-1
	   	while ((-1<j) && (!exists(i, --j)));
	   	return j;
   	}

   	virtual VStatus& status ( int i ) { return V[i].status; } //状态
   	virtual int& dTime ( int i ) { return V[i].dTime; } //时间标签dTime
   	virtual int& fTime ( int i ) { return V[i].fTime; } //时间标签fTime
   	virtual int& parent ( int i ) { return V[i].parent; } //在遍历树中的父亲
   	virtual int& priority ( int i ) { return V[i].priority; } //在遍历树中的优先级数
   	virtual bool exists(int i, int j){ return (i<n)&&(0<=i)&&(j<n)&&(0<=j)&&E[i][j]!=nullptr; }

	virtual EStatus& status( int i, int j ) { return E[i][j]->status; } //边(i, j)的类型
   	virtual Te& edge ( int i, int j ) { return E[i][j]->data; } //边(i, j)的数据
   	virtual int& weight ( int i, int j ) { return E[i][j]->weight; } //边(i, j)的权重

	virtual int insert(const Tv &vertex){  // 插入顶点
	   	for(int j=0; j<n; ++j) E[j].insert(nullptr);
	   	n++;
	   	E.insert(Vector<Edge<Te> *>(n, n, nullptr)); 
	   	return V.insert(Vertex<Tv>(vertex));
   	}

	virtual Tv remove(int i){    // 删除秩为i的顶点及其关联边
		for(int j=0; j<n; ++j)  // 删除所有出边
			if(exists(i, j)){
				delete E[i][j];
				V[j].inDegree--;
			}
		E.remove(i); 
		n--;
		for(int j=0; j<n; ++j)  // 删除所有入边
			if(exists(i, j)){
				delete  E[j].remove(i);
				V[j].outDegree--;
			}
		Tv vBak=vertex(i);  	// 删除对应的顶点
		V.remove(i);
		return vBak;
	}

	virtual void insert(const Te &edge, int w, int i, int j){ // 插入 w=e(i, j)
	   	if(exists(i, j)) return ;
	   	E[i][j]=new Edge<Te>(edge, w);
	   	e++;
	   	V[i].outDegree++;
	   	V[j].inDegree++;
	}

	virtual Te remove(int i, int j){
		Te ebak=edge(i, j);
		delete E[i][j];
		E[i][j]=nullptr;
		e--;
		V[i].outDegree--;
		V[i].inDegree--;
		return ebak;
	}

	void traverse_edge(EStatus es){
		for(int i=0; i<n; ++i)
			for(int j=0; j<n; ++j)	
				if(E[i][j]!=nullptr && E[i][j]->status==es)
					std::cout<<"edge "<<i<<" -> "<<j<<" : "<<E[i][j]->status<<std::endl;
	}
};

