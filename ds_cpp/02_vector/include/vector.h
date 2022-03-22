#ifndef DS_CPP_VECTOR_H
#define DS_CPP_VECTOR_H

#include <random>
#include <chrono>
#include <iostream>
#include <stdexcept>
#include <utility>

#include "vector_error.h"
#include "fib.h"

namespace ds_cpp {

// 定义 Vector 类型别名, 常量
class VectorBase {
 public:
  // 下标类型 (秩) [low, high) 范围为: [0, 2^k - 2)
  using Rank = unsigned long long;
  // 个数类型 (数)
  using Size = unsigned long long;

  // 装载因子 (size_ >= kMinLoadFactor * capacity_)
  static constexpr double kMinLoadFactor = 0.25;
  // 默认容量
  static constexpr Size kDefaultCapacity = 3;
  // 最大容量 2^k - 1
  static constexpr Size kMaxSize         = -2;
  // 空余的一个 作为 溢出哨兵
  static constexpr Rank kNonPosition     = -1;
};

constexpr double VectorBase::kMinLoadFactor;
constexpr VectorBase::Size VectorBase::kDefaultCapacity;
constexpr VectorBase::Size VectorBase::kMaxSize;
constexpr VectorBase::Rank VectorBase::kNonPosition;

template <typename>
class Vector;
template <typename T>
void swap(Vector<T> &lhs, Vector<T> &rhs) noexcept;

template <typename T>
class Vector : public VectorBase {
  friend void swap<T>(Vector<T> &lhs, Vector<T> &rhs) noexcept;
 public:
  // 泛型类型指针
  using Ptr = T*;
  using CPtr = const T*;

  /*---------------------------- 拷贝控制 -----------------------------------*/

  // 默认构造函数
  explicit Vector(Size size = 0, T elem = T());
  // 数组拷贝构造函数 [lo, hi)
  Vector(CPtr p_elem, Rank lo, Rank hi);
  Vector(CPtr p_elem, Size size);
  // 拷贝构造函数 [lo, hi)
  Vector(const Vector<T>& rhs, Rank lo, Rank hi);
  Vector(const Vector<T>& rhs);
  Vector(Vector<T>&& rhs) noexcept;
  // 重载赋值运算符
  Vector<T> &operator=(const Vector<T> &rhs);
  Vector<T> &operator=(Vector<T> &&rhs) noexcept;
  // 析构
  ~Vector();

  /*--------------------------- 只读访问 ------------------------------------*/

  // 返回元素数量
  inline Size size() const { return size_; }
  // 返回容量
  inline Size capacity() const { return capacity_; }
  // 是否为空
  inline bool Empty() const { return !size_; }
  // 下标随机访问(不可修改)
  const T& operator[](Rank r) const;
  // 下标随机访问(可修改, 委托 const 函数)
  T& operator[](Rank r);

  // 无序查找 在 [low, high) 范围内
  Rank Find(const T &elem, Rank low, Rank high) const;
  Rank Find(const T &elem) const;
  // 二分查找 在 [low, high) 范围内
  // 返回 <= elem 的秩, 如果秩在范围内不存在则返回 kNonPosition
  Rank BinSearch(const T &elem , Rank low, Rank high) const;
  Rank BinSearch(const T &elem) const;
  // Fib分查找 在 [low, high) 范围内
  // 返回 <= elem 的秩, 如果秩在范围内不存在则返回 kNonPosition
  Rank FibSearch(const T &elem , Rank low, Rank high) const;
  Rank FibSearch(const T &elem) const;

//  Rank Max(Rank low, Rank high) const;
//  Rank Max() const;
//  Size Disordered() const;

  // 访问器(不可修改)
  template <typename VST> void Traverse(const VST &visit) const ;
  // 访问器(可修改)
  template <typename VST> void Traverse(const VST &visit);
//
  /*--------------------------- 可写访问 ------------------------------------*/
  // 区间置乱
  void Unsort(Rank low, Rank high);
  void Unsort();
  // 位置插入
  Rank Insert(Rank r, const T &elem);
  Rank Insert(const T &elem);
  // 区间删除
  Size Remove(Rank low, Rank high);
  T Remove(Rank r);
  // 区间去重(无序)
  Size Deduplicate(Rank low, Rank high);
  Size Deduplicate();
  // 有序区间去重
  Size Uniquify(Rank low, Rank high);
  Size Uniquify();

//  // 区间转置
//  void Reverse(Rank low, Rank high);

