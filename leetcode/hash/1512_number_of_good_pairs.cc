#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
 public:
  static int numIdenticalPairs(vector<int> &nums) {
    unordered_map<int, int> mp;
    for (const auto &item : nums) {
      if (mp.find(item) == mp.end()) {
        mp[item] = 1;
      } else {
        ++mp[item];
      }
    }

    int sum = 0;
    for (const auto &item : mp) {
      sum += item.second * (item.second - 1) / 2;
    }

    return sum;
  }
};