// PATB1027 打印沙漏
#include <cstdio>

int main(){
	char cc;
	int N, rows=1, sum=1;
	scanf("%d %c", &N, &cc);
	while(sum<=N){
		rows+=2;
		sum+=2*rows;
	}
	sum-=2*rows;
	rows-=2;

	int rowsn=rows;
	for(int i=0; i<(rows+1)/2; ++i){
		for(int j=0; j<(rows-rowsn)/2; ++j)
			printf(" ");
		for(int j=0; j<rowsn; ++j)
			printf("%c", cc);
		printf("\n");
		rowsn-=2;
	}
	rowsn+=4;
	for(int i=0; i<(rows+1)/2-1; ++i){
		for(int j=0; j<(rows-rowsn)/2; ++j)
			printf(" ");
		for(int j=0; j<rowsn; ++j)
			printf("%c", cc);
		printf("\n");
		rowsn+=2;
	}
	printf("%d", N-sum); 	
	return 0;
}
