#include <random>
#include <iostream>
#include <chrono>

void F1(int n) {
  for (int i = 0; i < n; ++i) {  // n^2
    for (int j = 0; j < n; ++j) { // n
      ;  // 1
    }
  }
}

void F2(int n) {
  for (int i = 0; i < n; ++i) {  // n + (n - 1) + ... + 1 = (n + 1) * n / 2
    for (int j = i; j < n; ++j) {  // n - i
      ;  // 1
    }
  }
}

void F3(int n) {
  for (int i = 0; i < n; ++i) {  
    // 0 (n = 1) 
    // 0 1 1 1 ... 2 2 2 ... = (4024 + n - 1 ) * n / (2 * 2013)  (n > 1) 
    for (int j = 0; j < i; j += 2013) {  
      // (2013 - 1 + i) / 2013 
      ;  // 1
    }
  }
}

void F4(int n) {
  for (int i = 0; i < n / 2; ++i) {  // (3n / 2 + 1) * n / 2 / 2
    for (int j = i; j < n; ++j) {  // n - i
      ;  // 1
    }
  }
}

void F5(int n) {
  for (int i = n / 2; i < n; ++i) {  // (n / 2 + 1) * n / 2 / 2
    for (int j = 0; j < n - i; ++j) {  // n - i
      ;  // 1
    }
  }
}

void F6(int n) {
  for (int i = 0; i < n; ++i) {  // n * [log2(n - 1) + 1]
    for (int j = 1; j < n; j <<= 1) {  // 下整[log2(n)] 含义是 从2^1到2^r的个数
      // n <  2 : 0
      // n >= 2 : 下整[log2(n - 1)] + 1
      ;  // 1
    }
  }
}

void F7(int n) {
  for (int i = 0; i < n; ++i) {  // n * log2(2012)
    for (int j = 1; j < 2013; j <<= 1) {  // log2(2012)
      ;  // 1
    }
  }
}

void F8(int n) {
  for (int i = 1; i < n; ++i) {
  // (n - 1) + (n - 1) / 2 + ... + (n - 1) / (n - 1) + (n - 1)
  // = (n - 1) * (1 + 1 / 2 + 1 / 3 + ... + 1 / (n -1)) + (n - 1)
  // = O(nlogn)
    for (int j = 0; j < n; j += i) {  
    // n > 0 : (n - 1) / i + 1 (TestF8)
      ;  // 1
    }
  }
}

void TestF8() {
  auto cycle_times = [](const int &n) ->int {
    int times = 0;
    for (int j = 0; j < n; j += 3) {  // (n - 1) / i + 1  (i = 3)
      ++times;  // 1
    }
    return times;
  };
  std::default_random_engine e;
  e.seed(std::chrono::system_clock::now().time_since_epoch().count());
  std::uniform_int_distribution<int> u;
  for (int i = 0; i < 10; ++i) {
    int n = u(e);
    std::cout << n << " " << cycle_times(n) << " " << (n - 1) / 3 + 1 << "\n";
  }
}

int main() {
  return 0;
}