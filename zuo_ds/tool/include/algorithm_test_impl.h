#pragma once

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
        ErrorMsg(array_size, target_array, right_array);
        return false;
      }
    }
  }
  SuccessMsg(test_times);
  return true;
}


}