#include <vector>
#include <queue>
#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

class Solution {
 public:
  vector<vector<int>> kSmallestPairs(vector<int> &nums1, vector<int> &nums2, int k) {
    vector<vector<int>> ans;

    using Pair = pair<int, pair<int, int>>;
    auto func = [](const Pair &lhs, const Pair &rhs) {
      if (lhs.first > rhs.first) return true;
      else if (lhs.first == rhs.first) return lhs.second.first < rhs.second.first;
      else return false;
    };
    unordered_set<string> hash;
    priority_queue<Pair, vector<Pair>, decltype(func)> heap(func);
    hash.insert("0-0");
    heap.push({nums1[0] + nums2[0], {0, 0}});

    while (!heap.empty() && ans.size() < k) {
      auto pair = heap.top(); heap.pop();
      ans.push_back({nums1[pair.second.first], nums2[pair.second.second]});

      int i = pair.second.first;
      int j = pair.second.second;

      if (i + 1 < nums1.size() && j < nums2.size()) {
        string key = to_string(i + 1) + "-" + to_string(j);
        if (hash.find(key) == hash.end()) {
          hash.insert(key);
          heap.push({nums1[i + 1] + nums2[j], {i + 1, j}});
        }
      }
      if (i < nums1.size() && j + 1 < nums2.size()) {
        string key = to_string(i) + "-" + to_string(j + 1);
        if (hash.find(key) == hash.end()) {
          hash.insert(key);
          heap.push({nums1[i] + nums2[j + 1], {i, j + 1}});
        }
      }
    }

    return ans;
  }
};


int main() {
  Solution sol;

//  vector<int> vec1{1, 7, 11};
//  vector<int> vec2{2, 4, 6};
//  auto vec = sol.kSmallestPairs(vec1, vec2, 3);

//  vector<int> vec1{1, 1, 2};
//  vector<int> vec2{1, 2, 3};
//  auto vec = sol.kSmallestPairs(vec1, vec2, 2);

  vector<int> vec1{-10, -4, 0, 0, 6};
  vector<int> vec2{3, 5, 6, 7, 8, 100};
  auto vec = sol.kSmallestPairs(vec1, vec2, 10);


  for (auto &item : vec) {
    for (auto &i : item) {
      cout << i << " ";
    }
    cout << "\n";
  }

  return 0;
}