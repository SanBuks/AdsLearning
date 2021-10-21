#ifndef DS_CPP_02_VECTOR_H
#define DS_CPP_02_VECTOR_H

#include <random>
#include <chrono>
#include <iostream>
#include <stdexcept>

namespace dsa_cpp {

// 定义 Vector 类型别名, 常量
class VectorBase {
 public:
  // 下标类型 (秩)
  using Rank = unsigned long;
  // 个数类型 (数)
  using Size = unsigned long;
  // 装载因子 (size_ >= kMinLoadFactor * capacity_)
  static constexpr double kMinLoadFactor = 0.25;
  // 默认容量
  static constexpr Size kDefaultCapacity = 3;
};

constexpr double VectorBase::kMinLoadFactor;
constexpr VectorBase::Size VectorBase::kDefaultCapacity;

template <typename T>
class Vector : public VectorBase {
 public:
  // 存储数据类型指针
  using Ptr = T*;
  using CPtr = const T*;

  /**** 拷贝控制 ****/
  explicit Vector(Size size = 0, T elem = T());
  Vector(CPtr p_elem, Size size);
  Vector(CPtr p_elem, Rank lo, Rank hi);
  Vector(const Vector<T>& rhs);
  Vector(const Vector<T>& rhs, Rank lo, Rank hi);
  Vector<T> &operator=(const Vector<T> &rhs);
  ~Vector();

  /**** 只读访问接口 (内联)  ****/
  inline Size size() const { return size_; }
  inline Size capacity() const { return capacity_; }
  inline bool Empty() const { return !size_; }
  inline const T& operator[](Rank r) const { return p_elem_[r]; }
  /**** 只读访问接口 (非内联) ****/
  Size Disordered() const;
  Rank Find(const T &elem) const;
  Rank Find(const T &elem, Rank low, Rank high) const;

  template <typename VST>
  void Traverse(const VST &visit);
  template <typename VST>
  void Traverse(const VST &visit) const ;
  void Traverse(void (*visit)(T &elem));
  void Traverse(void (*visit)(const T &elem)) const;

  /****可写访问接口****/
  T& operator[] (Rank r) {
    return const_cast<T &>(
        static_cast<const Vector<T>&>(*this)[r]
    );
  }

  Rank Insert(Rank r, const T &elem);
  Rank Insert(const T &elem);
  Size Remove(Rank low, Rank high);
  T Remove(Rank r);
  /*
  void Unsort();
  void BubbleSort();
  void MergeSort(Rank low, Rank high);
  Rank BinSearch(const T &elem , Rank low, Rank high) const;
  Size Deduplicate();
  Size Uniquify();
  */

 protected:
  // 扩容
  void Expand();
  // 缩容
  void Shrink();

  // 个数
  Rank size_;
  // 容量
  Size capacity_;
  // 数据
  Ptr p_elem_;

 private:
  // 根据当前 size_ 和 capacity_ 分配空间 (处理 capacity_ 下限)
  void Allocate();
  // 根据当前 size_ 从 low 拷贝数组 初始化
  void InitCopyFrom(CPtr p_elem, Rank low);
  // 处理 capacity 范围
  void ProcessCapacity();
  // 检测 参数范围, 如果失败会抛出异常
  void CheckRange(Rank low, Rank high);
  // 检测 参数范围, 如果失败会抛出异常
  void CheckVectorRange(Size size, Rank low, Rank high);

