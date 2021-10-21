#pragma once
#include <iostream>
#include <cmath>
#include <cstring>
#include "Stack.h"

const int N_OPT=9;
typedef enum{ NON=-1, ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE } Operator;
// 					   +    -    *    /    ^    !    (    )   \0

const char pri[N_OPT][N_OPT]={ // 横向是当前操作符 纵向是栈顶操作符
// 			+	-	*	/	^	!	(	)	\0
/* + */    '>','>','<','<','<','<','<','>','>',
/* - */    '>','>','<','<','<','<','<','>','>',
/* * */    '>','>','>','>','<','<','<','>','>',
/* / */    '>','>','>','>','<','<','<','>','>',
/* ^ */    '>','>','>','>','<','<','<','>','>',  // 2^3^5 <=> 2^(3^5)
/* ! */    '>','>','>','>','>','>',' ','>','>',  // 3!!+3=723  不存在 3!(1+2)情况
/* ( */    '<','<','<','<','<','<','<','=',' ',
/* ) */    ' ',' ',' ',' ',' ',' ',' ',' ',' ',
/* \0*/    '<','<','<','<','<','<','<',' ','='
};

// 字符 转换成 优先级表中的 下标
int c2n(char c){
	switch(c){
		case '+': return ADD; break;
		case '-': return SUB; break;
		case '*': return MUL; break;
		case '/': return DIV; break;
		case '^': return POW; break;
		case '!': return FAC; break;
		case '(': return L_P; break;
		case ')': return R_P; break;
		case '\0': return EOE; break;
		default : exit(0);
	}
}
char orderBetween(char o1, char o2){
	return pri[c2n(o1)][c2n(o2)];
}

// 从字符串中读取数字
void readNumber(char * &S, Stack<double> &stk){
	stk.push((double)(*S-'0')); // 先放入数字
	while(isdigit(*(++S))){
		stk.top()*=10;
		stk.top()+=(double)(*S-'0');
	}

	if('.'!=*S) return ;  // 如果没有小数部分则返回
	double fraction=1;
	while(isdigit(*(++S)))
		stk.top()+=(double)(*S-'0')*(fraction/=10);
}

// 单目计算
double calc(char c, double n){
	switch(c){
		case '!' :{
			if(0==n) return 1;
			int sum=n;
			while(--n>0)
				sum*=n;
			return (double)sum;
			}
			break;
		default : exit(0);
	}
}
// 双目计算
double calc(double n1, char c, double n2){
	switch(c){
		case '+': return n1+n2; break;
		case '-': return n1-n2; break;
		case '*': return n1*n2; break;
		case '/': return n1/n2; break;
		case '^': return pow(n1, n2); break;
		default : exit(0);
	}
}

// 存储逆波兰表达式
void append(char * &Rpn, char c){
	int n=strlen(Rpn);
	Rpn=(char*)realloc(Rpn, sizeof(char)*(n+3));
	sprintf(Rpn+n, "%c ", c);
	Rpn[n+2]='\0';
}
void append(char * &Rpn, double num){
	int n=strlen(Rpn);
	char buf[64];
	if(num!=(double)(int)num)
		sprintf(buf, "%.2f \0", num);
	else
		sprintf(buf, "%.0f \0", num);
	Rpn=(char*)realloc(Rpn, sizeof(char)*(n+strlen(buf)+1));
	strcat(Rpn, buf);
}

// 计算算数表达式
double evaluate(char *S, char * &Rpn){
	Stack<double> opn; 
	Stack<char> opt;
	opt.push('\0');

	while(!opt.empty()){
		if(isdigit(*S)){
			readNumber(S,opn);
			append(Rpn,opn.top());
		}else{
			switch(orderBetween(opt.top(), *S)){
				case '<' :	opt.push(*S++); break;
				case '=' : 	opt.pop(); S++; break;
				case '>' :	{
							auto op=opt.pop();
							append(Rpn, op);
							if('!'==op){
								auto number=opn.pop();
								opn.push(calc(op,number));
						   	}else{
								auto number2=opn.pop();
								auto number1=opn.pop();
								opn.push(calc(number1, op, number2));
							}
							break;
				}
				default : exit(0);
			}
		}
	}
	return opn.pop();
}
