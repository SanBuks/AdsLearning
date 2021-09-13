// PATB1022 D进制的A+B
#include <cstdio>
int result[33]={};
int main(){
	int a, b, d, n; n=0;
	scanf("%d %d %d", &a, &b, &d);
	int sum=a+b;
	do{
		result[n++]=sum%d;
		sum/=d;
	}while(sum!=0);
	while(--n>-1) printf("%d", result[n]);
	return 0;
}
