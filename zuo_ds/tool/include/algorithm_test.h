#pragma once

#include <memory>
#include <random>
#include <chrono>
#include <array>

#include "randomor.h"

namespace zuo {

// 测试排序算法
template <typename T>
class SortAlgorithmTest {
 public:
  /**
   * 测试主方法
   * @param test_times     测试次数
   * @param size_range     数组长度范围
   * @param value_range    数值范围
   * @return               算法是否正确
   */
  static bool Test(size_t test_times,
                   const std::pair<size_t, size_t> &size_range,
                   const std::pair<const T &, const T &> &value_range,
                   void (*sort_func)(T array[], size_t len));
 private:
  static void ArrayMsg(size_t len, const std::unique_ptr<T[]> &array) {
    for (size_t i = 0; i != len; ++i) {
      std::cout << array[i] << " ";
    }
    std::cout << "\n";
  }

  static void ErrorMsg(size_t len,
                       const std::unique_ptr<T[]> &array_wrong,
                       const std::unique_ptr<T[]> &array_right) {
    std::cout << "Wrong array is\n";
    ArrayMsg(len, array_wrong);
    std::cout << "Right array is\n";
    ArrayMsg(len, array_right);
  }

  static void SuccessMsg(size_t test_times) {
    std::cout << "Test Success: test " << test_times << "\n";
  }
};

}

#include "algorithm_test_impl.h"
