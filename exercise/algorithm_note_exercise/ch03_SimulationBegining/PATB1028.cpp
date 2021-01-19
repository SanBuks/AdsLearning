// PATB1028 人口普查
#include <cstdio>
#include <cstring>
inline bool isLeap(const int &e){
	return (e%400==0)&&( (e%4==0) && (e%100!=0));
}
int dayofmonth[13][2]={
	0,0,
	31,31,
	28,29,
	31,31,
	30,30,
	31,31,
	30,30,
	31,31,
	31,31,
	30,30,
	31,31,
	30,30,
	31,31
};
int days[3000][13][32]={};
void init(){
	int n, yy, mm, dd; n=yy=0; dd=mm=1;
	while(yy!=3000){
		n++;
		dd++;
		if(dd>dayofmonth[mm][isLeap(yy)]){
			dd=1;
			mm++;
			if(mm>12){
				yy++;
				mm=1;
			}
		}
		days[yy][mm][dd]=n;
	}
}
char name[3][30]={};

int main(){
	init();
	int N, yy, mm, dd, num=0;
	int youngest=0x7fffffff, oldest=-1;
	scanf("%d", &N);
	for(int i=0; i<N; i++){
		scanf("%s %d/%d/%d", name[2], &yy, &mm, &dd);
		int dif=days[2014][9][6]-days[yy][mm][dd]+1; // dif>=1
		if( dif>(days[2014][9][6]-days[1814][9][6]+1) || dif<1) continue;
		num++;
		if(dif<youngest){
			strcpy(name[0], name[2]);
			youngest=dif;
		}
		if(dif>oldest){
			strcpy(name[1], name[2]);
			oldest=dif;
		}
	}
	if(num!=0) printf("%d %s %s", num, name[1], name[0]);
	else printf("%d", num);
	return 0;
}
