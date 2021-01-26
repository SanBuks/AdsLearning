// PATA1058 A+B in Hogwarts
#include <cstdio>
inline long long clac(const long long &g, const int &s, const int &k){ return 29*17*g+29*s+k; }
int main(){
	long long sum;
	long long g; int s, k;
	scanf("%lld.%d.%d", &g, &s, &k);
	sum=clac(g, s, k);
	scanf("%lld.%d.%d", &g, &s, &k);
	sum+=clac(g, s, k);

	g=sum/(17*29);
	s=sum%(17*29)/29;
	k=sum%29;
	printf("%lld.%d.%d", g, s, k);
	return 0;
}
