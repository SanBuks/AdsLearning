#pragma once

namespace zuo {

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
