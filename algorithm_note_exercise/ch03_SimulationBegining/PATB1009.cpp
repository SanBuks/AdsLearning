//PATB1009 说反话
#include <cstdio>
char result[90][90]={};
int main(){
	int n=0;
	while(scanf("%s", result[n++])!=EOF) ;
    --n; // 最后一次失败
	while(n--){
		printf("%s", result[n]);
		if(n!=0) printf(" ");
	}
	return 0;
}
