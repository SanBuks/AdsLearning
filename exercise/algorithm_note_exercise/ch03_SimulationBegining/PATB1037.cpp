// PATB1037 在霍格沃茨找零钱
#include <cstdio>
inline int clac(const int &g, const int &s, const int &k){ return 29*17*g+29*s+k; }
int main(){
	int g,s,k,sum1, sum2;
	scanf("%d.%d.%d", &g, &s, &k);
	sum1=clac(g, s, k);
	scanf("%d.%d.%d", &g, &s, &k);
	sum2=clac(g, s, k);
	sum2-=sum1;
	if(sum2<0) { printf("-"); sum2=-sum2; }
	g=sum2/(17*29);
	s=sum2%(17*29)/29;
	k=sum2%29;
	printf("%d.%d.%d", g, s, k);
	return 0;
}
