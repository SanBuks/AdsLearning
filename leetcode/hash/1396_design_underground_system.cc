#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

class UndergroundSystem {
 public:
  unordered_map<int, pair<string, int>> customer_;
  unordered_map<string, pair<int, int>> record_;

  explicit UndergroundSystem() :
      customer_{}, record_{} {
    customer_.clear();
    record_.clear();
  }

  void checkIn(int id, const string &stationName, int t) {
    customer_[id] = {stationName, t};
  }

  void checkOut(int id, const string &stationName, int t) {
    auto key = customer_[id].first + "_" + stationName;
    if (record_.find(key) != record_.end()) {
      ++record_[key].first;
      record_[key].second += t - customer_[id].second;
    } else {
      record_[key].first = 1;
      record_[key].second = t - customer_[id].second;
    }
  }

  double getAverageTime(const string &startStation, const string &endStation) {
    auto dir = direction(startStation, endStation);
    return record_[dir].second * 1.0 / record_[dir].first;
  }
  string direction(const string &lhs, const string &rhs) {
    return lhs + "_" + rhs;
  }
};

//#include <iostream>
//#include <string>
//#include <unordered_map>
//
//// 自定义 hash 函数
//struct PairHasher {
//  std::size_t operator()(const std::pair<std::string, std::string> &p) const {
//    return std::hash<std::string>()(p.first) ^ std::hash<std::string>()(p.second);
//  }
//};
//
//int main() {
//  // 创建一个 unordered_map，键类型为 pair<string, string>，值类型为 pair<int, int>
//  std::unordered_map<std::pair<std::string, std::string>, std::pair<int, int>, PairHasher> myMap;
//
//  // 向 unordered_map 中添加一些键值对
//  myMap.emplace(std::make_pair("key1", "value1"), std::make_pair(1, 2));
//  myMap.emplace(std::make_pair("key2", "value2"), std::make_pair(3, 4));
//  myMap.emplace(std::make_pair("key3", "value3"), std::make_pair(5, 6));
//
//  // 查找指定的键
//  auto it = myMap.find(std::make_pair("key1", "value1"));
//  if (it != myMap.end()) {
//    std::cout << "Found the key: (" << it->first.first << ", " << it->first.second << ")" << std::endl;
//    std::cout << "Value is: (" << it->second.first << ", " << it->second.second << ")" << std::endl;
//  } else {
//    std::cout << "Key not found." << std::endl;
//  }
//
//  return 0;
//}
