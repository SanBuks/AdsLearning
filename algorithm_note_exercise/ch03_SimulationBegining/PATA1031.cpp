// PATA1031 Hello World for U
#include <cstdio>
#include <cstring>
char str[90]={};
int main(){
	int N;
	scanf("%s", str);
	N=strlen(str);
	int n1=-1, n2=N;
	while(n2>=3){ // 根据n2进行遍历
		if((N+2-n2)%2==0){ // n1是整数
			int temp=(N+2-n2)/2;
			if(temp<=n2&&temp>n1)  // n1不大于n2 且 是最大值
				n1=temp;
		}
		n2--;
	}
	n2=N+2-n1-n1;
	for(int i=0; i<n1-1; ++i){
		printf("%c", str[i]);
		for(int j=0; j<n2-2; ++j)
			printf(" ");
		printf("%c", str[N-1-i]);
		printf("\n");
	}
	for(int i=0; i<n2; ++i)
		printf("%c", str[n1-1+i]);
	return 0;
}
