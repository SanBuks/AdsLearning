#pragma once

#include <memory>
#include <random>
#include <chrono>
#include <array>

namespace zuo {

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

#include "randomor_impl.h"
