#ifndef ZUO_DS_TOOL_COMPARATOR_IMPL_H_
#define ZUO_DS_TOOL_COMPARATOR_IMPL_H_

#include <utility>
#include <memory>
#include <random>
#include <iterator>
#include <algorithm>

namespace zuo {

template<typename T>
bool SortAlgorithmTest<T>::Test(size_t test_times,
                 const std::pair<size_t, size_t> &size_range,
                 const std::pair<const T &, const T &> &value_range,
                 void (*sort_func)(T array[], size_t len)) {
  size_t array_size = RandomGenerator<size_t>::RandomScalaElem(size_range);
  for (size_t i = 0; i != test_times; ++i) {
    auto target_array = RandomGenerator<T>::RandomScalaArray(array_size, value_range);
    auto right_array = RandomGenerator<T>::CloneScalaArray(array_size, target_array);
    sort_func(target_array.get(), array_size);
    std::sort(right_array.get(), right_array.get() + array_size);
    for (size_t j = 0; j != array_size; ++j) {
      if (target_array[j] != right_array[j]) {
        TestArrayPrintMessage(array_size, target_array, right_array);
        return false;
      }
    }
  }
  TestArrayPrintSuccess(test_times);
  return true;
}

template<typename T>
std::unique_ptr<T[]> RandomGenerator<T>::RandomScalaArray(size_t len,
                                                          const std::pair<const T &, const T &> &value_range) {
  auto array = std::make_unique<T[]>(len);
  for (size_t i = 0; i < len; ++i) {
    array[i] = RandomScalaElem(value_range);
  }
  return std::move(array);
}

template<typename T>
std::unique_ptr<T[]> RandomGenerator<T>::CloneScalaArray(size_t len, const std::unique_ptr<T[]> &array) {
  auto clone_array = std::make_unique<T[]>(len);
  for (size_t i = 0; i != len; ++i) {
    clone_array[i] = array[i];
  }
  return std::move(clone_array);
}

template<typename T>
T RandomGenerator<T>::RandomScalaElem(const std::pair<const T &, const T &> &value_range) {
  static std::default_random_engine re(seed());
  if constexpr (std::is_integral<T>::value) {
    std::uniform_int_distribution<T> dist(value_range.first, value_range.second);
    return dist(re);
  } else {
    std::uniform_real_distribution<T> dist(value_range.first, value_range.second);
    return dist(re);
  }
}

}
#endif
