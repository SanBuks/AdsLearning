#include <unordered_map>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class SnapshotArray {
 public:
  explicit SnapshotArray(int length) : data_(length, {{0, 0}}), snap_times(1) {
  }

  void set(int index, int val) {
    size_t last = data_[index].size() - 1;
    if (data_[index][last].first == snap_times) {
        data_[index][last].second = val;
    } else if (data_[index][last].second != val) {
        data_[index].emplace_back(snap_times, val);
    }
  }

  int snap() {
    int result = snap_times - 1;
    ++snap_times;
    return result;
  }

  int get(int index, int snap_id) {
    return bin_search(data_[index], snap_id + 1);
  }

  int bin_search(vector<pair<int, int>> &vec, int snap_id) {
    int lo = 0;
    int hi = vec.size();
    while (lo < hi) {
      int mi = (hi - lo) / 2 + lo;
      if (vec[mi].first > snap_id) {
        hi = mi;
      } else {
        lo = mi + 1;
      }
    }
    return vec[--lo].second;
  }

 private:
  vector<vector<pair<int, int>>> data_;
  int snap_times;
};

void test1() {
  SnapshotArray snapshot_array(3);
  snapshot_array.set(0, 5);
  cout << snapshot_array.snap() << "\n";
  snapshot_array.set(0, 6);
  cout << snapshot_array.get(0, 0) << "\n";
}

void test2() {
  SnapshotArray snapshot_array(3);
  snapshot_array.set(1, 18);
  snapshot_array.set(1, 4);
  cout << snapshot_array.snap() << "\n";
  cout << snapshot_array.get(0, 0) << "\n";
  snapshot_array.set(0, 20);
  cout << snapshot_array.snap() << "\n";
  snapshot_array.set(0, 2);
  snapshot_array.set(1, 1);
  cout << snapshot_array.get(1, 1) << "\n";
  cout << snapshot_array.get(1, 0) << "\n";
}

int main() {
//  test1();
  test2();
  return 0;
}

