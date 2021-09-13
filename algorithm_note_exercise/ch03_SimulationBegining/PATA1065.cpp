// PATA1065 A+B and C (64bit)
#include <cstdio>
#include <string>
#include <iterator>

const int CALC_CON[2][2]={ 1, 2, 3, 4 };

using std::string;
using std::begin;
using std::end;

class BigN{
private:
	string number;  //  存储绝对值 00023 => 23
	int nn;  // 非负记号(not negative) >=0 : 1  <0 : 0
	
	BigN add(const BigN&, const BigN&);  // 非负整数相加
	BigN minus(const BigN&, const BigN&); // 非负整数 大减小
	bool compare(const string &a1, const string &a2){
		if(a1.size()>a2.size()) return true; 
		else if(a1.size()<a2.size()) return false;
		return a1>a2;
	}

public:
	BigN(const string &s="0"):number(s){ 
		nn=(number[0]=='-'?0:1);  
		if(!nn) number.erase(0, 1);
	}
	BigN(const char *p):number(string(p)){
		nn=(number[0]=='-'?0:1);  
		if(!nn) number.erase(0, 1);
	}

	BigN operator+(const BigN &);
	bool operator>(const BigN &);
	int isnn() const { return nn; }
	void print(){ 
		if(!nn) printf("-"); 
		for(auto it=number.begin(); it!=number.end(); it++)
			printf("%c", *it);
		printf("\n");
	}
};

BigN BigN::add(const BigN &n1, const BigN &n2){  // 非负整数 加
	string result=n1.number;
	int one=0;  // 进位
	auto it1=result.rbegin();

	// 遍历一边最短值 逐位相加
	for(auto it2=n2.number.rbegin(); it2!=n2.number.rend(); it1++,it2++){
		if(*it1+*it2-96+one>10){ 
			*it1=(*it1+*it2-96+one)%10+'0';
			one=1; 
		}else{
			*it1=(*it1+*it2-96+one)%10+'0';
			one=0; 
		} 
	}

	// 处理进位
	while(one!=0 && it1!=result.rend() ){
		(*it1)++;
		if(*it1>'9'){
			*it1='0'; 
			one=1;
		}
		it1++;
	}

	// 添加最后的进位
	if(one==1&&it1==result.rend())
		result.insert(0, 1, '1');

	BigN Result(result);
	Result.nn=n1.nn;
	return Result;
}

BigN BigN::minus(const BigN &n1, const BigN &n2){ // 非负整数 大减小
	string result=n1.number;
	int one=0;  // 减位
	auto it1=result.rbegin();

	// 遍历一边最短值 逐位相减
	for(auto it2=n2.number.rbegin(); it2!=n2.number.rend(); it1++,it2++){
		if(*it1-*it2+one<0){ 
			*it1=*it1-*it2+one+10+48;
			one=-1; 
		}else{
			*it1=*it1-*it2+one+48;
			one=0; 
		} 
	}

	// 处理减位
	while(one==-1 && it1!=result.rend()){
		(*it1)--;
		if(*it1<'0'){
			(*it1)+=10; 
			one=-1;
		}else one=0; 
		it1++;
	}

	// 处理多余的零
	while(result[0]=='0'&&result.size()>1)
		result.erase(0, 1);
	BigN Result(result);
	return Result;
}

BigN BigN::operator+(const BigN &rhs){
	switch(CALC_CON[nn][rhs.nn]){
		case 1:  // 两个负数相加
		case 4:  // 两个正数相加
			if(rhs.number.size()>number.size()) 
				return add(rhs, *this);
			return add(*this, rhs);
			break;
		case 2: 
		case 3:{
			BigN result;
			if(!compare(number, rhs.number)){
				result=minus(rhs, *this);
				result.nn=rhs.nn;
			}else{
				result=minus(*this, rhs);
				result.nn=nn;
			}
			if(result.number[0]=='0'&&result.number.size()==1)
				result.nn=1;
			return result;
			break;
		}
		default:
			break;
	}
}

bool BigN::operator>(const BigN &rhs){
	switch(CALC_CON[nn][rhs.nn]){
		case 1:  // 两个负数相比
			return !compare(number, rhs.number);
			break;
		case 4:  // 两个正数相比
			return compare(number, rhs.number);
			break;
		case 2: 
		case 3:
			if(nn==0)	return false;
			else return true;
			break;
		default:
			break;
	}
}

char a[22];
char b[22];
char c[22];

int main(){
	int N;
	scanf("%d", &N);
	for(int ii=1; ii<=N; ++ii){
		scanf("%s %s %s", a, b, c);
		BigN aa(a); BigN bb(b); BigN cc(c); 
		auto it=aa+bb;
		if(it>cc) printf("Case #%d: true", ii);
		else printf("Case #%d: false", ii);
		if(ii<N) printf("\n");
	}
	return 0;
}
