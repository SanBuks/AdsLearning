// PATA 1006 Sign In and Sign Out
#include <cstdio>
#include <cstring>
char id[3][20]={};
int main(){
	int N, min, max, h1, h2, m1, m2, s1, s2;
	scanf("%d", &N);
	scanf("%s %d:%d:%d %d:%d:%d", id[0], &h1, &m1, &s1, &h2, &m2, &s2);
	strcpy(id[1], id[0]);
	min=h1*60*60+m1*60+s1;
	max=h2*60*60+m2*60+s2;
	for(int i=0; i<N-1; ++i){
		scanf("%s %d:%d:%d %d:%d:%d", id[2], &h1, &m1, &s1, &h2, &m2, &s2);
		if((h1*60*60+m1*60+s1)<min){
			strcpy(id[0], id[2]);	
			min=h1*60*60+m1*60+s1;
		}
		if((h2*60*60+m2*60+s2)>max){
			strcpy(id[1], id[2]);	
			max=h2*60*60+m2*60+s2;
		}
	}
	printf("%s %s", id[0], id[1]);
	return 0;
}
