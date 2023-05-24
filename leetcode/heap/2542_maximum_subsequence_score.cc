#include <vector>
#include <iostream>
#include <utility>
#include <queue>
#include <algorithm>
using namespace std;
class Solution {
 public:
  static vector<pair<int, int>> Sequence;
  static priority_queue<int, vector<int>, greater<int>> Queue;

  long long maxScore(vector<int> &nums1, vector<int> &nums2, int k) {
    Sequence.clear();
    while(!Queue.empty()) Queue.pop();
    int n = static_cast<int>(nums1.size());
    long long sum = 0;
    long long ans = 0;

    for (int i = 0; i < n; ++i) {
      Sequence.emplace_back(nums1[i], nums2[i]);
    }

    sort(Sequence.begin(), Sequence.end(), [](const pair<int, int> &lhs, const pair<int, int> &rhs) {
      return lhs.second > rhs.second;
    });

    for (int i = 0; i < k; ++i) {
      sum += Sequence[i].first;
      Queue.push(Sequence[i].first);
    }
    ans = sum * Sequence[k - 1].second;

    for (int i = k; i < n; ++i) {
      sum -= Queue.top();
      Queue.pop();

      sum += Sequence[i].first;
      Queue.push(Sequence[i].first);

      ans = max(ans, sum * Sequence[i].second);
    }

    return ans;
  }
};

vector<pair<int, int>> Solution::Sequence{};
priority_queue<int, vector<int>, greater<int>> Solution::Queue{};

void test1() {
  vector<int> nums1{4, 2, 3, 1, 1};
  vector<int> nums2{7, 5, 10, 9, 6};
  Solution sol;
  cout << sol.maxScore(nums1, nums2, 1) << "\n";
}

void test2() {
  vector<int> nums1{1, 3, 3, 2};
  vector<int> nums2{2, 1, 3, 4};
  Solution sol;
  cout << sol.maxScore(nums1, nums2, 3) << "\n";
}

int main() {
  test1();
  return 0;
}
