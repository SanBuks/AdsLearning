// PATB1010 一元多项式求导
#include <cstdio>
int num[2010][2]={}; /* int : index | -1000 : 0 | 0 : 1000 | 1000 : 2000 */
inline int int2index(const int &a){
	return a+1000;
}

inline int index2int(const int &a){
	return a-1000;
}

int main(){
	int n1, n2; int count=0;
	while(scanf("%d %d", &n1, &n2)!=EOF){
		if(n2!=0){
			n1=n1*n2;
			n2--;
			if(num[int2index(n2)][1]==0){
				count++;
				num[int2index(n2)][1]=1;
			}
			num[int2index(n2)][0]+=n1;
		}
	}
	if(count==0) printf("0 0");
	else{
		for(int j=int2index(1000); j>=int2index(-1000); j--){
			if(num[j][0]!=0){
				printf("%d %d", num[j][0], index2int(j));
				count--;
				if(count>0)
					printf(" ");
			}
		}
	}
	return 0;
}
