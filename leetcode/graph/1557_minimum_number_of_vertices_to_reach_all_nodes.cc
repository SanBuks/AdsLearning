#include <vector>
#include <cstring>
using namespace std;

class Solution {
 public:
  static int in_degree[100010];
  vector<int> findSmallestSetOfVertices(int n, vector<vector<int>> &edges) {
    vector<int> result;
    memset(in_degree, 0, sizeof(in_degree));
    auto size = edges.size();
    for (size_t i = 0; i < size; ++i) {
      ++in_degree[edges[i][1]];
    }
    for (int i = 0; i < n; ++i) {
      if (in_degree[i] == 0) {
        result.push_back(i);
      }
    }
    return result;
  }
};

int Solution::in_degree[100010];
