#include <iostream>
#include <cmath>

// 求2的幂 
int power2(int n){
	if(n==0) return 1;
	int sqr=power2(n>>1);
	if(n&1) return sqr*sqr*2;
	else return sqr*sqr;
}

int main(){
	std::cout<<power2_R(30);
}
