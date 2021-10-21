#include <iostream>
using ST = unsigned long;

//  O(n)
ST Power2(ST number) {
	ST result = 1;
	while (number--) {
		result <<= 1;
	}
	return result;
}

//  O(logn)
ST Power2_R(ST number) {
	if (!number) 
	  return 1;
	ST result = Power2(number>>1);
	result *= result;
	return (number & 1) ? result << 1 : result;
}

//  O(logn)
ST Power2_I(ST number) {
	ST result = 1, multiplier = 2;
	while (number) {
		if (number & 1) {
			result *= multiplier;	
		}
		number >>= 1;
		multiplier *= multiplier;
	}
	return result;
}


int main(){
	std::cout << Power2_I(32) << "\n";
	return 0;
}
