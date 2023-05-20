#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

using namespace std;
/// 注意, 问题可以简化:
/// equations 中 {"a","b"} 和 {"ab", "cd"} 没有关联, 不必约分
/// equations 中 {"2a", "2b"} 中 2 和 字母看作整体, 不必关联处理
class Solution {
 public:
  unordered_map<string, vector<pair<string, double>>> mp;
  unordered_set<string> visit;
  vector<double> result;

  vector<double> calcEquation(vector<vector<string>> &equations,
                              vector<double> &values,
                              vector<vector<string>> &queries) {
    mp.clear();
    visit.clear();
    result.clear();

    for (size_t i = 0; i != equations.size(); ++i) {
      mp[equations[i][0]].emplace_back(equations[i][1], values[i]);
      mp[equations[i][1]].emplace_back(equations[i][0], 1 / values[i]);
    }

    for (auto & query : queries) {
      const string &source = query[0];
      const string &target = query[1];
      result.push_back(Dfs(source, target, 1.0));
    }
    return result;
  }

  double Dfs(const string &source, const string &target, double value) {
    if (mp.find(source) == mp.end()) {
      return -1;
    }
    if (visit.find(source) != visit.end()) {
      return -1;
    }
    if (source == target) {
      return value;
    }
    visit.insert(source);
    for (const auto &pair : mp[source]) {
      auto num = Dfs(pair.first, target, value * pair.second);
      if (num != -1) {
        visit.erase(source);
        return num;
      }
    }
    visit.erase(source);
    return -1;
  }
};

int main() {
  vector<vector<string>> eq{{"a", "b"}, {"b", "c"}};
  vector<double> values{2.0, 3.0};
  vector<vector<string>> query{{"a", "c"}, {"b", "a"}, {"a", "e"}, {"a", "a"}, {"x", "x"}};
  Solution sol;
  for (auto item : sol.calcEquation(eq, values, query)) {
    std::cout << item << " ";
  }
  return 0;
}