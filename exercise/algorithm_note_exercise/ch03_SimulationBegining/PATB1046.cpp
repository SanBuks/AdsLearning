// PTAB1046 划拳
#include <cstdio>

int main(){
	int n, A, a, B, b, aa, bb;
	aa=bb=0;
	scanf("%d", &n);
	while(n--){
		scanf("%d %d %d %d", &A, &a, &B, &b);
		if((A+B)==a && (A+B)==b) continue;
		else if((A+B)==a) bb++;
		else if((A+B)==b) aa++;
		else continue;
	}
	printf("%d %d", aa, bb);
	return 0;
}
