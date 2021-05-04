#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <utility>
#include <chrono>

using namespace std;
using SizeType = vector<int>::size_type;

// 1. 利用标志符提前判断是否已经排序
void BubbleSortA(vector<int> &vec) { 
	if (vec.empty()) return;
	bool sorted = false;
	for (SizeType num = vec.size(); (sorted = !sorted); --num) {
		sorted = true;
		for (SizeType i = 0; i < num - 1; ++i) {
			if (vec[i] > vec[i+1]) {
				std::swap(vec[i], vec[i+1]);
				sorted = false;
			}
		}
	}
}

// 2. 记录最后排序位置跳过局部排序元素
void BubbleSortB(vector<int> &vec) {
	if (vec.empty()) return;
	for (SizeType pos = vec.size(), last_swap; 1 < pos; pos = last_swap){
		last_swap = 1;
		for (SizeType i = 0; i < pos - 1; ++i) {
			if (vec[i] > vec[i + 1]) {
				swap(vec[i], vec[i + 1]);
				last_swap = i + 1;
			}
		}
	}
}

int main(){
	vector<int> vec{3,2,5,4,7,8,6,1,3,1,6,498};
	auto print = [](const int &item) { cout << item << " "; };		
	unsigned long seeds = 
	  chrono::system_clock::now().time_since_epoch().count();
	default_random_engine e(seeds);

	shuffle(vec.begin(), vec.end(), e);
	for_each(vec.cbegin(), vec.cend(), print);
	cout << "\n";
	BubbleSortA(vec);
	for_each(vec.cbegin(), vec.cend(), print);
	cout << "\n";

	shuffle(vec.begin(), vec.end(), e);
	for_each(vec.begin(), vec.end(), print);
	cout << "\n";
	BubbleSortB(vec);
	for_each(vec.begin(), vec.end(), print);
	cout << "\n";

	return 0;
}
