#include <string>
#include <iostream>

using namespace std;

class Solution {
 public:
  static string convert(const string &s, int numRows) {
    // same as input
    if (numRows == 1) { return s; }

    const int size = static_cast<int>(s.size());
    string result(size, ' ');

    auto gap = (numRows << 1) - 2;
    auto mid_row = numRows - 2;

    // result index
    int i = 0;

    // first line
    for (int index = 0; index < size; index += gap) {
      result[i++] = s[index];
    }

    for (int mid_times = 1; mid_times <= mid_row; ++mid_times) {
      auto first_index = mid_times;
      // rule found by example
      auto second_index = first_index + gap - (mid_times << 1);
      while (first_index < size) {
        result[i++] = s[first_index];
        if(second_index < size) {
          result[i++] = s[second_index];
          second_index += gap;
        }
        first_index += gap;
      }
    }

    // last line
    for (int index = numRows - 1; index < size; index += gap) {
      result[i++] = s[index];
    }
    return result;
  }
};


int main() {
//  string s = "PAYPALISHIRING";
  string s = "PAYPALISHIRING";

  std::cout << Solution::convert(s, 4) << "\n";
  return 0;
}