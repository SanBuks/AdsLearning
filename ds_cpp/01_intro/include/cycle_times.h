#ifndef DS_CPP_INTRO_CYCLE_TIMES_H
#define DS_CPP_INTRO_CYCLE_TIMES_H

#include <random>
#include <iostream>
#include <chrono>

namespace ds_cpp {

namespace cycle_times {

unsigned long long F1(unsigned n) {
  auto times = 0ULL;
  for (int i = 0; i < n; ++i) {    // n^2
    for (int j = 0; j < n; ++j) {  // n
      ++times;                     // 1
    }
  }
  return times;
}

unsigned long long F1Times(unsigned n) {
  return n * n;
}

unsigned long long F2(unsigned n) {
  auto times = 0ULL;
  for (int i = 0; i < n; ++i) {    // n + (n - 1) + ... + 1 = (n + 1) * n / 2
    for (int j = i; j < n; ++j) {  // n - i
      ++times;                     // 1
    }
  }
  return times;
}

unsigned long long F2Times(unsigned n) {
  return (n + 1) * n / 2;
}

unsigned long long F3(unsigned n, int step) {
  if (step <= 0) {
    throw std::runtime_error("F3(): step must > 0!");
  }
  auto times = 0ULL;
  for (int i = 0; i < n; ++i) {          // O(n^2)
    for (int j = 0; j < i; j += step) {  // (step - 1 + i) / step
      ++times;                           // 1
    }
  }
  return times;
}

unsigned long long F3Times(unsigned n, int step) {
  auto times = 0ULL;
  for (int i = 0; i < n; ++i) {
    times += (step - 1 + i) / step;
  }
  return times;
}

//void F4(int n) {
//  for (int i = 0; i < n / 2; ++i) {  // (3n / 2 + 1) * n / 2 / 2
//    for (int j = i; j < n; ++j) {  // n - i
//      ;  // 1
//    }
//  }
//}
//
//void F5(int n) {
//  for (int i = n / 2; i < n; ++i) {  // (n / 2 + 1) * n / 2 / 2
//    for (int j = 0; j < n - i; ++j) {  // n - i
//      ;  // 1
//    }
//  }
//}
//
//void F6(int n) {
//  for (int i = 0; i < n; ++i) {  // n * [log2(n - 1) + 1]
//    for (int j = 1; j < n; j <<= 1) {  // 下整[log2(n)] 含义是 从2^1到2^r的个数
//      // n <  2 : 0
//      // n >= 2 : 下整[log2(n - 1)] + 1
//      ;  // 1
//    }
//  }
//}
//
//void F7(int n) {
//  for (int i = 0; i < n; ++i) {  // n * log2(2012)
//    for (int j = 1; j < 2013; j <<= 1) {  // log2(2012)
//      ;  // 1
//    }
//  }
//}
//
//void F8(int n) {
//  for (int i = 1; i < n; ++i) {
//    // (n - 1) + (n - 1) / 2 + ... + (n - 1) / (n - 1) + (n - 1)
//    // = (n - 1) * (1 + 1 / 2 + 1 / 3 + ... + 1 / (n -1)) + (n - 1)
//    // = O(nlogn)
//    for (int j = 0; j < n; j += i) {
//      // n > 0 : (n - 1) / i + 1 (TestF8)
//      ;  // 1
//    }
//  }
//}
//
//void TestF8() {
//  auto cycle_times = [](const int &n) ->int {
//    int times = 0;
//    for (int j = 0; j < n; j += 3) {  // (n - 1) / i + 1  (i = 3)
//      ++times;  // 1
//    }
//    return times;
//  };
//  std::default_random_engine e;
//  e.seed(std::chrono::system_clock::now().time_since_epoch().count());
//  std::uniform_int_distribution<int> u;
//  for (int i = 0; i < 10; ++i) {
//    int n = u(e);
//    std::cout << n << " " << cycle_times(n) << " " << (n - 1) / 3 + 1 << "\n";
//  }
//}

}  // namespace ds_cpp::cycle_times

}  // namespace ds_cpp

#endif
