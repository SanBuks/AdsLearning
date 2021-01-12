//PATB1009 说反话
#include <iostream>
#include <vector>
#include <cstring>
#include <iterator>
#include <algorithm>

using namespace std;
void amain(){
	char str[90];
	char word[90][90];
	gets_s(str, 90);
	int len=strlen(str);
	int r=0, h=0;
	for(int i=0; i<len; ++i){
		if(str[i]!=' ')
			word[r][h++]=str[i];
		else{
			word[r][h]='\0';
			r++;
			h=0;
		}
	}
	for(int i=--r; i>=0; i--){
		printf("%s", word[i]);
		if(i>0) printf(' ');
	}
}

int main(){
	vector<string> vec;
	string str;
	while(cin>>str)
		vec.push_back(str);
	for(auto it=vec.rbegin(); it!=vec.rend(); it++){
		cout<<*it;
		if(it+1!=vec.rend())
			cout<<' ';
	}
	return 0;
}


