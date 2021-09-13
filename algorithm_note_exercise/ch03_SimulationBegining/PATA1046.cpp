// PATA1046 Shortest Distance
#include <utility>
#include <cstdio>
const int MAX=100010;
int distance[MAX]={}; // distance of 1-#
int main(){
	int N, M, dis, d1, d2;
	scanf("%d", &N);
	for(int i=1; i<=N; i++){
		scanf("%d", &dis);
		distance[i+1]=distance[i]+dis;
	}
	scanf("%d", &M);
	while(M--){
		scanf("%d %d", &d1, &d2);	
		if(d1==d2) printf("0");
		else{
			if(d1<d2) std::swap(d1, d2);
			int a=distance[d1]-distance[d2];
			int b=distance[N+1]-a;
			if(a>b) std::swap(a,b);
			printf("%d", a);
		}
		if(M>0) printf("\n");
	}
	return 0;
}

