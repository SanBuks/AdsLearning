#pragma once
#include <climits>
#include <iostream>
#include "../ch04_Stack/Queue.h"
#include "../ch04_Stack/Stack.h"
typedef enum { UNDIS, DIS, VIS } VStatus;
typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD} EStatus;
template <typename Tv, typename Te> struct PrimPU;
template <typename Tv, typename Te>
class Graph{
private:
	void reset(){
		for(int i=0; i<n; ++i){
			status(i)=UNDIS;
			dTime(i)=fTime(i)=-1;
			parent(i)=-1;
			priority(i)=INT_MAX;
			for(int j=0; j<n; ++j)
				if(exists(i, j)) 
					status(i, j)=UNDETERMINED;
		}
	}

	void BFS(int, int &);
	void DFS(int, int &);
	void DFS_S(int, int &);
	bool TSort(int, int &, Stack<Tv> *);

	template <typename PU>
	void PFS(int, PU);

public:
	int n, e;  // 顶点总数 边总数
	virtual Tv& vertex (int)=0;
   	virtual int inDegree (int)=0;
   	virtual int outDegree (int)=0;
   	virtual int firstNbr(int)=0;
	virtual int nextNbr(int,int)=0;

   	virtual VStatus& status (int)=0; 
   	virtual int& dTime (int)=0; 
   	virtual int& fTime (int)=0; 
   	virtual int& parent (int)=0; 
   	virtual int& priority (int)=0; 
   	virtual bool exists(int, int)=0;

	virtual EStatus& status(int, int)=0; 
   	virtual Te& edge (int, int)=0; 
   	virtual int& weight (int, int)=0; 

	virtual int insert(const Tv &)=0;
	virtual Tv remove(int)=0;
	virtual void insert(const Te &, int, int, int)=0;
	virtual Te remove(int, int)=0;

	void bfs(int);
	void dfs(int);
	Stack<Tv> * tSort(int);
	template <typename PU>
	void pfs(int, PU);
};

template <typename Tv, typename Te>
void Graph<Tv, Te>::bfs(int s){
	reset();
	int clock=0;
	int v=s;
	do{
		if(status(v)==UNDIS)
			BFS(v, clock);
	}while(s != ( v = ((v+1)%n) ));
}

template <typename Tv, typename Te>
void Graph<Tv, Te>::BFS(int v, int &clock){
	Queue<int> Q;
	status(v)=DIS;
	Q.enqueue(v);
	while(!Q.empty()){ 
		int v=Q.dequeue();
		dTime(v)=++clock;
		std::cout<<vertex(v)<<" "<<dTime(v)<<std::endl; //
		for(int u=firstNbr(v); -1<u; u=nextNbr(v, u)){
			if(status(u)==UNDIS){
				status(u)=DIS;
				Q.enqueue(u);
				status(v,u)=TREE;
				parent(u)=v;
			}
		}
		status(v)=VIS;
	}
}

template <typename Tv, typename Te>
void Graph<Tv, Te>::dfs(int s){
	reset();
	int clock=0;
	int v=s;
	do{
		if(status(v)==UNDIS)
			DFS(v, clock);
	}while(s!=(v=(v+1)%n));
}
	
template <typename Tv, typename Te>
void Graph<Tv, Te>::DFS(int v, int &clock){
	dTime(v)=++clock;
	std::cout<<vertex(v)<<" "<<clock<<std::endl;
	status(v)=DIS;
	for(int u=firstNbr(v); -1<u; u=nextNbr(v, u)){
		switch(status(u)){
			case UNDIS:
				status(v,u)=TREE;
				parent(u)=v;
				DFS(u, clock);
				break;
			case DIS:
				status(v,u)=BACKWARD;
				break;
			default:
				status(v,u)= ( dTime(v)<dTime(u)? FORWARD : CROSS);
				break;
		}
	}
	status(v)=VIS;
	fTime(v)=++clock;
	std::cout<<vertex(v)<<" "<<clock<<std::endl;
}

