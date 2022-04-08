#include <queue>
#include <iostream>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
 public:
  static vector<int> topKFrequent(vector<int> &nums, int k) {
    vector<int> vec; vec.reserve(k);
    unordered_map<int, int> frequency;
    for (const auto &item : nums) {
      ++frequency[item];
    }

    auto cmp = [](const pair<const int, int>&lhs, const pair<int, int>&rhs) {
                  return lhs.second > rhs.second; };
    priority_queue<pair<int, int>, deque<pair<int, int>>, decltype(cmp)> qu(cmp);

    for (const auto &item : frequency) {
      if (qu.size() < k || item.second > qu.top().second) {
        qu.push(item);
        if (qu.size() > k) {
          qu.pop();
        }
      }
    }

    while (!qu.empty()) {
      vec.push_back(qu.top().first);
      qu.pop();
    }
    reverse(vec.begin(), vec.end());
    return vec;
  }
};

int main() {
  vector<int> vec{1, 1, 1, 2, 2, 3};
  auto res = Solution::topKFrequent(vec, 2);
  for (auto &item : res) {
    cout << item << " ";
  }
  cout << "\n";
  return 0;
}