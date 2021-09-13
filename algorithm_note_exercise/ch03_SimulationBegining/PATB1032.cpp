// PATB 1032 挖掘机技术哪家强
#include <cstdio>
#include <cstring>

int school[100010][2]={};

int main(){
	int n, score, id;
	scanf("%d", &n);
	while(n-->0){
		scanf("%d %d", &id, &score);
		school[id][0]+=score;
		school[id][1]=1;
	}

	int maxscore, maxid;
	maxscore=-1;
	for(int i=1; i<100010; i++){
		if(school[i][1]!=0 && school[i][0]>maxscore){
			maxscore=school[i][0];
			maxid=i;
		}
	}
	printf("%d %d", maxid, maxscore);
	return 0;
}
