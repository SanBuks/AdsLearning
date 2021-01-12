// PATB1001 A+B 和 C
#include <cstdio>

int main(){
	long long a, b, c;
	int T, Temp;
	scanf("%d", &T);
	Temp=T;
	while(T--){
		scanf("%lld %lld %lld", &a, &b, &c);
		printf("Case #%d: ", Temp-T);
		if(a+b>c) printf("true\n");
		else printf("false\n");
	}
	return 0;
}
