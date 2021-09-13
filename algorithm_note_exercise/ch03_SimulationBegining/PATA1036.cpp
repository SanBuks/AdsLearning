// PATA1036 Boys vs Girls
#include <cstdio>
#include <cstring>
typedef struct stu{
	char name[30];
	char gender;
	char id[30];
	int score;
	bool exist;
}Stu;

Stu result[3];

int main(){
	result[0].exist=false;
	result[0].score=0x7fffffff;
	result[1].exist=false;
	result[1].score=-1;
	int N;	
	scanf("%d", &N);
	while(N--){
		scanf("%s %c %s %d", result[2].name, &result[2].gender, result[2].id, &result[2].score);
		if(result[2].gender=='F'&&result[2].score>=result[1].score){
			strcpy(result[1].name, result[2].name);
			strcpy(result[1].id, result[2].id);
			result[1].exist=true;
			result[1].score=result[2].score;
		}
		if(result[2].gender=='M'&&result[2].score<=result[0].score){
			strcpy(result[0].name, result[2].name);
			strcpy(result[0].id, result[2].id);
			result[0].exist=true;
			result[0].score=result[2].score;
		}
	}
	if(result[1].exist) printf("%s %s\n", result[1].name, result[1].id);
	else printf("Absent\n");
	if(result[0].exist) printf("%s %s\n", result[0].name, result[0].id);
	else printf("Absent\n");
	if(result[1].exist && result[0].exist) printf("%d", result[1].score-result[0].score);
	else printf("NA");
	return 0;
}
