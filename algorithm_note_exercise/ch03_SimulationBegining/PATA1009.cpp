// PATA1009 Product of Polynomials
#include <cstdio>

double e[1010]={};
double result[1000010]={};

int main(){
	int N, ee, count=0;
	double aa;
	scanf("%d", &N);
	while(N--){
		scanf("%d %lf", &ee, &aa);
		if(e[ee]==0) e[ee]+=aa;
		else e[ee]+=aa;
	}
	scanf("%d", &N);
	while(N--){
		scanf("%d %lf", &ee, &aa);
		for(int i=1000; i>=0; i--){
			if(e[i]!=0){ 
				if(result[ee+i]!=0){
					result[ee+i]+=e[i]*aa;	
					if(result[ee+i]==0)
						count--;
				}else{
					result[ee+i]+=e[i]*aa;	
					if(result[ee+i]!=0)
						count++;
				}
			}
		}
	}
	printf("%d", count);
	for(int i=1000000; i>=0; --i){
		if(result[i]!=0)
			printf(" %d %.1lf", i, result[i]);
	}
	return 0;
}
