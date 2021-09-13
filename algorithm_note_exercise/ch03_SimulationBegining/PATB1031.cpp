// PATB1031 检查身份证
#include <cstdio>
int weight[]={7,9,10,5,8,4,2,1,6,3,7,9,10,5,8,4,2};
char checksum[]={'1','0','X','9','8','7','6','5','4','3','2'};
char str[20]={};
int main(){
	bool allPassed=true;
	int N, sum=0;
	scanf("%d", &N);
	while(N--){
		sum=0;
		scanf("%s", str);	
		for(int i=0; i<17; ++i)
			sum+=(str[i]-'0')*weight[i];
		if(checksum[sum%11]!=str[17]){
			printf("%s\n", str);
			allPassed=false;
		}
	}
	if(allPassed)
		printf("All passed");
	return 0;
}
