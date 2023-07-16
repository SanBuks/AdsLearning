#ifndef ZUO_DS_TOOL_COMPARATOR_H_
#define ZUO_DS_TOOL_COMPARATOR_H_

#include <memory>
#include <random>
#include <chrono>

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
  static void PrintArrayMessage(size_t len, const std::unique_ptr<T[]> &array) {
    for (size_t i = 0; i != len; ++i) {
      std::cout << array[i] << " ";
    }
    std::cout << "\n";
  }

  static void TestArrayPrintMessage(size_t len,
                                    const std::unique_ptr<T[]> &array_wrong,
                                    const std::unique_ptr<T[]> &array_right) {
    std::cout << "Wrong array is\n";
    PrintArrayMessage(len, array_wrong);
    std::cout << "Right array is\n";
    PrintArrayMessage(len, array_right);
  }

  static void TestArrayPrintSuccess(size_t test_times) {
    std::cout << "Test Success: test " << test_times << "\n";
  }
};

// 随机生成类
template <typename T>
class RandomGenerator {
 public:
  /**
   * 随机值种子
   * @return 随机种子
   */
  static inline auto seed() { return std::chrono::system_clock::now().time_since_epoch().count(); }
  /**
   * 返回随机标量数组
   * @param len 数组长度
   * @param value_range 标量范围 [a, b]
   * @return 标量数组的 unique_ptr
   */
  static std::unique_ptr<T []> RandomScalaArray(size_t len, const std::pair<const T &, const T &> &value_range);
  /**
   * 克隆一个数组
   * @param len 数组长度
   * @param array 数组指针引用
   * @return 标量数组的 unique_ptr
   */
  static std::unique_ptr<T []> CloneScalaArray(size_t len, const std::unique_ptr<T []> &array);
  /***
   * 返回随机标量
   * @param value_range 标量范围 [a, b]
   * @return 标量值
   */
  static T RandomScalaElem(const std::pair<const T &, const T &> &value_range);
};

}

#include "comparator_impl.h"
#endif
