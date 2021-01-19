// PATB1004 成绩排名
#include <cstring>
#include <cstdio>
typedef struct stu{
	char name[20];
	char id[20];
	int score;
}Stu;
Stu result[3];
int main(){
	int N;
	scanf("%d", &N);

	scanf("%s %s %d", result[0].name, result[0].id, &result[0].score);
	strcpy(result[1].name, result[0].name);
	strcpy(result[1].id, result[0].id);
	result[1].score=result[0].score;

	for(int i=0; i<N-1; i++){
		scanf("%s %s %d", result[2].name, result[2].id, &result[2].score);
		if(result[2].score>result[1].score){
			strcpy(result[1].name, result[2].name);
			strcpy(result[1].id, result[2].id);
			result[1].score=result[2].score;
		}
		if(result[2].score<result[0].score){
			strcpy(result[0].name, result[2].name);
			strcpy(result[0].id, result[2].id);
			result[0].score=result[2].score;
		}
	}
	printf("%s %s\n", result[1].name, result[1].id);
	printf("%s %s", result[0].name, result[0].id);
	return 0;
}
