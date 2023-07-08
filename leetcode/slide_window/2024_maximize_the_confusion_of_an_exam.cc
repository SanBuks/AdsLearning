#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

class Solution {
 public:
  int maxConsecutiveAnswers(string answerKey, int k) {
    int ans = 0;

    int T_size = 0;
    int F_size = 0;

    int low = 0;
    for (int i = 0; i < answerKey.size(); ++i) {
      if (answerKey[i] == 'T') {
        ++T_size;
      }
      if (answerKey[i] == 'F') {
        ++F_size;
      }

      while (T_size > k && F_size > k) {
        if (answerKey[low] == 'T') {
          --T_size;
        }
        if (answerKey[low] == 'F') {
          --F_size;
        }
        ++low;
      }
      ans = max(ans, i - low + 1);
    }
    return ans;
  }
};


int main() {
  Solution sol;

  cout << sol.maxConsecutiveAnswers("TTFF", 2) << "\n";
  cout << sol.maxConsecutiveAnswers("TFFT", 1) << "\n";
  cout << sol.maxConsecutiveAnswers("TTFTTFTT", 1) << "\n";

  return 0;
}