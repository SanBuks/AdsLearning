#include <vector>
#include <numeric>
#include <queue>
#include <map>
#include <iostream>

using namespace std;

class Solution {
 public:
  double maxProbability(int n, vector<vector<int>> &edges, vector<double> &succProb, int start, int end) {
    vector<double> dis(n, 0);

    map<int, vector<pair<int, double>>> graph;  // S->(T, weight)
    for (int i = 0; i < edges.size(); ++i) {
      graph[edges[i][0]].emplace_back(edges[i][1], succProb[i]);
      graph[edges[i][1]].emplace_back(edges[i][0], succProb[i]);
    }


    dis[start] = 1;
    priority_queue<pair<double, int>, vector<pair<double, int>>, less<>> pq;
    pq.emplace(1, start);

    while (!pq.empty()) {
      double distance = pq.top().first;
      int source = pq.top().second;
      pq.pop();

      if (source == end) {
        return distance;
      }

      for (const auto &pair : graph[source]) {
        int target = pair.first;
        double weight = pair.second;

        if (distance * weight > dis[target]) {
          dis[target] = distance * weight;
          pq.emplace(dis[target], target);
        }
      }
    }

    return 0.0;
  }
};


int main() {
  Solution sol;
  vector<vector<int>> edges{{0,1},{1,2},{0,2}};
  vector<double> succProb{0.5, 0.5, 0.2};
  cout << sol.maxProbability(3, edges, succProb, 0, 2) << "\n";


  return 0;
}