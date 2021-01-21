#include<iostream>
#include"List.h"

void println(){ std::cout<<"\n"; }
void visit(const int &e){
	std::cout<<e<<" ";
}

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

int main(){
	test_mergeSort();
	return 0;
}