  /*---------------------------  排序  ------------------------------------*/
  // 区间冒泡排序
  void BubbleSort(Rank low, Rank high);
  void BubbleSort();
  // 区间选择排序
  void SelectSort(Rank low, Rank high);
  void SelectSort();
  // 区间插入排序
  void InsertSort(Rank low, Rank high);
  void InsertSort();
  // 区间归并排序
  void MergeSort(Rank low, Rank high);
  void MergeSort();

 protected:
  // 扩容
  void Expand();
  // 缩容
  void Shrink();
  // 个数
  Rank size_;
  // 容量(任何状态下: capacity_ >= size_)
  Size capacity_;
  // 数据
  Ptr p_elem_;

 private:
  /*--------------------------- 检测参数 ------------------------------------*/
  // 检测 size_ 与 capacity_ 范围
  void CheckSizeCapacity();
  // 检测 访问下标是否有效
  void CheckVisitIndex(Rank r) const ;
  // 检测 low <= high, 如果超出范围会抛出异常
  void CheckRange(Rank low, Rank high) const ;
  // 检测 high <= size_, 如果超出范围会抛出异常
  void CheckUpperBound(Rank high, Size size) const ;

  /*--------------------------- 功能函数 ------------------------------------*/
  // 根据 capacity_ 分配空间
  void Allocate();
  // 从 p_source 所指数组下标 low 处拷贝 num 个元素到 p_target
  void CopyFrom(CPtr p_source, Rank low, Size num, Ptr p_target);
  // 将 [low, mid) 和 [mid , high) 范围合并成 [low, low + n)
  void Merge(Rank low, Rank mid, Rank high);
};

template <typename T>
Vector<T>::Vector(Size size, T elem)
    : size_(size), capacity_(size_ << 1), p_elem_(nullptr) {
  CheckSizeCapacity();
  Allocate();
  for (Rank i = 0; i != size_; ++i) {
    p_elem_[i] = elem;
  }
}

template <typename T>
Vector<T>::Vector(CPtr p_elem, Rank low, Rank high)
    : size_(high - low), capacity_(size_ << 1), p_elem_(nullptr) {
  CheckRange(low, high);
  CheckSizeCapacity();
  Allocate();
  CopyFrom(p_elem, low, size_, p_elem_);
}

template <typename T>
Vector<T>::Vector(CPtr p_elem, Size size) : Vector(p_elem, 0, size) {}

template <typename T>
Vector<T>::Vector(const Vector<T>& rhs, Rank low, Rank high)
    : size_(high - low), capacity_(size_ << 1), p_elem_(nullptr) {
  CheckRange(low, high);
  CheckUpperBound(high, rhs.size());
  CheckSizeCapacity();
  Allocate();
  CopyFrom(rhs.p_elem_, low, size_, p_elem_);
}

template <typename T>
Vector<T>::Vector(const Vector<T>& rhs) : Vector(rhs, 0, rhs.size()) {}

template <typename T>
Vector<T>::Vector(Vector<T>&& rhs) noexcept
    : size_(rhs.size_), capacity_(rhs.capacity_), p_elem_(rhs.p_elem_) {
  rhs.size_ = 0;
  rhs.capacity_ = 0;
  rhs.p_elem_ = nullptr;
}

template <typename T>
Vector<T> &Vector<T>::operator=(const Vector<T> &rhs) {
  using std::swap;
  if (&rhs != this) {
    Vector<T> temp(rhs);
    swap(*this, temp);
  }
  return *this;
}

template <typename T>
Vector<T> &Vector<T>::operator=(Vector<T> &&rhs) noexcept {
  if (this != &rhs) {
    delete [] p_elem_;
    size_ = rhs.size_;
    capacity_ = rhs.capacity_;
    p_elem_ = rhs.p_elem_;

    rhs.size_ = 0;
    rhs.capacity_ = 0;
    rhs.p_elem_ = nullptr;
  }
  return *this;
}

template <typename T>
Vector<T>::~Vector() {
  delete [] p_elem_;
}

template <typename T>
const T& Vector<T>::operator[](Rank r) const {
  CheckVisitIndex(r);
  return p_elem_[r];
}

template <typename T>
T& Vector<T>::operator[](Rank r) {
  return const_cast<T &>(
      static_cast<const Vector<T>&>(*this)[r]
  );
}

template <typename T>
VectorBase::Rank Vector<T>::Find(const T &elem, Rank low, Rank high) const {
  CheckRange(low, high);
  CheckUpperBound(high, size_);

  while(low < high) {
    if (p_elem_[high - 1] == elem) {
      return high - 1;
    }
    --high;
  }
  return kNonPosition;
}

template <typename T>
VectorBase::Rank Vector<T>::Find(const T &elem) const {
  return Find(elem, 0, size_);
}

template <typename T>
VectorBase::Rank
Vector<T>::BinSearch(const T &elem , Rank low, Rank high) const {
  CheckRange(low, high);
  CheckUpperBound(high, size_);

  Rank old_low = low;
  while (low < high) {
    Size mid = low + (high - low) / 2;
    if (p_elem_[mid] <= elem) {  // [start_low, low) <= elem
      low = mid + 1;
    } else {                     // [high, start_high) > elem
      high = mid;
    }
  }
  if (low == 0 || low - 1 < old_low) {
    return kNonPosition;
  } else {
    return --low;
  }
}

template <typename T>
VectorBase::Rank
Vector<T>::BinSearch(const T &elem) const {
  return BinSearch(elem, 0, size_);
}

template <typename T>
VectorBase::Rank
Vector<T>::FibSearch(const T &elem , Rank low, Rank high) const {
  CheckRange(low, high);
  CheckUpperBound(high, size_);

  Rank old_low = low;
  Fib fib(high - low);
  while (low < high) {
    while (fib.Get() > high - low) {
      fib.Prev();
    }
    Rank mid = low + (high - low) / 2;
    if (elem < p_elem_[mid]) {
      high = mid;
    } else {
      low = mid + 1;
    }
  }

  if (low == 0 || low - 1 < old_low) {
    return kNonPosition;
  } else {
    return --low;
  }
}

template <typename T>
VectorBase::Rank
Vector<T>::FibSearch(const T &elem) const {
  return FibSearch(elem, 0, size_);
}

//template<typename T>
//VectorBase::Rank Vector<T>::Max(Rank low, Rank high) const {
//  CheckRange(low, high);
//  CheckUpBound(size_, high);
//  if (low == high) {
//    return kNonPosition;
//  }
//  Rank max_pos = low;
//  for (Rank i = low + 1; i != high; ++i) {
//    if ((*this)[i] > (*this)[max_pos]) {
//      max_pos = i;
//    }
//  }
//  return max_pos;
//}
//
//template<typename T>
//VectorBase::Rank Vector<T>::Max() const {
//  return Max(0, size_);
//}
//
//template<typename T>
//VectorBase::Size Vector<T>::Disordered() const {
//  if (size_ < 2) {
//    return 0;
//  }
//
//  Size unordered_num = 0;
//  for (Rank i = 0; i != size_ - 1; ++i) {
//    if ((*this)[i] > (*this)[i + 1]) {
//      ++unordered_num;
//    }
//  }
//  return unordered_num;
//}
//



template <typename T>
template <typename VST>
void Vector<T>::Traverse(const VST &visit) {
  for (Rank i = 0; i != size_; ++i) {
    visit(p_elem_[i]);
  }
}

template <typename T>
template <typename VST>
void Vector<T>::Traverse(const VST &visit) const {
  for (Rank i = 0; i != size_; ++i) {
    visit(p_elem_[i]);
  }
}

template <typename T>
void Vector<T>::Unsort(Rank low, Rank high) {
  CheckRange(low, high);
  CheckUpperBound(high, size_);

  unsigned long seeds =
      std::chrono::system_clock::now().time_since_epoch().count();
  static std::default_random_engine engine(seeds);
  std::uniform_int_distribution<Size> uniform_distribution(0, high - low);

  for (Rank i = high; i > low; --i) {
    Rank now_pos = i - 1;
    Rank swap_pos = low + uniform_distribution(engine) % (i - low);
    std::swap(p_elem_[now_pos], p_elem_[swap_pos]);
  }
}

template <typename T>
void Vector<T>::Unsort() {
  Unsort(0, size_);
}

template <typename T>
VectorBase::Rank Vector<T>::Insert(Rank r, const T &elem) {
  CheckUpperBound(r, size_);
  if (size_ == capacity_) {
    Expand();
  }
  for (Rank i = size_; i > r; --i) {
    p_elem_[i] = p_elem_[i - 1];
  }
  p_elem_[r] = elem;
  ++size_;
  return r;
}

template <typename T>
VectorBase::Rank Vector<T>::Insert(const T &elem) {
  return Insert(size_, elem);
}

template <typename T>
VectorBase::Size Vector<T>::Remove(Rank low, Rank high) {
  CheckRange(low, high);
  CheckUpperBound(high, size_);

  while(high < size_) {
    p_elem_[low++] = p_elem_[high++];
  }
  size_ = low;
  Shrink();
  return high - low;
}

template <typename T>
T Vector<T>::Remove(Rank r) {
  CheckVisitIndex(r);
  T temp = p_elem_[r];
  Remove(r, r+1);
  return temp;
}

template <typename T>
VectorBase::Size Vector<T>::Deduplicate(Rank low, Rank high) {
  CheckRange(low, high);
  CheckUpperBound(high, size_);
  Size oldSize = size_;
  for (Rank i = low + 1; i < high; ++i) {
    auto pos = Find(p_elem_[i], low, i);
    if (pos != kNonPosition) {
      Remove(i);
      --i;
      --high;
    }
  }
  return oldSize - size_;
}

template <typename T>
VectorBase::Size Vector<T>::Deduplicate() {
  return Deduplicate(0, size_);
}

template <typename T>
VectorBase::Size Vector<T>::Uniquify(Rank low, Rank high) {
  CheckRange(low, high);
  CheckUpperBound(high, size_);
  Size oldSize = size_;

  Rank to_copy = low + 1;
  for (Rank i = to_copy; i != high; ++i) {
    if (p_elem_[to_copy - 1] != p_elem_[i]) {
      p_elem_[to_copy++] = p_elem_[i];
    }
  }
  size_ = to_copy;
  return oldSize - size_;
}

template <typename T>
VectorBase::Size Vector<T>::Uniquify() {
  return Uniquify(0, size_);
}

template <typename T>
void Vector<T>::BubbleSort(Rank low, Rank high) {
  CheckRange(low, high);
  CheckUpperBound(high, size_);

  Rank last_pos = high;
  for (Rank i = last_pos; i > low; i = last_pos) {
    last_pos = low;
    for (Rank j = low + 1; j < i; ++j) {
      if (p_elem_[j - 1] > p_elem_[j]) {
        std::swap(p_elem_[j - 1], p_elem_[j]);
        last_pos = j;
      }
    }
  }
}

template <typename T>
void Vector<T>::BubbleSort() {
  BubbleSort(0, size_);
}

template <typename T>
void Vector<T>::SelectSort(Rank low, Rank high) {
  CheckRange(low, high);
  CheckUpperBound(high, size_);

  Rank min_index;
  for (Rank i = 0; i < high - low; ++i) {
    min_index = low + i;
    for (Rank j = min_index + 1; j < high; ++j) {
      if (p_elem_[j] < p_elem_[min_index]) {
        min_index = j;
      }
    }
    std::swap(p_elem_[low + i], p_elem_[min_index]);
  }
}

template <typename T>
void Vector<T>::SelectSort() {
  SelectSort(0, size_);
}

template <typename T>
void Vector<T>::InsertSort(Rank low, Rank high) {
  CheckRange(low, high);
  CheckUpperBound(high, size_);

  for (Rank i = low + 1; i < high; ++i) {
    for (Rank end = i;
         end >= low + 1 && p_elem_[end] < p_elem_[end - 1];  // low + 1 防止溢出
         --end) {
      std::swap(p_elem_[end], p_elem_[end - 1]);
    }
  }
}

template <typename T>
void Vector<T>::InsertSort() {
  InsertSort(0, size_);
}

template <typename T>
void Vector<T>::MergeSort(Rank low, Rank high) {
  CheckRange(low, high);
  CheckUpperBound(high, size_);

  if (high - low < 2) {
    return ;
  }
  Rank mid = (high - low) / 2 + low;
  MergeSort(low , mid);
  MergeSort(mid, high);
  Merge(low, mid, high);
}

template <typename T>
void Vector<T>::MergeSort() {
  MergeSort(0, size_);
}

template <typename T>
void Vector<T>::Expand() {
  // 未满
  if (size_ < capacity_) {
    return;
  }
  // 已是上限
  if (size_ == kMaxSize) {
    throw std::runtime_error(vector_error::kVectorFull);
  }

  Size capacity_temp;
  // 处理上限和下限
  if (capacity_ > kMaxSize >> 1) {
    capacity_temp = kMaxSize;
  } else if (capacity_ << 1 > kDefaultCapacity) {
    capacity_temp = capacity_ << 1;
  } else {
    capacity_temp = kDefaultCapacity;
  }

  Ptr p_elem_temp = new T[capacity_temp];
  for (Rank i = 0; i != size_; ++i) {
    p_elem_temp[i] = p_elem_[i];
  }
  std::swap(p_elem_temp, p_elem_);
  capacity_ = capacity_temp;
  delete [] p_elem_temp;
}

template <typename T>
void Vector<T>::Shrink() {
  if (capacity_ * 1.0 * kMinLoadFactor <= size_) {
    return ;
  }
  Size capacity_temp = capacity_ >> 1 < kDefaultCapacity ?
                       kDefaultCapacity : capacity_ >> 1;
  Ptr p_elem_temp = new T[capacity_temp];
  for (Rank i = 0; i != size_; ++i) {
    p_elem_temp[i] = p_elem_[i];
  }
  std::swap(p_elem_temp, p_elem_);
  capacity_ = capacity_temp;
  delete [] p_elem_temp;
}

template <typename T>
void Vector<T>::CheckSizeCapacity() {
  // 处理 size_ 上溢
  if (kMaxSize < size_) {
    throw std::runtime_error(vector_error::kSizeOverFlow);
  }
  // 处理 capacity_ 上溢, 确保在 [size_, kMaxSize] 范围内
  capacity_ = kMaxSize < capacity_ ? kMaxSize : capacity_;
  capacity_ = capacity_ < size_ ? size_ : capacity_;
  // 处理 capacity_ 下溢
  capacity_ = capacity_ < kDefaultCapacity ? kDefaultCapacity : capacity_;
}

template <typename T>
void Vector<T>::CheckVisitIndex(Rank r) const {
  if (r >= size_) {
    throw std::runtime_error(vector_error::kVisitIndexError);
  }
}
template <typename T>
void Vector<T>::CheckRange(const Rank low, const Rank high) const {
  if (high < low) {
    throw std::runtime_error(vector_error::kInvalidRange);
  }
}

template <typename T>
void Vector<T>::CheckUpperBound(const Rank high, const Size size) const {
  if (high > size) {
    throw std::runtime_error(vector_error::kUpperBoundOverFlow);
  }
}

template <typename T>
void Vector<T>::Allocate() {
  p_elem_ = new T[capacity_];
}

template <typename T>
void Vector<T>::CopyFrom(CPtr p_source, Rank low, Size num, Ptr p_target) {
  for (Rank i = 0; i != num; ++i) {
    p_target[i] = p_source[low + i];
  }
}

template <typename T>
void Vector<T>::Merge(Rank low, Rank mid, Rank high) {
  Size la = mid - low;
  Size lb = high - mid;

  // 复制前半段 防止交错情况发生
  Ptr p_temp = new T[la];
  Ptr p_target = p_elem_ + low;
  for (Rank i = 0; i < la; ++i) {
    p_temp[i] = p_target[i];
  }

  Ptr A = p_temp;
  Ptr B = p_elem_ + mid;
  Ptr C = p_elem_ + low;

  for (Rank i = 0, j = 0, k = 0; (i < la) /*|| (j < lb) */;) {
    if (/*(i < la) && */(lb <= j || A[i] <= B[j])) {
      C[k++] = A[i++];
    }
    if ((j < lb) && (/*la <= i ||*/ B[j] < A[i])) {
      C[k++] = B[j++];
    }
  }
}

//template <typename T>
//void Vector<T>::Reverse(Rank low, Rank high) {
//  CheckRange(low, high);
//  CheckUpBound(size_, high);
//  while (low < high) {
//    T temp = (*this)[low];
//    (*this)[low] = (*this)[high - 1];
//    (*this)[high - 1] = temp;
//    ++low, --high;
//  }
//}
//

// 遍历调用对象类型
template <typename T>
class VectorTraverse {
 public:
  explicit VectorTraverse(std::ostream &io) : io_(io) {}
  void operator()(const T &e) const {
    io_ << e << " ";
  }
  void operator()(T &e) const {
    io_ << e << " ";
  }
  std::ostream& io() const { return io_; }
 private:
  std::ostream& io_;
};

template <typename T>
void swap(Vector<T> &lhs, Vector<T> &rhs) noexcept {
  using std::swap;
  swap(lhs.size_, rhs.size_);
  swap(lhs.capacity_, rhs.capacity_);
  swap(lhs.p_elem_, rhs.p_elem_);
}

}  // namespace ds_cpp

#endif