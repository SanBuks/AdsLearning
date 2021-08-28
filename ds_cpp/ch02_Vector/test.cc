#include "vector.h"
#include <iostream>

template <typename T>
class VectorTraverse {
 public:
  void operator()(const T &e) const {
    std::cout << e << " ";
  }
  void operator()(T &e) const {
    std::cout << e << " ";
  }
};

using VisitInt = VectorTraverse<int>;
VisitInt vst;

void TestOperatorEqual() {
  my_ads::Vector<int> vec(3, 2); 
  my_ads::Vector<int> vec2(2, 3);
  vec = vec2;
  std::cout << vec.capacity() << "\n";
  for (size_t i = 0; i < vec.size(); ++i ) {
    std::cout << vec[i] << " ";
  }
}

void TestUnsort() {
  int a[] = {1, 2, 3, 4, 5, 6};
  my_ads::Vector<int> vec(a, 6);
  vec.Unsort();
  for (size_t i = 0; i < vec.size(); ++i ) {
    std::cout << vec[i] << " ";
  }
}

void TestFind() {
  int a[] = {1, 2, 3, 4, 5, 6};
  my_ads::Vector<int> vec(a, 6);
  vec.Unsort();
  for (size_t i = 0; i < vec.size(); ++i ) {
    std::cout << vec[i] << " ";
  }
  std::cout << "\n" << vec.Find(7, 0, vec.size());
}

void TestRemove() {
  int a[] = {1, 2, 3, 4, 5, 6};
  my_ads::Vector<int> vec(a, 6);
  vec.Unsort();
  for (size_t i = 0; i < vec.size(); ++i ) {
    std::cout << vec[i] << " ";
  }

  vec.Remove(0);

  std::cout << "\n";
  for (size_t i = 0; i < vec.size(); ++i ) {
    std::cout << vec[i] << " ";
  }
}

void TestDeduplicate() {
  int a[] = {3, 2, 3, 4, 7, 4};
  my_ads::Vector<int> vec(a, 6);
  vec.Unsort();
  vec.Traverse<VisitInt>(vst);

  vec.Deduplicate();
  std::cout << "\n";
  vec.Traverse<VisitInt>(vst);
}


void TestUniquify() {
  int a[] = {1, 2, 2, 2, 3, 3, 4, 4, 4, 7, 9};
  my_ads::Vector<int> vec(a, sizeof(a) / sizeof(int));
  vec.Traverse<VisitInt>(vst);
  std::cout << "\n" << vec.Uniquify() << "\n";
  vec.Traverse<VisitInt>(vst);
}

void TestBinSearch() {
  int a[] = {1, 2, 2, 2, 3, 3, 4, 4, 4, 7, 9};
  my_ads::Vector<int> vec(a, sizeof(a) / sizeof(int));
  vec.Traverse<VisitInt>(vst);
  std::cout << "\n" << vec.BinSearch(2, 0, vec.size()) << "\n";
  vec.Traverse<VisitInt>(vst);
}

void TestBubbleSort() {
  int a[] = {1, 2, 2, 2, 3, 3, 4, 4, 4, 7, 9};
  my_ads::Vector<int> vec(a, sizeof(a) / sizeof(int));
  vec.Unsort();
  vec.Traverse<VisitInt>(vst);

  std::cout << "\n";
  vec.BubbleSort();
  vec.Traverse<VisitInt>(vst);
}

void TestMergeSort() {
  int a[] = {1, 2, 3};
  my_ads::Vector<int> vec(a, sizeof(a) / sizeof(int));
  vec.Unsort();
  vec.Traverse<VisitInt>(vst);

  std::cout << "\n";
  vec.MergeSort(0, vec.size());
  vec.Traverse<VisitInt>(vst);
}

unsigned long CalcCompareTimes(unsigned long k) {
  if (k == 1) { 
    return 1;
  }

  unsigned long result = 2 * CalcCompareTimes(k - 1);
  result += (3 * (1 << (k-1)) -1);  

  return result;
}

int main() {
  TestMergeSort();
  return EXIT_SUCCESS; 
}
