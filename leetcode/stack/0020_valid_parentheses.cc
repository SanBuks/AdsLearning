#include <stack>
#include <string>

using namespace std;

class Solution {
 public:
  // 1 <= s.length <= 104
  static bool isValid(const string &s) {
    stack<char> st;
    size_t i = 0;
    size_t size = s.size();
    st.push(s[i++]);

    char c;
    while (i != size) {
      c = s[i++];
      switch(c) {
        case '(':
        case '[':
        case '{': {
          st.push(c);
          break;
        }

        case ')': {
          if (!st.empty() && st.top() == '(') {
            st.pop();
          } else {
            return false;
          }
          break;
        }

        case ']': {
          if (!st.empty() && st.top() == '[') {
            st.pop();
          } else {
            return false;
          }
          break;
        }

        case '}': {
          if (!st.empty() && st.top() == '{') {
            st.pop();
          } else {
            return false;
          }
          break;
        }
        default: {
          return false;
        }
      }
    }
    return st.empty();
  }
};