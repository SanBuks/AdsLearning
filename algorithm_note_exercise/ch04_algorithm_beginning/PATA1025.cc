// 1025 PAT Ranking
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;
struct Student{
	char id[15];
	int score;
	int final_rank;
	int location_num;
	int local_rank;
}stu[30010];

bool cmp(const Student &s1, const Student &s2){
	if(s1.score!=s2.score)	return s1.score>s2.score;
	else return strcmp(s1.id, s2.id)<0;
}

int main(){
	int num_location;
	int num_lostu; 
	int sum=0;
	scanf("%d", &num_location);
	for(int i=0; i<num_location; ++i){
		scanf("%d", &num_lostu);
		if(num_lostu<1) continue;
		int begin=sum;  // 当前考场 学生开始位置
		for(int j=0; j<num_lostu; ++j){
			stu[begin+j].location_num=i+1;  // 读入 考场号
			scanf("%s %d", stu[begin+j].id, &stu[begin+j].score);  // 读入 id 和 分数
		}
		sort(stu+begin, stu+begin+num_lostu, cmp);  // 按分数排序
		stu[begin].local_rank=1;  // 设置第一排名
		for(int j=1; j<num_lostu; ++j){
			if(stu[begin+j].score!=stu[begin+j-1].score)  // 与上一位相同 不同则设为 排序数
				stu[begin+j].local_rank=j+1;
			else stu[begin+j].local_rank=stu[begin+j-1].local_rank;  // 与上一位相同设为 同一个排名
		}
		sum=begin+num_lostu;  // 更新 考场开始位置
	}
	sort(stu, stu+sum, cmp);  // 总体排序
	printf("%d\n", sum);
	if(sum!=0){  // 没有人直接返回 
		stu[0].final_rank=1;
		printf("%s %d %d %d\n", stu[0].id, stu[0].final_rank, stu[0].location_num, stu[0].local_rank);
		for(int j=1; j<sum; ++j){
			if(stu[j].score!=stu[j-1].score)
				stu[j].final_rank=j+1;
			else stu[j].final_rank=stu[j-1].final_rank;
			printf("%s %d %d %d\n", stu[j].id, stu[j].final_rank, stu[j].location_num, stu[j].local_rank);
		}
	}
	return 0;
}
