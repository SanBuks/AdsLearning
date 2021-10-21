#include "./Stack.h"
#include "./Rpn.h"

// 测试栈的基础操作
void stackTest(){
	Stack<int> s;
	s.push(1);
	s.push(2);
	s.push(3);
	s.top()=100;
	while(!s.empty())
		std::cout<<s.pop()<<"\n"; // 100 2 1
}
// 测试进制转换
void convertTest(){
	convert(2020, 16); // 7E4
	convert(782369, 8); // 2770041
	convert(23, 2); // 10111
	convert(-2, 2); // -10
}
// 测试递归括号匹配
void parenTest(){
	const char str1[]="12+((15+16))-((12-19)+72)-2"; // 27
	std::cout<<paren(str1, 0, 26)<<'\n'; // true;
	const char str2[]="12+((15+16))-((12)19)+72)-2"; // 27
	std::cout<<paren(str2, 0, 26)<<'\n'; // flase;
}

// 测试递归括号匹配
void paren_iterationTest(){
	const char str1[]="12+((15+16))-((12-19)+72)-2"; // 27
	std::cout<<paren_iteration(str1, 0, 26)<<'\n'; // true;
	const char str2[]="12+((15+16))-((12)19)+72)-2"; // 27
	std::cout<<paren_iteration(str2, 0, 26)<<'\n'; // flase;
}

// 测试从字符串中读取数字 
void readNumberTest(){
	Stack<double> stk;
	char str[]="123.22323";
	char *s=str;
	readNumber(s, stk);
	std::cout<<stk.pop();
}

// 测试向字符串中添加字符和数字
void appendTest(){
	char *str=(char*)malloc(sizeof(char)*4);
	strcpy(str,"123");
	append(str, '4');
	std::cout<<str<<'\n';
	append(str, 12.254);
	std::cout<<str<<'\n';
}

// 测试逆波兰表达式计算值
void evaluateTest(){
	//char str[]="((0+(1+23)/4*5*67-8+9))";
	char str[]="(0!+1)*2^(3!+4)-(5!-67-(8+9))";
	//char str[]="0!+2!";
	char *Rpn=(char*)malloc(sizeof(char)*1);		*Rpn='\0';
	std::cout<<evaluate(str, Rpn)<<'\n';
	std::cout<<Rpn<<'\n';
}

int main(){
	evaluateTest();
	return 0;
}
