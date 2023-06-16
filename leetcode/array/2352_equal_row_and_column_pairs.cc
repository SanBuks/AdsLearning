#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>

using namespace std;

class Solution {
 public:
  static unordered_map<string, int> hash;
  int static equalPairs(vector<vector<int>> &grid) {
    string row;
    hash.clear();
    for (int i = 0; i < grid.size(); ++i) {
      row.clear();
      for (int j = 0; j < grid.size(); ++j) {
        row.append(" " + to_string(grid[i][j]));
      }
      if (hash.find(row) != hash.end()) {
        ++hash[row];
      } else {
        hash[row] = 1;
      }
    }

    int ans = 0;
    for (int i = 0; i < grid.size(); ++i) {
      row.clear();
      for (int j = 0; j < grid.size(); ++j) {
        row.append(" " + to_string(grid[j][i]));
      }

      if (hash.find(row) != hash.end()) {
        ans += hash[row];
      }
    }
    return ans;
  }
};

unordered_map<string, int> Solution::hash;

int main() {

//  vector<vector<int>> grid{{3, 1, 2, 2}, {1, 4, 4, 4}, {2, 4, 2, 2}, {2, 5, 2, 2}};
  vector<vector<int>> grid{{11,1},{1,11}};
  cout << Solution::equalPairs(grid) << "\n";
  return 0;
}