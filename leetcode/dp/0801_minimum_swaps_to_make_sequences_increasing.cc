#include <vector>
#include <limits>
#include <iostream>
using namespace std;

class Solution {
 public:
  int minSwap(vector<int> &nums1, vector<int> &nums2) {
    const int size = static_cast<int>(nums1.size());
    const int kNAN = numeric_limits<int>::max();

    vector<int> keep(size, kNAN);
    vector<int> swap(size, kNAN);

    keep[0] = 0;
    swap[0] = 1;

    for (int i = 1; i < size; ++i) {

      // keep 更新
      if (nums1[i] > nums1[i - 1] && nums2[i] > nums2[i - 1] && keep[i - 1] != kNAN) {
        // 如果可以从上一个原序维持
        keep[i] = keep[i - 1];
      }
      if (nums1[i] > nums2[i - 1] && nums2[i] > nums1[i - 1] && swap[i - 1] != kNAN) {
        // 如果可以从上一个交换维持
        keep[i] = min(keep[i], swap[i - 1]);
      }

      // swap 更新
      if (nums2[i] > nums1[i - 1] && nums1[i] > nums2[i - 1] && keep[i - 1] != kNAN) {
        // 如果可以从上一个原序交换
        swap[i] = keep[i - 1] + 1;
      }
      if (nums2[i] > nums2[i - 1] && nums1[i] > nums1[i - 1] && swap[i - 1] != kNAN) {
        // 如果可以从上一个交换交换
        swap[i] = min(swap[i], swap[i - 1] + 1);
      }
    }

    return min(keep[size - 1], swap[size - 1]);
  }
};


int main() {
  Solution sol;
//  vector<int> vec1{1, 3, 5, 4};
//  vector<int> vec2{1, 2, 3, 7};

//  vector<int> vec1{0, 3, 5, 8, 9};
//  vector<int> vec2{2, 1, 4, 6, 9};

  vector<int> vec1{0, 1, 4, 6, 8};
  vector<int> vec2{1, 2, 2, 7, 10};

  cout << sol.minSwap(vec1, vec2) << "\n";
  return 0;
}