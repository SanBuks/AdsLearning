// PATB1006 换个格式输出整数
#include <cstdio>
int main(){
	int N;
	scanf("%d", &N);
	if(N/100){
		for(int i=0; i<N/100; ++i)
			printf("B");
	}
	N%=100;
	if(N/10){
		for(int i=0; i<N/10; ++i)
			printf("S");
	}
	N%=10;
	for(int i=1; i<=N; ++i)
		printf("%d", i);
	return 0;
}
