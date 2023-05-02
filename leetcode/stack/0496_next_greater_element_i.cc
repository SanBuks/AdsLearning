#include <vector>
#include <stack>
#include <unordered_map>

using namespace std;

class Solution {
 public:
  vector<int> nextGreaterElement(vector<int> &nums1, vector<int> &nums2) {
    stack<int> st;
    vector<int> result(nums1.size(), -1);
    unordered_map<int, int> mp;

    st.push(nums2[0]);
    for (int i = 1; i < nums2.size(); ++i) {
      if (nums2[i] <= st.top()) {
        st.push(nums2[i]);
        continue;
      } else {
        while (!st.empty() && nums2[i] > st.top()) {
          mp[st.top()] = nums2[i];
          st.pop();
        }
        st.push(nums2[i]);
      }
    }
    while (!st.empty()) {
      mp[st.top()] = -1;
      st.pop();
    }

    for (int i = 0; i < nums1.size(); ++i) {
      result[i] = mp[nums1[i]];
    }

    return result;
  }
};