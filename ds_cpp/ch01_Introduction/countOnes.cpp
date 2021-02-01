#include <iostream>
#include <bitset>
// O(logn)
unsigned countOnes_1(unsigned n){
	unsigned sum=0;
	while(n){
		if(n&1) sum++;
		n>>=1;
	}
	return sum;
}

// O(r) r= 1的实际个数
unsigned countOnes_2(unsigned n){
	int sum=0;
	while(n){
		++sum;
		n&=n-1;
	}
	return sum;
}

// 返回 2^n次方  n<=31
unsigned inline pow(size_t n){ return 1<<n; }

/* 	
 	返回 : (1/2)*length(000...0111...1) = 2^n 掩码 
	原理 :
	11111/100..01 = 掩码
   	(1/2)*length(000...0111...1)=(length(100..01)-1)
	length(2^n+1)=length(100...01)=n	
	length(2^2^n+1)=length(100...01)=2^n
*/ 
unsigned inline mask(size_t n){ return (unsigned)(-1)/(pow(pow(n))+1); }

/* 	
    返回 以 2^i = (1/2)*length(00...011...1) 为分组, 统计分组内1的个数(个数以一半为实际数值) 如:
   	0110 为分组, 前2位代表为1  后两位代表为2  数值不超过2^(n-1) n为半分组长度
*/
unsigned round(unsigned n, size_t i){
	return (n&mask(i))+(n>>pow(i)&mask(i));
}

unsigned countOnes_3(unsigned num){
	// 4=log2(sizeof(unsigned)*8)-1
	for(int i=0; i<=4; ++i)
		num=round(num, i);
	return num;
}

int main(){
	unsigned a=0xD3A596CB;
	unsigned b=0;
	unsigned c=1;
	unsigned d=0xffffffff;
	std::cout<<countOnes_3(a)<<std::endl;
	std::cout<<countOnes_3(b)<<std::endl;
	std::cout<<countOnes_3(c)<<std::endl;
	std::cout<<countOnes_3(d)<<std::endl;
	return 0;
}
