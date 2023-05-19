#include <vector>
#include <queue>
using namespace std;
class Solution {
 public:
  static bool isBipartite(vector<vector<int>> &graph) {
    bool bipartite = true;
    int size = static_cast<int>(graph.size());
    vector<int> status(size, 0);

    queue<int> queue;
    for (int i = 0; i < size; ++i) {
      if (status[i] != 0) continue;
      status[i] = -1;
      if (!bfs(i, queue, graph, status)) {
        return false;
      }
    }
    return bipartite;
  }

  static bool bfs(int i, queue<int> &queue, vector<vector<int>> &graph, vector<int> &status) {
    queue.push(i);
    while (!queue.empty()) {
      auto index = queue.front();
      for (int j : graph[index]) {
        if (status[j] == status[index]) {
          return false;
        }
        if (status[j] == 0) {
          status[j] = -status[index];
          queue.push(j);
        }
      }
      queue.pop();
    }
    return true;
  }
};