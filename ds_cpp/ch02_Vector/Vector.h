#include <memory>
#include <utility>
#include <random>
#include <chrono>
#include <stdexcept>
#include <iostream>

namespace my_ads {

class VectorBase {
 public:
  using Rank = unsigned long;
  using Size = unsigned long;
  static constexpr Rank kDefaultCapacity = 3; 
  static constexpr double kMinLoadFactor = 0.25;
 private:
};

template <typename T>
class Vector : public VectorBase {
 public:
  using Ptr = std::unique_ptr<T[]>;

  Vector(T elem, Size size = 0);
  Vector(const T *array, Rank num);
  Vector(const T *array, Rank low, Rank high);
  Vector(const Vector<T> &vector);
  Vector(const Vector<T> &vector, Rank low, Rank high);
  Vector<T> &operator=(const Vector<T> &rhs);
  ~Vector();

  Size size() const { return size_; }
  Size capacity() const { return capacity_; }
  bool empty() const { return !size_;}
  const T& operator[] (Rank r) const { return p_elem_[r]; }
  T& operator[] (Rank r) { 
    return const_cast<T &>(static_cast<const Vector<T> &>(*this)[r]); 
  }

  Size Disordered() const;
  void Unsort();
  void BubbleSort();
  void MergeSort(Rank low, Rank high);

  template <typename VST>
  void Traverse(const VST &visit) const ;
  template <typename VST>
  void Traverse(const VST &visit);
  void Traverse(void (*visit)(const T &elem)) const ;

  Rank Find(const T &elem, Rank low, Rank high) const;
  Rank BinSearch(const T &elem , Rank low, Rank high) const;

  Rank Insert(Rank r, const T &elem);
  Size Remove(Rank low, Rank high);
  T Remove(Rank r);
  Size Deduplicate();
  Size Uniquify();

 protected:
  Rank size_;
  Size capacity_;
  Ptr p_elem_;

  void Expand();
  void Shrink();

 private:
  void InitCopyFrom(const T *array, Rank low, Rank high);
  void Merge(Rank low1, Rank high1, Rank low2, Rank high2);
};

template <typename T>
Vector<T>::Vector(T elem, Size size) : size_(size), capacity_(2 * size_) {
  if (size < 2) {
    capacity_ = kDefaultCapacity;
  }
  p_elem_.reset(new T[capacity_]);
  for (Rank i = 0; i < size_; ++i) {
    p_elem_[i] = elem;
  }
}

template <typename T>
Vector<T>::Vector(const T *array, Size num) {
  InitCopyFrom(array, 0, num);
}

template <typename T>
Vector<T>::Vector(const T *array, Rank low, Rank high) {
  InitCopyFrom(array, low, high);
}

template <typename T>
Vector<T>::Vector(const Vector<T> &vector) {
  const T *array = vector.p_elem_.get();
  Size num = vector.size();
  InitCopyFrom(array, 0, num);
}

template <typename T>
Vector<T>::Vector(const Vector<T> &vector, Rank low, Rank high) {
  const T *array = vector.p_elem_.get();
  InitCopyFrom(array, low, high);
}

template <typename T> 
VectorBase::Size Vector<T>::Disordered() const {
  Size num = 0;
  for (Rank i = 0; i < size_ - 1; ++i) {
    if (p_elem_[i] > p_elem_[i + 1]) {
      ++num; 
    }
  }
  return num;
}

template <typename T>
void Vector<T>::Traverse(void (*visit)(const T &elem)) const {
  for (Rank i = 0; i < size_; ++i) {
    visit(p_elem_[i]);
  }
}

template <typename T> template <typename VST>
void Vector<T>::Traverse(const VST &visit) const {
  for (Rank i = 0; i < size_; ++i) {
    visit(p_elem_[i]);
  }
}

template <typename T> template <typename VST>
void Vector<T>::Traverse(const VST &visit) {
  for (Rank i = 0; i < size_; ++i) {
    visit(p_elem_[i]);
  }
}

template <typename T>
Vector<T> &Vector<T>::operator=(const Vector<T> &rhs) {
  //  Self = Self
  if (&rhs == this) {
    return *this;
  }
  //  create temp Ptr firstly
  Size size_temp = rhs.size(); 
  Size capacity_temp = 2 * size_temp;
  if (size_temp < 2) {
    capacity_temp = kDefaultCapacity;
  }
  Ptr p_elem_temp(new T[capacity_temp]);
  for (Rank i = 0; i < size_temp; ++i) {
    p_elem_temp[i] = rhs[i];
  }
  //  update state
  p_elem_ = std::move(p_elem_temp);
  size_ = size_temp;
  capacity_ = capacity_temp;
  return *this;
}

template <typename T>
Vector<T>::~Vector() { }

template <typename T>
void Vector<T>::Unsort() {
  unsigned long seeds = 
      std::chrono::system_clock::now().time_since_epoch().count();
  static std::default_random_engine e(seeds);
  std::uniform_int_distribution<unsigned long> u(0, size_ - 1);
  for (Rank i = size_ - 1; i > 0; --i) {
    std::swap(p_elem_[i], p_elem_[u(e) % i]);
  }
}
template <typename T>
void Vector<T>::BubbleSort() {
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
void Vector<T>::MergeSort(Rank low, Rank high) {
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
void Vector<T>::Merge(Rank low1, Rank high1, Rank low2, Rank high2) { 
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
VectorBase::Rank Vector<T>::Find(const T &elem, Rank low, Rank high) const {
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
Vector<T>::BinSearch(const T &elem , Rank low, Rank high) const {
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
VectorBase::Size Vector<T>::Remove(Rank low, Rank high) {
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
T Vector<T>::Remove(Rank r) {
  T e = p_elem_[r];
  Remove(r, r + 1);
  return e;
}

template <typename T>
VectorBase::Size Vector<T>::Deduplicate() {
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
VectorBase::Size Vector<T>::Uniquify() {
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
VectorBase::Rank Vector<T>::Insert(Rank r, const T &elem) {  
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

template <typename T>
void Vector<T>::Expand() {  
  if (size_ < capacity_) {    
    return ;  
  }  
  if (capacity_ < kDefaultCapacity) {    
    capacity_ = kDefaultCapacity;  
  }  
  Size capacity_temp = capacity_ << 1;  
  Ptr p_elem_temp(new T[capacity_temp]);  
  for (Rank i = 0; i < size_; ++i) {    
    p_elem_temp[i] = p_elem_[i];  
  }  
  p_elem_ = std::move(p_elem_temp);  
  capacity_ = capacity_temp;
}

template <typename T>
void Vector<T>::Shrink() {  
  if (kMinLoadFactor <= size_ * 1.0 / capacity_) {    
    return ;  
  }  
  if (capacity_ < kDefaultCapacity * 2) {    
    return ;  
  }  
  Size capacity_temp = capacity_ >> 1;  
  Ptr p_elem_temp(new T[capacity_temp]);  
  for (Rank i = 0; i < size_; ++i) {
    p_elem_temp[i] = p_elem_[i];  
  }  
  p_elem_ = std::move(p_elem_temp);  
  capacity_ = capacity_temp;
}

template <typename T>
void Vector<T>::InitCopyFrom(const T *array, Rank low, Rank high) {  
  size_ = high - low;  
  capacity_ = 2 * size_;  
  if (size_ < 2) {    
    capacity_ = kDefaultCapacity;  
  }  
  p_elem_.reset(new T[capacity_]);  
  for (Rank i = 0; i < size_; ++i) {    
    p_elem_[i] = array[i];  
  }
}

}  // namespace my_ads