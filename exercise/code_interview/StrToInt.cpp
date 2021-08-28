#include <iostream>
#include <stdexcept>
#include <cctype>

// 补码加法溢出
// 补码乘法溢出
// 野指针判断
// 非法字符判断

inline bool tmult_ok(const int &a, const int &b){ int p=a*b; return !a || (p/a==b); } 
inline bool tadd_ok(const int &a, const int &b){ 
	return !(a<0 && b<0 && (a+b>=0) ) && !(a>0 && b>0 && (a+b)<0 );
}
	
int StrToInt(char *string){
	bool nflag=false; 
	int sum=0;
	char *p=string;
	if(!string) throw std::runtime_error("StrToInt() : nullptr !\n");
	if(*string=='\0') throw std::runtime_error("StrToInt() : empty_str !\n");
	if(*p=='-') { nflag=true; p++; }

	for(; *p!='\0'; ++p){
		if(isdigit(*p)){
			if(tmult_ok(sum, 10)) sum*=10;
			else throw std::runtime_error("StrToInt() : overflow !\n");

			int delta; 
			if(nflag) delta=-(*p-'0');
			else delta=*p-'0';

			if(tadd_ok(sum, delta)) sum+=delta;
			else throw std::runtime_error("StrToInt() : overflow !\n");

		} else throw std::runtime_error("StrToInt() : not vailed number !\n");
	}
	return sum;
}

int main(){
	char *p1=nullptr;
	char p2[13]="-23100";
	char p3[13]="-11111111111";
	char p4[13]="1111+-/*+";
	std::cout<<StrToInt(p3);
	return 0;
}
