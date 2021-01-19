// PATA 1011 World Cup Betting
#include <cstdio>
char pattern[3]={'W', 'T', 'L'};
double odds[3]={};
int main(){
	int N; double sum=1.0;
	for(int i=0; i<3; i++){
		scanf("%lf %lf %lf", &odds[0], &odds[1], &odds[2]);
		int minindex=0;
		for(int j=1; j<3; ++j)
			if(odds[j]>odds[minindex])
				minindex=j;
		sum*=odds[minindex];
		printf("%c ", pattern[minindex]);
	}
	sum=(sum*0.65-1)*2;
	printf("%.2lf", sum);
}
