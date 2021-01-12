// PAT B 1001 害死人不偿命的3n+1问题
#include <cstdio>

int main(){
	int n,sum;
	sum=0;
	scanf("%d", &n);
	while(n!=1){
		if(n%2) n=(3*n+1)/2;
		else n/=2;
		sum++;
	}
	printf("%d", sum);
	return 0;
}
