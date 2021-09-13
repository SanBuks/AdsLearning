// PATB1002 写出这个数
#include <cstdio>
char str[110];
char num[10][5]={"ling", "yi", "er", "san", "si", "wu", "liu",
	"qi", "ba", "jiu"};
int main(){
	int sum=0, p=0;

	scanf("%s", str);
	for(int i=0; str[i]!='\0'; ++i)
		sum+=str[i]-'0';

	while(sum){
		str[p++]=sum%10;
		sum/=10;
	}
	if(!p)
		printf("ling");
	while(p--){
		printf("%s", num[str[p]]);
		if(p!=0)
			printf(" ");
	}
	return 0;
}
