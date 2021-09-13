#include <iostream>
#include <utility>
#include <set>
#include <vector>

using std::vector;

// book 1. 找出任意一个重复数字 循环查找
bool IsDupli(int *a, int n, int *out){
	if(!a || n<=0) return false;  // 数量 字符串不够

	for(int i=0; i<n; ++i)        // 值不符合要求
		if(a[i]<0 || a[i]>n-1)
			return false;

	for( int i=0; i<n; ++i){
		if(i==a[i]) continue;

		// 应当交换到位置上的数与本身相同则重复
		else if(a[a[i]]==a[i]){ 
			*out=a[i];
			return true;
		}
		else{		
			std::swap(a[i], a[a[i]]);
			i--;
		}
	}
	return false;
}

// book 2. 找出任意一个重复数字 不修改 二分法查找 
// numbers 指向 length 个数组,  数的范围 在 [1, length-1] 中
int FindDupli(const int *numbers, int length){
	if(!numbers || length <= 0) return -1;
	int start = 1, end = length - 1;  // 数值的范围
	int count = 0;
	while(start < end){
		int mid = (start + end) >> 1;
		count = 0;
		for(int i = 0; i < length; ++i)
			if(start <= numbers[i] && numbers[i] <= mid)
				++count;
		if(count > mid - start + 1)
			end = mid;
		else
			start = mid + 1;
	}
	return start;
}

int main(){
	int *p=new int;
	int a[7]={2, 3, 1, 0, 2, 5, 3};
	IsDupli(a, 7, p);
	std::cout<<*p<<std::endl;

	int b[8]={4,1,5,4,3,2,6,7};
	std::cout<<FindDupli(b, 8)<<std::endl;
	return 0;
}