template <typename Tv, typename Te>
void Graph<Tv, Te>::DFS_S(int v, int &clock){
	Stack<int> s;

	status(v)=DIS;
	dTime(v)=++clock;
	std::cout<<vertex(v)<<" "<<clock<<std::endl;
	s.push(v);

	while(!s.empty()){
T:
		auto v=s.top();
		for(auto u=firstNbr(v); -1<u; u=nextNbr(v, u)){
			switch(status(u)){
				case DIS:
					status(v,u)=BACKWARD;
					break;
				case VIS:
					if(status(v,u)==UNDETERMINED)
						status(v,u)= (dTime(v)<dTime(u)?FORWARD:CROSS);
					break;
				default:
					parent(u)=v;
					status(v,u)=TREE;
					status(u)=DIS;
					dTime(u)=++clock;
					std::cout<<vertex(u)<<" "<<clock<<std::endl;
					s.push(u);
					goto T;
					break;
			}
		}
		status(v)=VIS;
		fTime(v)=++clock;
		std::cout<<vertex(v)<<" "<<clock<<std::endl;
		s.pop();
	}
}

template <typename Tv, typename Te>
Stack<Tv>* Graph<Tv, Te>::tSort(int s){
	reset();
	int clock=0;
	int v=s;
	Stack<Tv> *S=new Stack<Tv>;
	do{
		if( UNDIS==status(v) )
			if( !TSort(v, clock, S) ){
				while(!S->empty()) S->pop();
				break;
			}
	}while( s != (v = ( (v+1)%n) ) );
	return S;
}

template <typename Tv, typename Te>
bool Graph<Tv, Te>::TSort(int v, int &clock, Stack<Tv> *S){
	dTime(v)=++clock;
	status(v)=DIS;
	for(int u=firstNbr(v); -1<u; u=nextNbr(v, u)){
		switch(status(u)){
			case UNDIS:
				parent(u)=v;
				status(v, u)=TREE;
				if(!TSort(u, clock, S))
					return false;
				break;
			case DIS:
				status(v, u)=BACKWARD;
				return false;
			default:
				status(v, u)=( dTime(v)<dTime(u)?FORWARD:CROSS);
				break;
		}
	}
	status(v)=VIS;
	S->push(vertex(v));
	return true;
}

template <typename Tv, typename Te>
template <typename PU>
void Graph<Tv, Te>::pfs(int s, PU prioUpdater){
	reset();
	int v=s;
	do{
		if(UNDIS==status(v))
			PFS(v, prioUpdater);
	}while(s != (v = ((v+1)%n)));
}

template <typename Tv, typename Te>
template <typename PU>
void Graph<Tv, Te>::PFS(int s, PU prioUpdater){
	priority(s)=0;
	status(s)=VIS;
	std::cout<<vertex(s)<<std::endl;
	parent(s)=-1;
	while(1){
		for(int w=firstNbr(s); -1<w; w=nextNbr(s, w))
			prioUpdater(this, s, w);
		for(int shortest=INT_MAX, w=0; w<n; ++w)
			if(status(w)==UNDIS)
				if(shortest>priority(w)){
					shortest=priority(w);
					s=w;
				}
		if(VIS==status(s)) break;
		status(s)=VIS; 
		std::cout<<vertex(s)<<std::endl;
		status(parent(s), s)=TREE;
	}
}


template <typename Tv, typename Te> 
struct PrimPU{
	virtual void operator()(Graph<Tv, Te> *g, int uk, int v){
		if(g->status(v)==UNDIS)
			if(g->priority(v)>g->weight(uk, v)){
				g->priority(v)=g->weight(uk, v);
				g->parent(v)=uk;
			}
	}
};

template <typename Tv, typename Te> 
struct DijkstraPU{
	virtual void operator()(Graph<Tv, Te> *g, int uk, int v){
		if(g->status(v)==UNDIS)
			if(g->priority(v)>g->priority(uk)+g->weight(uk, v)){
				g->priority(v)=g->priority(uk)+g->weight(uk, v);
				g->parent(v)=uk;
			}
	}
};
