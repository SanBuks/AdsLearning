// PATB 1015 德才论
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

struct Student{
	char id[10];
	int mscore;
	int ascore;
}stu[100010];

int lb, hb;

int calcp(const Student &s){
	if(s.mscore>=hb && s.ascore>=hb) return s.mscore+s.ascore+3000;
	else if(s.mscore>=hb && s.ascore<hb) return s.mscore+s.ascore+2000;
	else if(s.mscore<hb && s.ascore<hb && s.mscore>=s.ascore) return s.mscore+s.ascore+1000;
	else return  s.mscore+s.ascore;	
}

bool cmp(const Student &s1, const Student &s2){
	int ss1=calcp(s1); int ss2=calcp(s2);
	if(ss1!=ss2) return ss1>ss2;
	else if(s1.mscore!=s2.mscore) return s1.mscore>s2.mscore; 
	return strcmp(s1.id, s2.id)<0;
}

int main(){
	int n, p=0;
	scanf("%d %d %d", &n, &lb, &hb);
	for(int i=0; i<n; i++){
		scanf("%s %d %d", stu[p].id, &stu[p].mscore, &stu[p].ascore);
		if(stu[p].mscore<lb||stu[p].ascore<lb) ;
		else p++;
	}
	sort(stu, stu+p, cmp);
	printf("%d\n", p);
	for(int i=0; i<p; ++i)
		printf("%s %d %d\n", stu[i].id, stu[i].mscore, stu[i].ascore);
	return 0;
}
