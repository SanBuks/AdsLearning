#include<iostream>
#include"List.h"

void println(){ std::cout<<"\n"; }

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

void test_deduplicate(){
	List<int> list1;
	list1.insertAsFirst(6);
	list1.insertAsFirst(6);
	list1.insertAsFirst(6);
	list1.insertAsFirst(9);
	list1.insertAsFirst(0);
	list1.insertAsFirst(6);
	list1.insertAsFirst(1);
	list1.traverse(visit);
	println();
	
	list1.deduplicate();
	list1.traverse(visit);
	println();
}
void test_uniqufy(){
	List<int> list1;
	list1.insertAsFirst(6);
	list1.insertAsFirst(6);
	list1.insertAsFirst(6);
	list1.insertAsFirst(4);
	list1.insertAsFirst(4);
	list1.insertAsFirst(5);
	list1.insertAsFirst(5);
	list1.insertAsFirst(1);
	list1.traverse(visit);
	println();
	
	list1.uniqufy();
	list1.traverse(visit);
	println();


}
void test_insertSort(){
	List<int> list1;
	list1.insertAsFirst(6);
	list1.insertAsFirst(5);
	list1.insertAsFirst(8);
	list1.insertAsFirst(0);
	list1.insertAsFirst(7);
	list1.insertAsFirst(33);
	list1.insertAsFirst(56);
	list1.insertAsFirst(10);
	list1.traverse(visit);
	println();
	
	list1.insertSort(list1.first(), list1.size());
	list1.traverse(visit);
	println();
}
void test_selectionSort(){
	List<int> list1;
	list1.insertAsFirst(6);
	list1.insertAsFirst(5);
	list1.insertAsFirst(8);
	list1.insertAsFirst(0);
	list1.insertAsFirst(7);
	list1.insertAsFirst(33);
	list1.insertAsFirst(56);
	list1.insertAsFirst(10);
	list1.traverse(visit);
	println();
	
	list1.selectionSort(list1.first(), list1.size());
	list1.traverse(visit);
	println();
}
void test_mergeSort(){
	List<int> list1;
	list1.insertAsFirst(7);
	list1.insertAsFirst(6);
	list1.insertAsFirst(5);
	list1.insertAsFirst(8);
	list1.insertAsFirst(0);
	list1.insertAsFirst(7);
	list1.insertAsFirst(33);
	list1.insertAsFirst(56);
	list1.insertAsFirst(10);
	list1.traverse(visit);
	println();
	
	list1.mergeSort();
	list1.traverse(visit);
	println();
}
void test_traverse(){
	List<int> list1;
	list1.insertAsFirst(7);
	list1.insertAsFirst(6);
	list1.insertAsFirst(5);
	list1.insertAsFirst(8);
	list1.insertAsFirst(0);
	list1.insertAsFirst(7);
	list1.insertAsFirst(33);
	list1.insertAsFirst(56);
	list1.insertAsFirst(10);
	list1.traverse(visit);
	println();

	list1.traverse(increase);
	list1.traverse(visit);
}
void test_selfAdjust(){
	List<int> list1;
	list1.insertAsFirst(7);
	list1.insertAsFirst(6);
	list1.insertAsFirst(5);
	list1.insertAsFirst(8);
	list1.insertAsFirst(0);
	list1.insertAsFirst(7);
	list1.insertAsFirst(33);
	list1.insertAsFirst(56);
	list1.insertAsFirst(10);
	list1.traverse(visit);
	println();
	std::cout<<list1[3];
	list1.traverse(visit);
}

int main(){
	test_selectionSort();
	return 0;
}
