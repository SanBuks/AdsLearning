// PATB1036 跟奥巴马一起编程
#include <cstdio>
#include <cmath>

int main(){
	char c; int n;
	scanf("%d %c", &n, &c);
	int m=round(n*0.5);
	for(int i=0; i<n; i++)
		printf("%c", c);
	printf("\n");

	for(int i=0; i<m-2; ++i){
		printf("%c", c);
		for(int j=0; j<n-2; j++)
			printf(" ");
		printf("%c\n", c);
	}
		
	for(int i=0; i<n; i++)
		printf("%c", c);

	return 0;
}
