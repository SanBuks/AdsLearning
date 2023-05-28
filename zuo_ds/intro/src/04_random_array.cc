#include <random>
#include <chrono>
#include <algorithm>
#include <iostream>
#include <memory>

namespace zuo {

/**
 * 测试数组排序工具类
 * @tparam T 测试元素类型
 */
template <typename T>
class TestArray {
 public:
  /**
   * 测试主方法
   * @param test_times     测试次数
   * @param max_array_size 数组长度
   * @param value_range    数值范围
   * @return               是否有序
   */
  static bool Test(size_t test_times, size_t max_array_size, const std::pair<const T &, const T &> &value_range) {
    static std::default_random_engine random_engine(seed());
    static std::uniform_int_distribution<size_t> distribution(0, max_array_size);

    size_t array_size = 0;
    for (size_t i = 0; i != test_times; ++i) {
      array_size = distribution(random_engine);
      auto target_array = RandomArray(array_size, value_range);
      auto right_array = CloneArray(array_size, target_array);
      std::sort(right_array.get(), right_array.get() + array_size);

      for (size_t index = 0; index != array_size; ++index) {
        if (target_array[index] != right_array[index])  {
          TestArrayPrintMessage(array_size, target_array, right_array);
          return false;
        }
      }
    }
    TestArrayPrintSuccess(test_times);
    return true;
  }

  static std::unique_ptr<T []> RandomArray(size_t len, const std::pair<const T &, const T &> &value_range) {
    auto array = std::make_unique<T []>(len);
    static std::default_random_engine random_engine(seed());
    static std::uniform_int_distribution<T> distribution(value_range.first, value_range.second);
    for (size_t i = 0; i < len; ++i) {
      array[i] = distribution(random_engine);
    }
    return std::move(array);
  }

 private:
  inline auto static seed() {
    return std::chrono::system_clock::now().time_since_epoch().count();
  }

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

  static std::unique_ptr<T []> CloneArray(size_t len, const std::unique_ptr<T[]> &array) {
    auto clone_array = std::make_unique<T []>(len);
    for (size_t i = 0; i != len; ++i) {
      clone_array[i] = array[i];
    }
    return std::move(clone_array);
  }
};

}

int main() {
  zuo::TestArray<int>::Test(100, 20, {-100, 100});
}