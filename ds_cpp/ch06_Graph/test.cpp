#include <iostream>

template <typename T>
class B{
public :
	int n;
};

template <typename T>
class A : public B<T>{
public:
	void print(){
		std::cout<<n;
	}
};


int main(){
	A<int> a;
	a.print();

	return 0;
}
