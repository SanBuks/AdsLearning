#include <vector>
#include <stack>

using namespace std;

class Solution {
 public:
  static vector<int> nextGreaterElements(vector<int> &nums) {
    int size = static_cast<int>(nums.size());
    vector<int> result(nums.size(), -1);
    stack<int> st;
    st.push(0);

    for (int i = 1; i < size * 2; ++i) {
      if (nums[i % size] <= nums[st.top()]) {
        st.push(i % size);
      } else {
        while (!st.empty() && nums[st.top()] < nums[i % size]) {
          result[st.top()] = nums[i % size];
          st.pop();
        }
        st.push(i % size);
      }
    }

    return result;
  }
};
