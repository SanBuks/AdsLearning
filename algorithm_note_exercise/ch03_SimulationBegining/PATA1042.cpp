// PATA1042 Shuffling Machine
#include <cstdio>
int order[55];
int number[55];  
int number_temp[55];
char word[5]={'S', 'H', 'C', 'D', 'J'};

void shuff(int *number, int *order){
	for(int i=1; i<55; ++i)
		number_temp[order[i]]=number[i];
	for(int i=1; i<55; ++i)
		number[i]=number_temp[i];
}

int main(){
	int n;
	scanf("%d", &n);
	for(int i=1; i<55; i++){
		scanf("%d", order+i);
		number[i]=i;
	}
	while(n--){
		shuff(number, order);
	}
	for(int i=1; i<55; i++){
		printf("%c%d", word[(number[i]-1)/13], ( ((number[i]-1)/13+number[i]) %14)); 
		/*
		 * 01 - 13 <=> (01+0)%14=01 - (13+0)%14=13 (13-1)/13=0
		 * 14 - 26 <=> (14+1)%14=01 - (26+1)%14=13 (26-1)/13=1
		 * 27 - 39 <=> (27+2)%14=01 - (39+2)%14=13 (39-1)/13=2
		 */
		if(i<54) printf(" ");
	}
	return 0;
}
