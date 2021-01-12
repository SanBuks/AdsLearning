// PATB1016 部分A+B
#include <cstdio>

long long partof(long long T, int t){
	int result=0;
	do{
		if(T%10==t) result=result*10+t; 
		T/=10; 
	}while(T);
	return result; 
}

int main(){
	long long A, B;
	int a, b;
	scanf("%lld %d %lld %d", &A, &a, &B, &b);
	A=partof(A, a);
	B=partof(B, b);
	printf("%lld", A+B);
	return 0;
}
