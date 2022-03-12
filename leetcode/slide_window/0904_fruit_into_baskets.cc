#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

/**
 *  easy 滑动窗口
 */
class Solution {
 public:
  int static totalFruit(vector<int> &fruits) {
    int result = 0, sum = 0;
    auto size = static_cast<int>(fruits.size());
    unordered_map<int, int> basket;
    for (int i = 0; i != size; ++i) {
      if (basket.end() != basket.find(fruits[i])) {
        ++basket[fruits[i]];
        ++sum;
        result = sum > result ? sum : result;
      } else if (basket.size() < 2) {
        basket[fruits[i]] = 1;
        ++sum;
        result = sum > result ? sum : result;
      } else {
        // 找到不连续的对象
        auto not_remove_value = fruits[i - 1];
        auto it = find_if(basket.begin(), basket.end(),
                          [not_remove_value](pair<int, int> elem) {
                            return elem.first != not_remove_value;
                          });
        // 计算连续的对象
        not_remove_value = 1;
        for (int j = i - 2; j >= 0; --j) {
          if (fruits[j] == fruits[i - 1]) {
            ++not_remove_value;
          } else {
            break;
          }
        }
        // 更新
        basket[fruits[i - 1]] = not_remove_value;
        basket.erase(it);
        basket[fruits[i]] = 1;
        sum = not_remove_value + 1;
        result = sum > result ? sum : result;
      }
    }
    return result;
  }
};

int main() {
//  vector<int> vec{0, 0, 1, 1};
//  vector<int> vec{0, 1, 2, 2};
//  vector<int> vec{1, 2, 3, 2, 2};
//  vector<int> vec{3, 3, 3, 1, 2, 1, 1, 2, 3, 3, 4};
  vector<int> vec{1, 0, 1, 4, 1, 4, 1, 2, 3};
  cout << Solution::totalFruit(vec) << endl;
  return 0;
}