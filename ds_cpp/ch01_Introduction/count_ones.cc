#include <iostream>
#include <cmath>
using ST = unsigned long;
constexpr ST kWordLength = sizeof(ST) * 8;

// 1. 移位 : O(logn)
ST CountOnes1(ST num) {
	ST sum = 0;
	while (num) {
		if (num & 1) 
			++sum;
		num >>= 1;
	}
	return sum;
}

// 2. & 消除二进制最低位的 '1' : O(r) r为 '1' 的实际个数
ST CountOnes2(ST num) {
	ST sum = 0;
	while (num) {
		++sum;
		num &= num - 1; // 将二进制最后的 1 转为 0
	}
	return sum;
}

// 返回 2^(n mod kWordLength) 
ST inline Pow(ST num) { 
	// 字面值 1 默认转换为 int 需要强制类型转换
	return 1UL << num; 
}

// 返回 分组长度为 n 的掩码 (分组长度指 连续 0 的长度)
ST inline Mask(ST num) {
	// n mod kWordLength = 0 发生 Pow(n) + 1 = 2 的退化情况
	if (!(num % kWordLength))
		return -1UL;
	return -1UL / (Pow(num) + 1); 
}

// 返回 分组长度为 2^n 的掩码 : 这里分组长度指 连续0的长度 
ST inline MaskExp(ST num) { 
	if (!(Pow(num) %  kWordLength)) 
		return -1UL;
	return -1UL / (Pow(Pow(num)) + 1); 
}

// 以 2^i 分组 计算各组类的 1 的个数
ST Round(ST num, ST length_mask) {
	return (num & MaskExp(length_mask)) + 
				 (num >> Pow(length_mask) & MaskExp(length_mask));
}

// 3. 迭代计算 1的 个数 
ST CountOnes3(ST num) {
	ST max_length_mask =
		static_cast<ST>(log2(kWordLength));
	for (ST length_mask = 0; 
			 length_mask != max_length_mask; 
	     ++length_mask)
		num = Round(num, length_mask);
	return num;
}

void TestCountOne(unsigned test_index) {
	std::cout << "WORD_LENGTH IS : " << kWordLength << "\n";

	unsigned a = 0xD3A596CBU;
	// countOnes( 1101 0011 1010 0101 1001 0110 1100 1011 ) = 18
	unsigned b = 0U;
	unsigned c = 1U;
	ST d = -1UL; 

	switch(test_index) {
		case 1: {
			std::cout << "TestCountOne1 : \n";
			std::cout << CountOnes1(a) << "\n"; // 18
			std::cout << CountOnes1(b) << "\n"; // 0
			std::cout << CountOnes1(c) << "\n"; // 1
			std::cout << CountOnes1(d) << "\n"; // 64
			break;
		}
		case 2: {
			std::cout << "TestCountOne2 : \n";
			std::cout << CountOnes2(a) << "\n"; // 18
			std::cout << CountOnes2(b) << "\n"; // 0
			std::cout << CountOnes2(c) << "\n"; // 1
			std::cout << CountOnes2(d) << "\n"; // 64
			break;
		}
		case 3: {
			std::cout << "TestCountOne3 : \n";
			std::cout << CountOnes3(a) << "\n"; // 18
			std::cout << CountOnes3(b) << "\n"; // 0
			std::cout << CountOnes3(c) << "\n"; // 1
			std::cout << CountOnes3(d) << "\n"; // 64
			break;
		}
		default: {
			std::cout << "Wrong Test Index ! \n";
		}
	}
}

int main() {
	TestCountOne(1);
	std::cout << "\n";
	TestCountOne(2);
	std::cout << "\n";
	TestCountOne(3);
	std::cout << "\n";
	return 0;
}