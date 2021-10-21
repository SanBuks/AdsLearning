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
  // 下标类型 (秩) [low, high)
  using Rank = unsigned long long;
  // 个数类型 (数)
  using Size = unsigned long long;

  // 装载因子 (size_ >= kMinLoadFactor * capacity_)
  static constexpr double kMinLoadFactor = 0.25;
  // 默认容量
  static constexpr Size kDefaultCapacity = 3;
  // 最大容量/个数 2^k - 1 [0, 2^k - 2)
  static constexpr Size kMaxSize = -2;
  // 空余的一个 作为 溢出哨兵
  static constexpr Rank kNonPosition = -1;
};

constexpr double VectorBase::kMinLoadFactor;
constexpr VectorBase::Size VectorBase::kDefaultCapacity;
constexpr VectorBase::Size VectorBase::kMaxSize;
constexpr VectorBase::Rank VectorBase::kNonPosition;

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
  const T& operator[](Rank r) const;
  /**** 只读访问接口 (非内联) ****/
  Rank Max(Rank low, Rank high) const;
  Rank Max() const;
  Size Disordered() const;
  Rank Find(const T &elem, Rank low, Rank high) const;
  Rank Find(const T &elem) const;

  template <typename VST> void Traverse(const VST &visit);
  template <typename VST> void Traverse(const VST &visit) const ;

  /****可写访问接口****/
  T& operator[](Rank r);
  // 区间转置
  void Reverse(Rank low, Rank high);
  // 区间置乱
  void Unsort(Rank low, Rank high);
  void Unsort();
  // 指定位置插入
  Rank Insert(Rank r, const T &elem);
  // 插入最后
  Rank Insert(const T &elem);
  // 区间删除
  Size Remove(Rank low, Rank high);
  // 指定位置删除
  T Remove(Rank r);
  // 无序区间去重
  Size Deduplicate(Rank low, Rank high);
  Size Deduplicate();
  // 有序区间去重
  Size Uniquify(Rank low, Rank high);
  Size Uniquify();

  /*
  void Unsort();
  void BubbleSort();
  void MergeSort(Rank low, Rank high);
  Rank BinSearch(const T &elem , Rank low, Rank high) const;
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
  // 根据当前 size_ 从 low 拷贝数组 size_ 个元素进行初始化
  void InitCopyFrom(CPtr p_elem, Rank low);
  // 处理 capacity 范围
  void ProcessCapacity();
  // 检测 low <= high, 如果超出范围会抛出异常
  void CheckRange(Rank low, Rank high) const ;
  // 检测 high <= size_, 如果超出范围会抛出异常
  void CheckUpBound(Size size, Rank high) const ;

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
  CheckRange(low, high);
  CheckUpBound(rhs.size(), high);
  ProcessCapacity();
  Allocate();
  InitCopyFrom(rhs.p_elem_, low);
}

template <typename T>
Vector<T> &Vector<T>::operator=(const Vector<T> &rhs) {
  if (&rhs == this) {
    return *this;
  }

  Size size_temp = rhs.size();
  Size capacity_temp = rhs.capacity_;

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
const T& Vector<T>::operator[](Rank r) const {
  CheckUpBound(size_ - 1, r);
  return p_elem_[r];
}

template<typename T>
VectorBase::Rank Vector<T>::Max(Rank low, Rank high) const {
  CheckRange(low, high);
  CheckUpBound(size_, high);
  if (low == high) {
    return kNonPosition;
  }
  Rank max_pos = low;
  for (Rank i = low + 1; i != high; ++i) {
    if ((*this)[i] > (*this)[max_pos]) {
      max_pos = i;
    }
  }
  return max_pos;
}

template<typename T>
VectorBase::Rank Vector<T>::Max() const {
  return Max(0, size_);
}

template<typename T>
VectorBase::Size Vector<T>::Disordered() const {
  if (size_ < 2) {
    return 0;
  }

  Size unordered_num = 0;
  for (Rank i = 0; i != size_ - 1; ++i) {
    if ((*this)[i] > (*this)[i + 1]) {
      ++unordered_num;
    }
  }
  return unordered_num;
}

template <typename T>
VectorBase::Rank Vector<T>::Find(const T &elem, Rank low, Rank high) const {
  CheckRange(low, high);
  CheckUpBound(size_, high);

  while(low < high) {
    if ((*this)[high - 1] == elem) {
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
void Vector<T>::Expand() {
  // 未满
  if (size_ < capacity_) {
    return;
  }
  // 已是上限
  if (size_ == kMaxSize) {
    throw std::runtime_error("Vector is full");
  }

  Size capacity_temp;
  // 处理 上限溢出
  if (kMaxSize >> 1 < capacity_) {
    capacity_temp = kMaxSize;
  } else {
  // 处理 下限
    capacity_temp = capacity_ << 1 < kDefaultCapacity << 1 ?
                    kDefaultCapacity << 1 : capacity_ << 1;
  }
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
  if (kMaxSize < size_) {
    throw std::runtime_error("size must less equal than kMaxSize");
  }
  // 处理 capacity_ 上溢
  capacity_ = capacity_ < size_ ? kMaxSize : capacity_;
  // 处理 capacity_ 下溢
  capacity_ = capacity_ < kDefaultCapacity ? kDefaultCapacity : capacity_;
}

template <typename T>
void Vector<T>::CheckRange(const Rank low, const Rank high) const {
  if (high < low) {
    throw std::runtime_error("low must less equal than high");
  }
}

template <typename T>
void Vector<T>::CheckUpBound(const Size size, const Rank high) const {
  if (high > size) {
    throw std::runtime_error("high should less equal than size");
  }
}

/*
template <typename T>
void vector<T>::Unsort() {
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
T& Vector<T>::operator[](Rank r) {
  return const_cast<T &>(
      static_cast<const Vector<T>&>(*this)[r]
  );
}

template <typename T>
void Vector<T>::Reverse(Rank low, Rank high) {
  CheckRange(low, high);
  CheckUpBound(size_, high);
  while (low < high) {
    T temp = (*this)[low];
    (*this)[low] = (*this)[high - 1];
    (*this)[high - 1] = temp;
    ++low, --high;
  }
}

template <typename T>
void Vector<T>::Unsort(Rank low, Rank high) {
  CheckRange(low, high);
  CheckUpBound(size_, high);

  unsigned long seeds =
      std::chrono::system_clock::now().time_since_epoch().count();
  static std::default_random_engine engine(seeds);
  std::uniform_int_distribution<Size> uniform_distribution(0, high - low);

  for (Rank i = high; i > low; --i) {
    Rank now_pos = i - 1;
    Rank swap_pos = low + uniform_distribution(engine) % (i - low);
    T temp = (*this)[now_pos];
    (*this)[now_pos] = (*this)[swap_pos];
    (*this)[swap_pos] = temp;
  }
}

template <typename T>
void Vector<T>::Unsort() {
  Unsort(0, size_);
}

template <typename T>
VectorBase::Rank Vector<T>::Insert(Rank r, const T &elem) {
  CheckUpBound(size_, r);
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
  CheckUpBound(size_, high);

  while(high < size_) {
    p_elem_[low++] = p_elem_[high++];
  }
  size_ -= size_ - low;
  Shrink();
  return high - low;
}

template <typename T>
T Vector<T>::Remove(Rank r) {
  // r 必须 < size_
  // 防止 r + 1 溢出 等效转换为 size_ - 1
  CheckUpBound(size_ - 1, r);
  T temp = (*this)[r];
  Remove(r, r+1);
  return temp;
}

template <typename T>
VectorBase::Size Vector<T>::Deduplicate(Rank low, Rank high) {
  CheckRange(low, high);
  CheckUpBound(size_, high);
  Size oldSize = size_;
  for (Rank i = low + 1; i < high; ++i) {
    auto pos = Find((*this)[i], low, i);
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
  CheckUpBound(size_, high);
  Size oldSize = size_;
  Rank right_pos = low;
  for (Rank i = right_pos + 1; i != high; ++i) {
    if ((*this)[right_pos] != (*this)[i]) {
      (*this)[++right_pos] = (*this)[i];
    }
  }
  size_ = right_pos + 1;
  return oldSize - size_;
}

template <typename T>
VectorBase::Size Vector<T>::Uniquify() {
  return Uniquify(0, size_);
}

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

}

#endif