  // void Merge(Rank low1, Rank high1, Rank low2, Rank high2);
};

template <typename T>
Vector<T>::Vector(Size size, T elem) :
    size_(size), capacity_(size_ << 1), p_elem_(nullptr) {
  ProcessCapacity();
  Allocate();
  for (Rank i = 0; i != size_; ++i) {
    p_elem_[i] = elem;
  }
}

template <typename T>
Vector<T>::Vector(CPtr p_elem, Size size)
    : size_(size), capacity_(size_ << 1), p_elem_(nullptr) {
  ProcessCapacity();
  Allocate();
  InitCopyFrom(p_elem, 0);
}

template <typename T>
Vector<T>::Vector(CPtr p_elem, Rank low, Rank high)
    : size_(high - low), capacity_(size_ << 1), p_elem_(nullptr) {
  CheckRange(low, high);
  ProcessCapacity();
  Allocate();
  InitCopyFrom(p_elem, low);
}

template <typename T>
Vector<T>::Vector(const Vector<T>& rhs)
  : size_(rhs.size()), capacity_(size_ << 1), p_elem_(nullptr) {
  ProcessCapacity();
  Allocate();
  InitCopyFrom(rhs.p_elem_, 0);
}

template <typename T>
Vector<T>::Vector(const Vector<T>& rhs, Rank low, Rank high)
    : size_(high - low), capacity_(size_ << 1), p_elem_(nullptr) {
  CheckVectorRange(rhs.size(), low, high);
  Allocate();
  InitCopyFrom(rhs.p_elem_, low);
}

template <typename T>
Vector<T> &Vector<T>::operator=(const Vector<T> &rhs) {
  if (&rhs == this) {
    return *this;
  }

  Size size_temp = rhs.size();
  Size capacity_temp = size_temp << 1;

  capacity_temp = capacity_temp < size_ ? size_ : capacity_temp;
  capacity_temp = capacity_temp < kDefaultCapacity ?
      kDefaultCapacity : capacity_temp;

  Ptr p_elem_temp = new T[capacity_temp];
  for (Rank i = 0; i != size_temp; ++i) {
    p_elem_temp[i] = rhs[i];
  }

  auto p_elem_old = p_elem_;
  p_elem_ = p_elem_temp;
  size_ = size_temp;
  capacity_ = capacity_temp;
  delete [] p_elem_old;

  return *this;
}

template <typename T>
Vector<T>::~Vector() {
  delete [] p_elem_;
}

template<typename T>
VectorBase::Size Vector<T>::Disordered() const {
  Size unordered_num = 0;
  for (Rank i = 0; i < size_ - 1; ++i) {
    if ((*this)[i] > (*this)[i + 1]) {
      ++unordered_num;
    }
  }
  return unordered_num;
}

template <typename T>
VectorBase::Rank Vector<T>::Find(const T &elem) const {
  return Find(elem, 0, size_);
}

template <typename T>
VectorBase::Rank Vector<T>::Find(const T &elem, Rank low, Rank high) const {
  return 0;
}

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
void Vector<T>::Traverse(void (* const visit)(T &elem)) {
  for (Rank i = 0; i < size_; ++i) {
    visit(p_elem_[i]);
  }
}

template <typename T>
void Vector<T>::Traverse(void (* const visit)(const T &elem)) const {
  for (Rank i = 0; i < size_; ++i) {
    visit(p_elem_[i]);
  }
}

template <typename T>
void Vector<T>::Expand() {
  if (size_ < capacity_) {
    return;
  }
  Size capacity_temp = capacity_ << 1 < kDefaultCapacity << 1 ?
                       kDefaultCapacity << 1 : capacity_ << 1;
  Ptr p_elem_temp = new T[capacity_temp];
  for (Rank i = 0; i != size_; ++i) {
    p_elem_temp[i] = p_elem_[i];
  }
  Ptr p_temp = p_elem_;
  p_elem_ = p_elem_temp;
  p_elem_temp = p_temp;
  delete [] p_elem_temp;
  capacity_ = capacity_temp;
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
  Ptr p_temp = p_elem_;
  p_elem_ = p_elem_temp;
  p_elem_temp = p_temp;
  delete [] p_elem_temp;
  capacity_ = capacity_temp;
}

template <typename T>
void Vector<T>::Allocate() {
  p_elem_ = new T[capacity_];
}

template <typename T>
void Vector<T>::InitCopyFrom(CPtr p_elem, Rank low) {
  for (Rank i = 0; i != size_; ++i) {
    p_elem_[i] = p_elem[low + i];
  }
}

template <typename T>
void Vector<T>::ProcessCapacity() {
  // 处理 capacity_ 上溢
  capacity_ = capacity_ < size_ ? size_ : capacity_;
  // 处理 capacity_ 下溢
  capacity_ = capacity_ < kDefaultCapacity ? kDefaultCapacity : capacity_;
}

template <typename T>
void Vector<T>::CheckRange(const Rank low, const Rank high) {
  if (high < low) {
    throw std::runtime_error("low must less equal than high");
  }
}

template <typename T>
void Vector<T>::CheckVectorRange(const Size size, const Rank low,
                                 const Rank high) {
  if (high > size) {
    throw std::runtime_error("high should less equal than size");
  }
  CheckRange(low, high);
}

/*
template <typename T>
VectorBase::Size vector<T>::Disordered() const {
  Size num = 0;
  for (Rank i = 0; i < size_ - 1; ++i) {
    if (p_elem_[i] > p_elem_[i + 1]) {
      ++num; 
    }
  }
  return num;
}




template <typename T>
void vector<T>::Unsort() {
  unsigned long seeds = 
      std::chrono::system_clock::now().time_since_epoch().count();
  static std::default_random_engine e(seeds);
  std::uniform_int_distribution<unsigned long> u(0, size_ - 1);
  for (Rank i = size_ - 1; i > 0; --i) {
    std::swap(p_elem_[i], p_elem_[u(e) % i]);
  }
}
template <typename T>
void vector<T>::BubbleSort() {
  if (size_ < 2) {
    return ;
  }
  using std::swap;
  for (Rank pos = size_, last_swap_pos; 1 < pos; pos = last_swap_pos) {
    last_swap_pos = 1;
    for (Rank i = 0; i < pos - 1; ++i) {
      if (p_elem_[i] > p_elem_[i + 1]) {
        std::swap(p_elem_[i], p_elem_[i + 1]);
        last_swap_pos = i + 1;
      }
    }
  }
}

template <typename T>
void vector<T>::MergeSort(Rank low, Rank high) {
  if (high - low < 2) {
    return ;
  } else {
    Rank mi = (low + high) >> 1;
    MergeSort(low, mi);
    MergeSort(mi, high);
    Merge(low, mi, mi, high);
  }
}

template <typename T>
void vector<T>::Merge(Rank low1, Rank high1, Rank low2, Rank high2) {
  Ptr temp_ptr(new T[high1 - low1]);
  for (Rank i = 0, low_temp = low1; low_temp < high1; ++i, ++low_temp) {
    temp_ptr[i] = p_elem_[low_temp];
  }
  const Rank kLow1Base = low1;
  Rank new_pos = low1;
  while ((low1 < high1) && (low2 < high2)) {
    if (p_elem_[low2] < temp_ptr[low1 - kLow1Base]) {
      p_elem_[new_pos++] = p_elem_[low2];
      ++low2;
    } else {
      p_elem_[new_pos++] = temp_ptr[low1 - kLow1Base];
      ++low1;
    }
  }
  while (low1 < high1) {
    p_elem_[new_pos++] = temp_ptr[low1 - kLow1Base];
    ++low1;
  }
}

template <typename T>
VectorBase::Rank vector<T>::Find(const T &elem, Rank low, Rank high) const {
  while (low < high) {
    --high;
    if (elem == p_elem_[high]) {
      return high;
    }
  }
  return --high;  //  找不到则返回比 high 大的秩
}

template <typename T> 
VectorBase::Rank 
vector<T>::BinSearch(const T &elem , Rank low, Rank high) const {
  while (low < high) {
    Size mid = (low + high) >> 1;
    if (p_elem_[mid] <= elem) {
      low = mid + 1;
    } else {
      high = mid;
    }
  }
  return --low;
}

template <typename T>
VectorBase::Size vector<T>::Deduplicate() {
  if (size_ < 2) {
    return 0;
  }
  Size old_size = size_;
  for (Rank i = 1; i < size_; ++i) {
    Size dupli_pos = Find(p_elem_[i], 0, i);
    if (dupli_pos < i) {      
      Remove(i);      
      --i;    
    }  
  }  
  return old_size - size_;
}

template <typename T>
VectorBase::Size vector<T>::Uniquify() {
  if (size_ < 2) {
    return 0;
  }
  Rank right_sentry = 1;
  for (Rank i = 1; i < size_; ++i) {
    if (p_elem_[i] != p_elem_[i - 1]) {
      p_elem_[right_sentry++] = p_elem_[i];
    }
  }
  Size result = size_ - right_sentry;
  size_ = right_sentry;
  return result;
}

 */

template <typename T>
VectorBase::Rank Vector<T>::Insert(Rank r, const T &elem) {
  if (r > size_ ) {
    return r;
  }
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
  if (high > size_) {
    high = size_;
  }
  Rank i = low;
  while(high < size_) {
    p_elem_[i++] = p_elem_[high++];
  }
  size_ -= size_ - low;
  Shrink();
  return high - low;
}

template <typename T>
T Vector<T>::Remove(Rank r) {
  T temp = (*this)[r];
  Remove(r, r+1);
  return temp;
}

/**
 * 遍历调用对象类型
 */
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

}  // namespace dsa_cpp

#endif