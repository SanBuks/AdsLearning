#include "fib.h"

Fib::Fib(ST n): f(0), g(1){
	while(f < n) 
		next();
}

Fib::ST Fib::next(){
	if(f + g >= f){ // 没有溢出上限
		f = g + f;
		g = f - g;
		return f;
	} else 
		throw std::runtime_error("ST Fib::next() : Max Over Flow!");
}

Fib::ST Fib::prev(){
	if(f > g){ // 没有溢出下限
		g = f - g;
		f = f - g;
		return f;
	} else 
		throw std::runtime_error("ST Fib::prev() : Minum Over Flow!");
}

Fib::ST fib_R1(Fib::ST n){
	if(n == 1 || n == 2) return 1;
	return fib_R1(n-1) + fib_R1(n-2);
}

Fib::ST fib_R2(Fib::ST n, Fib::ST &pre){
	if(n==0){ pre=1; return 0; }
	else{
		Fib::ST prepre;
		pre=fib_R2(n-1, prepre);
		return pre+prepre;
	}
}