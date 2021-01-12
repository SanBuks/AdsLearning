// PATB1018 锤子剪刀布
#include <cstdio>
int result[2][6]={}; 
// 0-2 win draw lose 
// 3-5 B C J
int judge(const char &c1, const char &c2){
	if(c1==c2) return 0; // 两者相同返回平局 0
	if( (c1=='B'&&c2=='C') ||
		(c1=='C'&&c2=='J') ||
		(c1=='J'&&c2=='B') ) return 1; // 甲赢了 返回 1
	return -1; // 乙赢了 返回-1
}
int char2int(const char &c){
	if(c=='B') return 3;
	if(c=='C') return 4;
	if(c=='J') return 5;
}
char int2char(const int &i){
	if(i==3) return 'B';
	if(i==4) return 'C';
	if(i==5) return 'J';
	return 'B';
}
int mostWinGesture(const int &index){
	int max=result[index][3];
	int maxid=3;
	for(int i=4; i<6; ++i){
		if(result[index][i]>max){
			maxid=i;
			max=result[index][i];
		}
	}
	return maxid;
}
int main(){
	int N;
	char c1, c2;
	scanf("%d\n", &N);
	while(N--){
		if(N>0) scanf("%c %c\n", &c1, &c2);	
		else scanf("%c %c", &c1, &c2); // 最后一次不用读取换行符
		switch(judge(c1, c2)){
			case -1: 
				result[1][0]++;  // 乙赢局++
				result[0][2]++;  // 甲输局++
				result[1][char2int(c2)]++; // 乙赢的手势次数++
				break;
			case 0:
				result[1][1]++;  // 乙平局++
				result[0][1]++;  // 甲平局++
				break;
			case 1: 
				result[0][0]++;  // 甲赢局++
				result[1][2]++;  // 乙输局++
				result[0][char2int(c1)]++;  // 甲赢的手势次数++
				break;
			default: break;
		}
	}
	printf("%d %d %d\n", result[0][0], result[0][1], result[0][2]);	
	printf("%d %d %d\n", result[1][0], result[1][1], result[1][2]);	
	printf("%c %c",	int2char(mostWinGesture(0)), int2char(mostWinGesture(1)));  	
	return 0;
}
