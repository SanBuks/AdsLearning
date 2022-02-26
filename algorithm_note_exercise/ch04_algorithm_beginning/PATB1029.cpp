// PAT 1029 旧键盘
#include <cstdio>
using namespace std;
bool hs[73]={};
char input[90]={};
char output[90]={};

int calcp(const char &c){
	if(c<='z' && c>='a') return c-'a';
	else if(c<='Z' && c>='A') return 26+c-'A';
	else if(c<='9' && c>='0') return 52+c-'0';
	else return 62;
}

int main(){
	gets(input);
	gets(output);
	for(int i=0; *(i+output)!='\0'; ++i)
		hs[calcp(*(i+output))]=true;
	for(int i=0; *(i+input)!='\0'; ++i)
		if(hs[calcp(*(i+input))]!=true){
			printf("%c", *(i+input));
			hs[calcp(*(i+input))]=true;
		}
	return 0;
}
