#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

class Solution {
 public:
  long long MAX;
  long long MIN;
  long long putMarbles(vector<int> &weights, int k) {
    MAX = 0; MIN = numeric_limits<long long>::max();
    vector<int> divide(k + 1, 0);
    divide[k] = weights.size();
    backTrace(weights,  divide, 1);
    return MAX - MIN;
  }

  void backTrace(vector<int> &weights, vector<int> &divide, int index) {
    int k = static_cast<int>(divide.size());
    if (index == k - 1) {

      for (auto item : divide) {
        cout << item << " ";
      }
      cout << "\n";

      long long sum = 0;
      for (int i = 1; i <= k; ++i) {
        sum += weights[i] + weights[i - 1];
      }
      MAX = max(MAX, sum);
      MIN = min(MIN, sum);
      return;
    }

    for (int i = divide[index - 1] + 1; i <= weights.size() - 1; ++i) {
      divide[index] = i;
      backTrace(weights, divide, index + 1);
    }
  }
};


int main() {
  Solution sol;
  vector<int> vec{1, 3, 5, 1};
  sol.putMarbles(vec, 2);
  return 0;
}