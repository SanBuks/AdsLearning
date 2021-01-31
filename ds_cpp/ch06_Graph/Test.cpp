#include "GraphMatrix.h"
#include <iostream>

void bfs_test(){
	GraphMatrix<int, int> gm;
	for(int i=0; i<8; ++i)
		gm.insert(i);
	gm.insert(0, 0, 0, 1);
	gm.insert(0, 0, 0, 3);
	gm.insert(0, 0, 0, 4);

	gm.insert(0, 0, 1, 3);
	gm.insert(0, 0, 1, 5);

	gm.insert(0, 0, 3, 2);

	gm.insert(0, 0, 4, 2);

	gm.insert(0, 0, 5, 6);
	gm.insert(0, 0, 5, 7);

	gm.insert(0, 0, 7, 2);
	gm.insert(0, 0, 7, 6);

	gm.bfs(0);
}
void dfs_test(){
	GraphMatrix<int, int> gm;
	for(int i=0; i<7; ++i)
		gm.insert(i);
	gm.insert(0, 0, 0, 1);
	gm.insert(0, 0, 0, 2);
	gm.insert(0, 0, 0, 5);

	gm.insert(0, 0, 1, 2);

	gm.insert(0, 0, 3, 0);
	gm.insert(0, 0, 3, 4);

	gm.insert(0, 0, 4, 5);

	gm.insert(0, 0, 5, 6);

	gm.insert(0, 0, 6, 0);
	gm.insert(0, 0, 6, 2);

	gm.dfs(0);
	gm.traverse_edge(TREE);
	
	gm.remove(6, 0);
	auto stack=gm.tSort(2);
	while(!stack->empty())
		std::cout<<stack->pop()<<std::endl;
	delete stack;
}
void pfs_test(){
	GraphMatrix<int, int> gm;
	for(int i=0; i<8; ++i)
		gm.insert(i);

	gm.insert(0, 4, 0, 1);
	gm.insert(0, 4, 1, 0);

	gm.insert(0, 12, 1, 2);
	gm.insert(0, 12, 2, 1);

	gm.insert(0, 6, 0, 3);
	gm.insert(0, 6, 3, 0);

	gm.insert(0, 9, 3, 2);
	gm.insert(0, 9, 2, 3);

	gm.insert(0, 13, 3, 4);
	gm.insert(0, 13, 4, 3);

	gm.insert(0, 5, 4, 5);
	gm.insert(0, 5, 5, 4);

	gm.insert(0, 1, 4, 2);
	gm.insert(0, 1, 2, 4);

	gm.insert(0, 2, 2, 5);
	gm.insert(0, 2, 5, 2);
	
	//PrimPU<int, int> ppu;
	//gm.pfs<PrimPU<int, int>>(4,ppu);
	//gm.traverse_edge(TREE);

	DijkstraPU<int, int> dpu;
	gm.pfs<DijkstraPU<int, int>>(0, dpu);
	gm.traverse_edge(TREE);
}

int main(){
	//bfs_test();
	//dfs_test();
	pfs_test();
	return 0;
}
