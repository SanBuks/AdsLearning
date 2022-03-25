#ifndef DS_CPP_INTRO_SUBSET_H
#define DS_CPP_INTRO_SUBSET_H

#include <vector>

namespace ds_cpp {

namespace subset {

template <typename T>
void UniqueSubsetRecurI(const std::vector<T> &sets,
                        std::vector<std::vector<T>> &subs,
                        size_t cur,
                        std::vector<T> &sub) {
  subs.push_back(sub);
  for (size_t i = cur; i != sets.size(); ++i) {
    sub.push_back(sets[i]);
    UniqueSubsetRecurI(sets, subs, i + 1, sub);
    sub.pop_back();
  }
}

/**
 * 回溯递归 求元素唯一集合的子集
 */
template <typename T>
std::vector<std::vector<T>> UniqueSubsetRecur(const std::vector<T> &sets) {
  std::vector<std::vector<T>> result{};
  std::vector<int> sub;
  UniqueSubsetRecurI(sets, result, 0, sub);
  return result;
}


/**
 * 倍增遍历 求元素唯一集合的子集
 */
template <typename T>
std::vector<std::vector<T>> UniqueSubsetIter(const std::vector<T> &sets) {
  std::vector<std::vector<T>> result{{}};
  for (const auto &item : sets) {
    auto old_size = result.size();
    result.resize(old_size * 2);
    auto last_end = result.begin() + old_size;
    std::copy(result.begin(), last_end, last_end);  // 自拷贝
    for (auto it = result.begin() + old_size; it != result.end(); ++it) {
      it->push_back(item);                          // 插入
    }
  }
  return result;
}

/**
 * 模拟二进制 status 所有状态
 */
void IterateStatus(std::vector<bool> &status) {
  bool flag = true;
  size_t size = status.size();
  for (size_t p = size - 1; flag && p < size; --p) {
    if (!status[p]) {
      status[p] = true;
      flag = false;
    } else {
      status[p] = false;
    }
  }
}

/**
 * 二进制遍历 求元素唯一集合的子集
 */
template <typename T>
std::vector<std::vector<T>> UniqueSubset(const std::vector<T> &sets) {
  std::vector<std::vector<T>> result;

  size_t size = sets.size();
  std::vector<bool> status(size);  // 模拟二进制
  std::vector<T> sub;              // status 对应的元素
  sub.reserve(size);

  int N = 1 << size;               // 2^n 个子集
  for (int times = 0; times < N; ++times) {
    for (int i = 0; i < size; ++i) {
      if (status[i]) {
        sub.push_back(sets[i]);
      }
    }
    result.push_back(sub);
    sub.clear();
    IterateStatus(status);
  }
  return result;
}

}  // namespace ds_cpp::subset

}  // namespace ds_cpp

#endif