#include <vector>
#include <iostream>
#include <numeric>

using namespace std;

class Solution {
 public:
  vector<int> getAverages(vector<int> &nums, int k) {
    vector<int> ans(nums.size(), -1);
    if (nums.size() <= k * 2) return ans;

    int num = k * 2 + 1;
    int start = 0; int mid = k; int end = k * 2;
    long long sum = accumulate(nums.begin(), nums.begin() + end + 1, 0LL);

    while (true) {
      ans[mid] = sum / num;

      sum -= nums[start];
      start += 1;
      mid += 1;
      end += 1;
      if (end == nums.size()) break;
      sum += nums[end];
    }
    return ans;
  }
};

int main() {

  Solution sol;
//  vector<int> vec{7, 4, 3, 9, 1, 8, 5, 2, 6};
//  vector<int> vec{100000};
  vector<int> vec{8};
//  auto item = sol.getAverages(vec, 3);
//  auto item = sol.getAverages(vec, 0);
  auto item = sol.getAverages(vec, 100000);
  for (auto &it : item) {
    cout << it << " ";
  }
  return 0;
}