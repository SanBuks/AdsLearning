// PATB1041 考试座位号
#include <cstdio>
#include <cstring>
typedef struct info{
	char id[20];
	int eid;
}Result;

Result result[1010];

int main(){
	int N, index, eidd;
	char str[20];
	scanf("%d", &N);
	for(int i=0; i<N; ++i){
		scanf("%s %d %d", str, &index, &eidd);
		result[index].eid=eidd;
		strcpy(result[index].id, str);
	}
	scanf("%d", &N);
	for(int i=0; i<N; ++i){
		scanf("%d", &index);
		printf("%s %d", result[index].id, result[index].eid);
		if(i<N-1)
			printf("\n");
	}
	return 0;
}
