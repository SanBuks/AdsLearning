# 第四章 栈

### 1. 概述
- 栈与队列是向量或列表的特殊线性序列结构，操作仅限于某个特定端，各自具有先进后出和先进先出的特性。
- 递归本身既为系统隐式维护函数栈，由于保存参数等信息会导致不必要消耗，可以通过迭代模拟递归本身，通过剪裁提高效率。
### 2. 数据部分
```c++
template <typename T>
class Stack: public Vector<T>{
public:
	using Vector<T>::insert;
	using Vector<T>::size;
	using Vector<T>::remove;
	using Vector<T>::operator[];
	// 出栈或访问时需要判断是否为空
	using Vector<T>::empty; 

	void push(T const &e){ insert(size(), e); } 
	T pop(){ return remove(size()-1); } 
	T &top(){ return (*this)[size()-1]; }
};

/* -------------------操作符优先级表-----------------------*/
const int N_OPT=9;  // 定义9个操作符数 分别为 + - * / ^ ! ( ) EOE 
typedef enum{ NON=-1, ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE } Operator;
const char pri[N_OPT][N_OPT]={ // 横向当前操作符 纵向栈顶操作符
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

```
### 3. 应用函数
#### 3.1 二进制转换
```c++
// 十进制n转化为base进制数并打印出来
void convert(long long n, int base){
	if(base<2||base>16) return ; // base 范围[2,16]
	bool flag=true; // 是否为正或负
	if(n<0) { flag=false; n=-n; }
	const char OP[]={ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E'};
	Stack<char> s;
	while(0<n){
		s.push(OP[(int)n%base]);
		n/=base;
	}
	if(!flag) std::cout<<-n<<" to "<<base<<" mode : -";
	else std::cout<<n<<" to "<<base<<" mode : ";
	while(!s.empty())
		std::cout<<s.pop();
	std::cout<<"\n";
}
```

#### 3.2 括号匹配(递归)
```c++
bool paren(const char exp[], int lo, int hi){  // 检查表达式[lo, hi] 范围是否括号匹配
	// str= S1+S2+S3+S4 其中 S1和S4 没有括号 S2括号匹配 当且仅当S3括号匹配,str括号匹配
	trim(exp, lo, hi); 
	if(lo>hi) return true; // 没有括号返回真
	if(exp[lo]!='(') return false;  // 保证 前后括号匹配
	if(exp[hi]!=')') return false;

	int mi=divide_exp(exp, lo, hi);
	if(mi>hi) return false;
	return paren(exp, lo+1, mi-1) && paren(exp, mi+1, hi);
}

void trim(const char exp[], int &lo, int &hi){  // 去除S1 和 S2
	while( (lo<=hi) && (exp[lo]!='(') && (exp[lo]!=')') ) lo++;
	while( (lo<=hi) && (exp[hi]!='(') && (exp[hi]!=')') ) hi--; 
}

int divide_exp(const char exp[], int lo, int hi){ // 分隔 返回S2匹配的最后位置
	int mi=lo, crc=1;
	while((crc>0) && (++mi<hi)){  // 由于前后括号匹配 默认返回最后一个位置
		if(exp[mi]=='(') crc++;
		if(exp[mi]==')') crc--;
	}
	return mi; // mi>hi则 S1不匹配
}
```

#### 3.3 括号匹配(迭代)
```c++
bool paren_iteration(const char exp[], int lo, int hi){
	Stack<char> s;
	for(int i=lo; i<=hi; ++i){
		switch(exp[i]){
			case '(':
			case '[':
			case '{':	s.push(exp[i]); break;
			case ')': 	if(s.empty() || s.pop()!='(') return false; break;
			case ']': 	if(s.empty() || s.pop()!='[') return false; break;
			case '}': 	if(s.empty() || s.pop()!='{') return false; break;
			default : 	break;	
		}
	}
	return s.empty();
}
```

#### 3.4 逆波兰表达式
```c++

```









