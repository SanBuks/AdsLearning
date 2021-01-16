// PATA1002 A+B for Polynomials
#include <cstdio>

double e[1010]={};
int main(){
	int N, ee, count=0;
	double aa;
	scanf("%d", &N);
	while(N--){
		scanf("%d %lf", &ee, &aa);
		if(e[ee]==0){
			e[ee]+=aa;
			if(e[ee]!=0)
				count++;
		}else{
			e[ee]+=aa;
			if(e[ee]==0)
				count--;
		}
	}
	scanf("%d", &N);
	while(N--){
		scanf("%d %lf", &ee, &aa);
		if(e[ee]==0){
			e[ee]+=aa;
			if(e[ee]!=0)
				count++;
		}else{
			e[ee]+=aa;
			if(e[ee]==0)
				count--;
		}
	}
	printf("%d", count);
	for(int i=1000; i>=0; i--){
		if(e[i]!=0)
			printf(" %d %.1lf", i, e[i]);
	}
	return 0;
}
