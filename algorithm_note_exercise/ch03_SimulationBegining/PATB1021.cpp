// PATB1021 个位数统计
#include <cstdio>
int num[20]={};
char str[1010]={};
int main(){
	int N;
	scanf("%s", str);
	for(int i=0; str[i]!='\0'; ++i)
		num[str[i]-'0']++;
	for(int i=0; i<10; ++i)
		if(num[i])
			printf("%d:%d\n", i, num[i]);
	return 0;
}
