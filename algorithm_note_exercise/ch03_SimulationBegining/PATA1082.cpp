// PATA1082 Read Number in Chinese
#include <iostream>
#include <string>
#include <vector>
using namespace std;
string number[]=
	{"ling", "yi","er", "san", "si", "wu", "liu", "qi", "ba", "jiu"};
string units[]=
	{"Yi", "Wan", "Qian", "Bai", "Shi"};
vector<string> vec;

int main(){
	long long n;
	bool flag=false;
	cin>>n;
	// 处理符号位
	if(n==0) { cout<<"ling"; return 0; }
	if(n<0) { vec.push_back("Fu"); n=-n; }
	// 处理亿位
	if(n/100000000){
		vec.push_back(number[n/100000000]);
		vec.push_back(units[0]);
		flag=true;  // 后者可以取零
		n%=100000000;
	}
	// 处理万位
	if(n/10000){
		int temp=n/10000;	
		if(temp/1000){ 
			vec.push_back(number[temp/1000]); 
			vec.push_back(units[2]);
			flag=true;
			if(temp%1000==0) // 能够被千位整除则直接打印万位
				goto UNIT;
		} else { 
			if(flag) vec.push_back(number[0]); // 规避前者是零的情况
			flag=false;
		}

		temp%=1000;
		if(temp/100){ 
			vec.push_back(number[temp/100]);
			vec.push_back(units[3]);
			flag=true;
			if(temp%100==0)
				goto UNIT;
		} else {
			if(flag) vec.push_back(number[0]);
			flag=false;
		}

		temp%=100;
		if(temp/10){
			vec.push_back(number[temp/10]);
			vec.push_back(units[4]);
			flag=true;
			if(temp%10==0)
				goto UNIT;
		} else {
			if(flag) vec.push_back(number[0]);
			flag=false;
		}
		if(temp%=10){
			vec.push_back(number[temp]);
			flag=true;
		}
UNIT:
		vec.push_back(units[1]);
		n%=10000;
	}
	// 处理个位
	if(n){
		int temp=n;
		if(temp/1000){ 
			vec.push_back(number[temp/1000]); 
			vec.push_back(units[2]);
			flag=true;
			if(temp%1000==0)
				goto UNITT;
		} else { 
			if(flag) vec.push_back(number[0]);
			flag=false;
		}

		temp%=1000;
		if(temp/100){ 
			vec.push_back(number[temp/100]);
			vec.push_back(units[3]);
			flag=true;
			if(temp%100==0)
				goto UNITT;
		} else {
			if(flag) vec.push_back(number[0]);
			flag=false;
		}

		temp%=100;
		if(temp/10){
			vec.push_back(number[temp/10]);
			vec.push_back(units[4]);
			flag=true;
			if(temp%10==0)
				goto UNITT;
		} else {
			if(flag) vec.push_back(number[0]);
			flag=false;
		}
		if(temp%=10){
			vec.push_back(number[temp]);
			flag=true;
		}
UNITT:	;
	}
	for(auto it=vec.begin(); it!=vec.end(); ++it){
		cout<<*it;
		if(it!=--vec.end()) cout<<" ";
	}
	return 0;
}
