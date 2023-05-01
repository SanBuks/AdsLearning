#include <vector>
#include <stack>

using namespace std;

class Solution {
 public:
  vector<int> dailyTemperatures(vector<int> &temperatures) {
    int size = static_cast<int>(temperatures.size());
    stack<int> st;
    st.push(0);
    vector<int> result(size, 0);

    for (int i = 1; i < size; ++i) {
      if (temperatures[i] <= temperatures[st.top()]) {
        st.push(i);
      } else {
        // 不断更新
        while (!st.empty() && temperatures[i] > temperatures[st.top()]) {
          result[st.top()] = i - st.top();
          st.pop();
        }
        st.push(i);
      }
    }
    return result;
  }
};