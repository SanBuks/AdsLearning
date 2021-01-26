// PATA1027 Colors in Mars
#include <cstdio>
char Patt[]={'0','1','2','3','4','5','6','7','8','9','A','B','C'};
char result[3]={'0','0','\0'};
void fresh(){ result[0]='0'; result[1]='0'; }
int main(){
	int n;
	printf("#");
	while(scanf("%d", &n)!=EOF){
		result[1]=Patt[n%13];
		result[0]=Patt[n/13];
		printf("%s", result);
		fresh();
	}
	return 0;
}
