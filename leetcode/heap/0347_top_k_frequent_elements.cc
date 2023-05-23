#include <queue>
#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
 public:
  vector<int> ans;
  unordered_map<int, int> freq;
  vector<int> topKFrequent(vector<int> &nums, int k) {
    ans.clear();
    freq.clear();

    auto cmp = [](const pair<int, int> &lhs, const pair<int, int> &rhs) {
      return lhs.second > rhs.second;
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> heap(cmp);

    for (const auto &item : nums) {
      if (freq.find(item) != freq.end()) {
        ++freq[item];
      } else {
        freq[item] = 0;
      }
    }

    for (const auto &item : freq) {
      heap.emplace(item);
    }

    for (int i = 0; i < k; ++i) {
      auto item = heap.top();
      ans.push_back(item.first);
      heap.pop();
    }

    return ans;
  }
};