#include <vector>
#include <queue>
using namespace std;
class Solution {
 public:
  bool possibleBipartition(int n, vector<vector<int>> &dislikes) {
    vector<int> colored(n + 1, 0);
    queue<int> queue;

    vector<vector<int>> graph(n + 1, vector<int>{});
    for (const auto &path : dislikes) {
      graph[path[0]].push_back(path[1]);
      graph[path[1]].push_back(path[0]);
    }

    // bfs
    for (int i = 1; i <= n; ++i) {
      if (colored[i] != 0) continue;
      colored[i] = -1;
      if (!Bfs(i, graph, colored, queue)) {
        return false;
      }
    }
    return true;
  }

  bool Bfs(int source_index, vector<vector<int>> &graph, vector<int> &colored, queue<int> &queue) {
    queue.push(source_index);
    while (!queue.empty()) {
      auto target_index = queue.front();
      for (int neighbour : graph[target_index]) {
        if (colored[neighbour] == colored[target_index]) {
          return false;
        }
        if (colored[neighbour] == 0) {
          colored[neighbour] = -colored[target_index];
          queue.push(neighbour);
        }
      }
      queue.pop();
    }
    return true;
  }
};