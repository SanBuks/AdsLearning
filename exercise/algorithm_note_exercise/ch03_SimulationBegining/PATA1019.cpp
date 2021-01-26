// PATA1019 General Palindromic Number
#include <cstdio>
int result[31];
bool ispalindromic(int *result, int p){
	for(int i=0, j=--p; i<j; ++i, --j)
		if(result[i]!=result[j])
				return false;
	return true;
}

int main(){
	int N, b, n;
	scanf("%d %d", &N, &b);
	for(n=0; N>0; ++n){
		result[n]=N%b;
		N/=b;
	}
	if(ispalindromic(result, n)) printf("Yes\n");
	else printf("No\n");
	while(--n>=0){ 
		printf("%d", result[n]);
		if(n!=0) printf(" ");
	}
	return 0;
}
