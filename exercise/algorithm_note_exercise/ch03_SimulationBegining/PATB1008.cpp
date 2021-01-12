#include <cstdio>
#include <utility>

int A[110];
void array_swap(int *a, int lo, int hi){
	int *start=a+lo;
	int *end=a+hi;
	for(int i=0; i<=(hi-lo)/2; ++i)
		std::swap(*(start+i), *(end-i));
}

int main(){
	int n, m;
	scanf("%d %d", &n, &m);
	for(int i=0; i<n; ++i)
		scanf("%d", A+i);
    m%=n;
    if(m!=0){
	    array_swap(A, 0, n-m-1);
	    array_swap(A, n-m, n-1);
	    array_swap(A, 0, n-1);
    }

	for(int i=0; i<n; ++i){
		printf("%d", *(A+i));
		if(i<n-1) printf(" ");
	}
	return 0;
}

