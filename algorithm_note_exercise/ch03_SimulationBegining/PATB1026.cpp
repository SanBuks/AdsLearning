// PATB1026 程序运行时间
#include <cstdio>
#include <cmath>
const int CLK_TCK=100;
const int MM=60;
const int HH=60*60;
int main(){
	int a, b;	
	scanf("%d %d", &a ,&b);
	b-=a; 
	b=round(b*1.0/CLK_TCK);
	printf("%02d:", b/HH);
	printf("%02d:", b%HH/MM);
	printf("%02d", b%HH%MM);
	return 0;
}
