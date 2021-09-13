// cmake -G"MinGW Makefiles" -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DCMAKE_MAKE_PROGRAM=make ..
// chcp.com 65001
#ifndef DS_CPP_CH02_VECTOR_H
#define DS_CPP_CH02_VECTOR_H

#include <random>
#include <chrono>
#include <iostream>

namespace dsa_cpp {

class VectorBase {
 public:
  // 秩
  using Rank = unsigned long;
  // 个数
  using Size = unsigned long;
  // 初始个数
  static constexpr Rank kDefaultCapacity = 3;
  // 装载因子
  static constexpr double kMinLoadFactor = 0.25;
};

template <typename T>
class Vector : public VectorBase {
 public:
  using Ptr = T*;
  using CPtr = const T*;

  explicit Vector(Size size = 0, T elem = T());
  Vector(CPtr p_elem, Size n);
  Vector(CPtr p_elem, Rank lo, Rank hi);
  Vector(const Vector<T>& rhs);
  Vector(const Vector<T>& rhs, Rank lo, Rank hi);
  Vector<T> &operator=(const Vector<T> &rhs);

  ~Vector();


  // 只读访问接口
  Size size() const { return size_; }
  Size capacity() const { return capacity_; }
  bool Empty() const { return !size_; }
  const T& operator[](Rank r) const { return p_elem_[r]; }

  template <typename VST>
  void Traverse(const VST &visit) const ;
  void Traverse(void (*visit)(const T &elem)) const ;

  // 可写访问接口
  T& operator[] (Rank r) {
    return const_cast<T &>(
        static_cast<const Vector<T>&>(*this)[r]
    );
  }

  /*
  Size Disordered() const;
  void Unsort();
  void BubbleSort();
  void MergeSort(Rank low, Rank high);
  Rank Find(const T &elem, Rank low, Rank high) const;
  Rank BinSearch(const T &elem , Rank low, Rank high) const;
  Rank Insert(Rank r, const T &elem);
  Size Remove(Rank low, Rank high);
  T Remove(Rank r);
  Size Deduplicate();
  Size Uniquify();
  */

 protected:
  // 个数
  Rank size_;
  // 容量
  Size capacity_;
  // 数据区
  Ptr p_elem_;

  // 扩容
  void Expand();
  // 缩容
  void Shrink();

 private:
  // 拷贝初始化公用函数
  void InitCopyFrom(CPtr p_elem, Rank low, Rank high);
  /*
  void Merge(Rank low1, Rank high1, Rank low2, Rank high2);
   */
};

template <typename T>
Vector<T>::Vector(Size size, T elem) {
  capacity_ = size << 1 < kDefaultCapacity ? kDefaultCapacity : size << 1;
  size_ = size;
  p_elem_ = new T[capacity_];
  for (Rank i = 0; i != size_; ++i) {
    p_elem_[i] = elem;
  }
}

template <typename T>
Vector<T>::Vector(CPtr p_elem, Size size) : size_(size), capacity_(size_ << 1) {
  InitCopyFrom(p_elem, 0, size);
}

template <typename T>
Vector<T>::Vector(CPtr p_elem, Rank low, Rank high) {
  InitCopyFrom(p_elem, low, high);
}

template <typename T>
Vector<T>::Vector(const Vector<T>& rhs) {
  InitCopyFrom(rhs.p_elem_, 0, rhs.size_);
}

template <typename T>
Vector<T>::Vector(const Vector<T>& rhs, Rank low, Rank high) {
  InitCopyFrom(rhs.p_elem_, low, high);
}

template <typename T>
Vector<T> &Vector<T>::operator=(const Vector<T> &rhs) {
  if (&rhs == this) {
    return *this;
  }
  Size size_temp = rhs.size();
  Size capacity_temp =
      size_temp << 1 < kDefaultCapacity ? kDefaultCapacity : size_temp << 1;
  Ptr p_elem_temp = new T[capacity_temp];
  for (Rank i = 0; i != size_temp; ++i) {
    p_elem_temp[i] = rhs[i];
  }
  p_elem_ = p_elem_temp;
  size_ = size_temp;
  capacity_ = capacity_temp;
  return *this;
}

template <typename T>
Vector<T>::~Vector() {
  delete [] p_elem_;
}

template <typename T>
template <typename VST>
void Vector<T>::Traverse(const VST &visit) const {
  for (Rank i = 0; i != size_; ++i) {
    visit(p_elem_[i]);
  }
}

template <typename T>
void Vector<T>::Traverse(void (*visit)(const T &elem)) const {
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
  if (capacity_ * 1.0 * kMinLoadFactor < size_) {
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
};

template <typename T>
void Vector<T>::InitCopyFrom(CPtr p_elem, Rank low, Rank high){
  size_ = high < low ? 0 : high - low;
  capacity_ = size_ << 1 < kDefaultCapacity ? kDefaultCapacity : size_ << 1;
  p_elem_ = new T[capacity_];
  for (Rank i = 0; i != size_; ++i) {
    p_elem_[i] = p_elem[low + i];
  }
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
VectorBase::Size vector<T>::Remove(Rank low, Rank high) {
  if (high > size_ || low > high) {
    throw std::runtime_error("Vector::Remove():: wrong position!");
  }
  if (low == high) {
    return 0;
  }
  while (high < size_) {
    p_elem_[low++] = p_elem_[high++];
  }
  size_ = low;
  Shrink();
  return high - low;
}

template <typename T>
T vector<T>::Remove(Rank r) {
  T e = p_elem_[r];
  Remove(r, r + 1);
  return e;
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

template <typename T>
VectorBase::Rank vector<T>::Insert(Rank r, const T &elem) {
  if ( r > size_) {    
    throw std::runtime_error("Vector::insert():: wrong position!");  
  }  
  Expand();  
  for (Rank i = size_; i > r; --i) {    
    p_elem_[i] = p_elem_[i - 1];  
  }  
  p_elem_[r] = elem;  
  size_++;  
  return r;
}
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