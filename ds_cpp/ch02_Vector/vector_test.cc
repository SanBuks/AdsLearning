#include "vector.h"

#include <iostream>
#include <string>
#include <locale>

using namespace dsa_cpp;

void TestTraverseAndCtor() {
  VectorTraverse<int> traverse;
  /*********** 默认初始化测试 **********/
  std::cout << u8"默认初始化\n";
  Vector<int> vec_default;
  std::cout << "content : ";
  vec_default.Traverse(traverse);
  std::cout << "\n";
  std::cout << "capacity : " << vec_default.capacity() << "\n";
  /*********** 数值初始化测试 **********/
  std::cout << u8"数值初始化测试\n";
  Vector<int> vec_num_default(6, 2);
  std::cout << "content : ";
  vec_num_default.Traverse(traverse);
  std::cout << "\n";
  std::cout << "capacity : " << vec_num_default.capacity() << "\n";
  /*********** 数组拷贝初始化测试 **********/
  int *array = new int[10]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::cout << u8"数组拷贝初始化测试\n";
  Vector<int> vec_copy_from_array1(array, 2);
  Vector<int> vec_copy_from_array2(array, 0, 5);
  std::cout << "content : ";
  vec_copy_from_array1.Traverse(traverse);
  std::cout << "\n";
  std::cout << "content : ";
  vec_copy_from_array2.Traverse(traverse);
  std::cout << "\n";
  std::cout << "capacity : " << vec_copy_from_array1.capacity() << "\n";
  std::cout << "capacity : " << vec_copy_from_array2.capacity() << "\n";
  /*********** 向量拷贝初始化测试 **********/
  std::cout << u8"向量拷贝初始化测试\n";
  Vector<int> vec_copy_from_vector1(vec_num_default);
  Vector<int> vec_copy_from_vector2(vec_num_default, 0, 5);
  Vector<int> vec_copy_from_vector3 = vec_num_default;
  std::cout << "content : ";
  vec_copy_from_vector1.Traverse(traverse);
  std::cout << "\n";
  std::cout << "content : ";
  vec_copy_from_vector2.Traverse(traverse);
  std::cout << "\n";
  std::cout << "content : ";
  vec_copy_from_vector3.Traverse(traverse);
  std::cout << "\n";
  std::cout << "capacity : " << vec_copy_from_vector1.capacity() << "\n";
  std::cout << "capacity : " << vec_copy_from_vector2.capacity() << "\n";
  std::cout << "capacity : " << vec_copy_from_vector3.capacity() << "\n";
}

int main() {
  TestTraverseAndCtor();
  return 0;
}

/*

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
*/