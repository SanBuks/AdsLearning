#include <iostream>
long long fib_R(long long n, long long &pre){
	if(n==0){ pre=1; return 0; }
	else{
		long long prepre;
		pre=fib_R(n-1, prepre);
		return pre+prepre;
	}
}

long long fib_I(std::size_t n){
	long long f=0, g=1;
	while(n--){
		f=f+g;
		g=f-g;
	}
	return f;
}


int main(){
	std::cout<<fib_I(6)<<std::endl;
	return 0;
}
