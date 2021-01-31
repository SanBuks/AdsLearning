# include<iostream>
# include"Vector.h"

class VST{
public:
	void operator()(const int &e){
		std::cout<<e<<" ";
	}
};

//void visit(const int &e){
//	std::cout<<e<<" ";
//}

int main(){
	int a[7]={1,2,2,4,4,5,5};
	Vector<int> l(a,0,7);
	VST visit;
	l.unsort(0,7);
	l.traverse<VST>(visit);
	std::cout<<"\n";

	l.mergeSort(0,l.size());
	l.traverse<VST>(visit);
	std::cout<<"\n";

	return 0;
}
