#ifndef DS_CPP_LIST_H
#define DS_CPP_LIST_H

#include <random>
#include <chrono>
#include <iostream>
#include <stdexcept>
#include <utility>

#include "list_node.h"
#include "list_error.h"

namespace ds_cpp {

class ListBase {
 public:
  // 下标类型 (秩) [low, high) 范围为: [0, 2^k)
  using Rank = unsigned long long;
  // 个数类型 (数)
  using Size = unsigned long long;
  // 最大容量 2^k - 1
  static constexpr Size kMaxSize = -1;
};

template <typename>
class List;

template <typename T>
void swap(List<T> &lhs, List<T> &rhs) noexcept;

template <typename T>
class List : public ListBase {

  friend void swap<T>(List<T> &lhs, List<T> &rhs) noexcept;
 public:

  using LNP = typename ListNode<T>::LNP;

  /*---------------------------- 拷贝控制 -----------------------------------*/
  List();
  List(const T array[], int n);
  List(const List &rhs);
  List(List &&rhs) noexcept ;
  List &operator=(const List &rhs);
  List &operator=(List &&rhs) noexcept;
  ~List();

  /*--------------------------- 只读访问 ------------------------------------*/
  // 返回元素数量
  inline Size size() const { return size_; }
  // 是否为空
  inline bool Empty() const { return !size_; }
  // 返回首哨兵
  inline LNP header() const { return header_; }
  // 返回尾哨兵
  inline LNP trailer() const { return trailer_; }

  // 下标随机访问(不可修改)
  const T& operator[](Rank r) const;
  // 下标随机访问(可修改, 委托 const 函数)
  T& operator[](Rank r);

  // 访问器(不可修改)
  template <typename VST> void Traverse(const VST &visit) const ;
  // 访问器(可修改)
  template <typename VST> void Traverse(const VST &visit);

  // 返回 p 及之后 n - 1 个位置中最大数的位置
  LNP Max(LNP p, Size n) const;
  // 返回连接逆序数
  Size Disordered() const;

  /*--------------------------- 查找访问 ------------------------------------*/
  // 无序查找, 在 p 的真前缀 n 个节点中寻找靠后等于 elem 节点位置, 没有找到则返回 nullptr
  LNP FindBefore(T const &elem, Size n, LNP p) const;
  // 无序查找, 在 p 的真后缀 n 个节点中寻找靠前等于 elem 节点位置, 没有找到则返回 nullptr
  LNP FindAfter(T const &elem, Size n, LNP p) const;

  // 有序查找, 在 p 的真前缀 n 个节点中寻找靠后等于 elem 节点位置, 没有找到则返回 左边界
  LNP SearchBefore(T const &elem, Size n, LNP p) const;
  // 有序查找, 在 p 的真后缀 n 个节点中寻找靠前等于 elem 节点位置, 没有找到则返回 左边界
  LNP SearchAfter(T const &elem, Size n, LNP p) const;


  /*--------------------------- 可写访问 ------------------------------------*/
  // 头插入
  LNP InsertAsFirst(const T &elem);
  // 尾插入
  LNP InsertAsLast(const T &elem);
  // 在 p 之前插入, 返回插入后的节点位置或者返回 nullptr
  LNP InsertBefore(LNP p, const T &elem);
  // 在 p 之后插入, 返回插入后的节点位置或者返回 nullptr
  LNP InsertAfter(LNP p, const T &elem);

  // 清空列表
  void Clear();
  // 删除指定位置的节点, 如果删除不成功则返回 nullptr
  T Remove(LNP p);
  // 无序去重
  Size Deduplicate();
  // 有序去重
  Size Uniquify();

  /*---------------------------  排序  ------------------------------------*/
  // 选择排序
  void SelectSort();
  // 插入排序
  void InsertSort();
  // 归并排序
  void MergeSort();

 protected:

  /*--------------------------- 检测参数 ------------------------------------*/
  // 检测 访问下标是否有效
  void CheckVisitIndex(Rank r) const ;
  // 检测 low <= high, 如果超出范围会抛出异常
  void CheckRange(Rank low, Rank high) const ;
  // 检测是否是有效的指针
  bool CheckVisitPosition(LNP p) const ;
  // 检测是否是有效的指针
  bool CheckInsertAfterPosition(LNP p) const ;
  // 检测是否是有效的指针
  bool CheckInsertBeforePosition(LNP p) const ;

  /*--------------------------- 数据成员 ------------------------------------*/
  Rank size_;    // 个数
  LNP header_;   // 头部哨兵
  LNP trailer_;  // 尾部哨兵

 private:
  // 初始化 首尾哨兵
  void Init();
  // 从 p_source 所指处拷贝 num 个元素(包含所指) 插入到 p_pre 之后
  void CopyFrom(LNP p_source, Size num, LNP p_pre);

};

template <typename T>
List<T>::List() : size_(0), header_(nullptr), trailer_(nullptr) {
  Init();
}

template <typename T>
List<T>::List(const T array[], int n)
    : size_(0), header_(nullptr), trailer_(nullptr) {
  Init();
  for (int i = 0; i < n; ++i) {
    InsertAsLast(array[i]);
  }
}

template <typename T>
List<T>::List(const List &rhs)
    : size_(0), header_(nullptr), trailer_(nullptr) {
  Init();
  CopyFrom(rhs.header()->succ_, rhs.size(), header());
}

template <typename T>
List<T>::List(List &&rhs) noexcept
    : size_(rhs.size_), header_(rhs.header_), trailer_(rhs.trailer_) {
  rhs.size_ = 0;
  rhs.header_ = nullptr;
  rhs.trailer_ = nullptr;
}

template <typename T>
List<T> &List<T>::operator=(const List &rhs) {
  using std::swap;
  if (&rhs != this) {
    List temp(rhs);
    swap(*this, temp);
  }
  return *this;
}

template <typename T>
List<T> &List<T>::operator=(List &&rhs) noexcept {
  if (&rhs != this) {
    Clear();
    delete header_;
    delete trailer_;

    size_ = rhs.size_;
    header_ = rhs.header_;
    trailer_ = rhs.trailer_;

    rhs.size_ = 0;
    rhs.header_ = nullptr;
    rhs.trailer_ = nullptr;
  }
  return *this;
}

template <typename T>
List<T>::~List() {
  Clear();
  delete trailer_;
  delete header_;
}

template <typename T>
const T& List<T>::operator[](Rank r) const {
  CheckVisitIndex(r);
  auto p = header()->succ_;
  while (r--) {
    p = p->succ_;
  }
  return p->data_;
}

template <typename T>
T& List<T>::operator[](Rank r) {
  return const_cast<T &>(
      const_cast<const List<T> &>(*this)[r]
  );
}

template <typename T>
template <typename VST>
void List<T>::Traverse(const VST &visit) const {
  auto p = header();
  while ((p = p->succ_) != trailer()) {
    visit(p->data_);
  }
}

template <typename T>
template <typename VST>
void List<T>::Traverse(const VST &visit) {
  auto p = header();
  while ((p = p->succ_) != trailer()) {
    visit(p->data_);
  }
}

template <typename T>
typename List<T>::LNP List<T>::Max(LNP p, Size n) const {
  if (!p || p == trailer() || n < 2) {
    return nullptr;
  }

  LNP max_p = p;
  for (--n, p = p->succ_; n && p!= trailer(); p = p->succ_) {
    if (p->data_ > max_p->data_) {
      max_p = p;
    }
  }
  return max_p;
}

template <typename T>
typename List<T>::Size List<T>::Disordered() const {
  Size num = 0;
  if (size_ < 2) {
    return num;
  }

  for (auto pp = header()->succ_, p = pp->succ_;
       p != trailer();
       pp = p, p = p->succ_) {
    if (p->data_ < pp->data_) {
      ++num;
    }
  }
  return num;
}

template <typename T>
typename List<T>::LNP List<T>::FindBefore(T const &elem, Size n, LNP p) const {
  if (!p) {
    return nullptr;
  }

  // 四种情况:
  // p != nullptr && p != header() && n > 0 && p->elem == elem
  // p != nullptr && p != header() && n == 0
  // p != nullptr && p == header()
  // p == nullptr
  for (p = p->pred_; n && p && p->data_ != elem; --n, p = p->pred_);
  return n && p && p != header() ? p : nullptr;
}

template <typename T>
typename List<T>::LNP List<T>::FindAfter(T const &elem, Size n, LNP p) const {
  if (!p) {
    return nullptr;
  }

  for (p = p->succ_; n && p && p->data_ != elem; --n, p = p->succ_);
  return n && p && p != trailer() ? p : nullptr;
}

template <typename T>
typename List<T>::LNP List<T>::SearchBefore(T const &elem, Size n, LNP p) const{
  if (!p) {
    throw std::runtime_error(list_error::kNullptrError);
  }

  for (p = p->pred_; n && p && p->data_ > elem; --n, p = p->pred_);
  return p ? p : header();
}

template <typename T>
typename List<T>::LNP List<T>::SearchAfter(T const &elem, Size n, LNP p) const {
  if (!p) {
    throw std::runtime_error(list_error::kNullptrError);
  }

  for (p = p->succ_; n && p && p->data_ < elem; --n, p = p->succ_);
  return p ? p->pred_ : trailer()->pred_;
}

template <typename T>
typename List<T>::LNP List<T>::InsertAsFirst(const T &elem) {
  if (size_ == kMaxSize) {
    return nullptr;
  }
  ++size_;
  return header()->InsertAsSucc(elem);
}

template <typename T>
typename List<T>::LNP List<T>::InsertAsLast(const T &elem) {
  if (size_ == kMaxSize) {
    return nullptr;
  }
  ++size_;
  return trailer()->InsertAsPred(elem);
}

template <typename T>
typename List<T>::LNP List<T>::InsertBefore(LNP p, const T &elem) {
  if (!CheckInsertBeforePosition(p) || size_ == kMaxSize) {
    return nullptr;
  }
  ++size_;
  return p->InsertAsPred(elem);
}

template <typename T>
typename List<T>::LNP List<T>::InsertAfter(LNP p, const T &elem) {
  if (!CheckInsertAfterPosition(p) || size_ == kMaxSize) {
    return nullptr;
  }
  ++size_;
  return p->InsertAsSucc(elem);
}

template <typename T>
void List<T>::Clear() {
  while (size_) {
    auto p_temp = header()->succ_;
    header()->succ_ = p_temp->succ_;
    p_temp->succ_->pred_ = header();
    delete p_temp;
    --size_;
  }
}

template <typename T>
T List<T>::Remove(LNP p) {
  if (!CheckVisitPosition(p)) {
    throw std::runtime_error(list_error::kVisitPositionError);
  }

  T temp = p->data_;
  p->pred_->succ_ = p->succ_;
  p->succ_->pred_ = p->pred_;
  delete p;
  --size_;
  return temp;
}

template <typename T>
ListBase::Size List<T>::Deduplicate() {
  if (size_ < 2) {
    return 0;
  }

  Size old_size = size_;
  Rank prev_num = 0;
  for (auto p = header()->succ_; p != trailer(); p = p->succ_) {
    auto pos = FindBefore(p->data_, prev_num, p);
    if (pos) {
      Remove(pos);
      p = p->pred_;
    } else {
      ++prev_num;
    }
  }
  return old_size - size_;
}

template <typename T>
ListBase::Size List<T>::Uniquify() {
  if (size_ < 2) {
    return 0;
  }

  Size old_size = size_;
  auto pp = header()->succ_;
  auto p = pp->succ_;
  while (p != trailer()) {
    if (pp->data_ == p->data_) {
      Remove(p);
      p = pp->succ_;
    } else {
      pp = p;
      p = p->succ_;
    }
  }
  return old_size - size_;
}

template <typename T>
void List<T>::SelectSort() {

}

template <typename T>
void List<T>::InsertSort() {
  Size pred_num = 0;
  auto p = header()->succ_;
  while (p != trailer()) {
    InsertAfter(SearchBefore(p->data_, pred_num, p), p->data_);
    p = p->succ_;
    Remove(p->pred_);
    ++pred_num;
  }
}

template <typename T>
void List<T>::MergeSort() {

}

template <typename T>
void List<T>::CheckVisitIndex(Rank r) const {
  if (r >= size_) {
    throw std::runtime_error(list_error::kVisitIndexError);
  }
}

// 检测 low <= high, 如果超出范围会抛出异常
template <typename T>
void List<T>::CheckRange(Rank low, Rank high) const {
  if (high < low) {
    throw std::runtime_error(list_error::kInvalidRange);
  }
}

template <typename T>
bool List<T>::CheckVisitPosition(LNP p) const {
  return p && p!= header() && p != trailer();
}

template <typename T>
bool List<T>::CheckInsertAfterPosition(LNP p) const {
  return p && p != trailer();
}

template <typename T>
bool List<T>::CheckInsertBeforePosition(LNP p) const {
  return p && p != header();
}

template <typename T>
void List<T>::Init() {
  header_ = new ListNode<T>;
  trailer_ = new ListNode<T>;
  header_->succ_ = trailer_;
  trailer_->pred_ = header_;
  size_ = 0;
}

template <typename T>
void List<T>::CopyFrom(LNP p_source, Size num, LNP p_pre) {
  while (num--) {
    p_pre = p_pre->InsertAsSucc(p_source->data_);
    p_source = p_source->succ_;
    ++size_;
  }
}

// 遍历调用对象类型
template <typename T>
class ListTraverse {
 public:
  explicit ListTraverse(std::ostream &io) : io_(io) {}
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
void swap(List<T> &lhs, List<T> &rhs) noexcept {
  using std::swap;
  swap(lhs.size_, rhs.size_);
  swap(lhs.header_, rhs.header_);
  swap(lhs.trailer_, rhs.trailer_);
}

//LNP(T)find(const T &e) const { // 全局查找
//  find(e, _size, trailer);
//}

//LNP(T)search(const T &e, int n, LNP(T)p) const { // 在p的n个真前驱且包括左哨兵查找<=e的最大秩节点
//  while (n--) // 遍历n次
//    if ((p = p->pred)->data <= e) // <=e 则直接返回
//      return p;
//  return p->pred; // 没找到则返回左哨兵
//}
//LNP(T)search(const T &e) {  // 全局区间查找
//  search(e, _size, trailer);
//}


//void insertSort(LNP(T)p, int n) { // 对 包括p在内的 n各节点排序  平均比较次数=(n-1)n/2=O(n^2)
//for (int r = 0; r < n; ++r) {
//insertAfter(search(p->data, r, p), p->data); // 在以排序范围内先插入再删除
//p = p->succ;  // 移动到下一个
//remove(p->pred); // 删除多余前驱
//}
//}
//void selectionSort(LNP(T)p, int n) {
//LNP(T)head = p->pred; // 设定区间
//LNP(T)tail = p;
//for (int i = 0; i < n; ++i) tail = tail->succ;
//while (1 < n) {
//LNP(T)m = selectMax(head->succ, n); // 每趟第一个节点会改变 找到最大节点位置
//auto temp = m->data;
//m->data = tail->pred->data;
//tail->pred->data = temp;
////insertBefore(tail, remove(m));  // 移动
//tail = tail->pred; // 更改区间
//--n; // 缩小范围
//}
//}

//void mergeSort(LNP(T)&p, int n) {
//if (n < 2) return;
//int m = n >> 1;
//LNP(T)q = p;
//for (int i = 0; i < m; ++i) q = q->succ;
//// p 指向前半段第一个 q指向后半段第一个 前半段一共m个 后半段一共n-m个
//mergeSort(p, m);
//mergeSort(q, n - m);
//merge(p, m, *this, q, n - m);
//}
//void merge(LNP(T)&p, int n, List<T> &L, LNP(T)q, int m) { // p实参应不是任何一个点的前后指针
//LNP(T)pp = p->pred; // 记录p原来的位置
//while (0 < m) {  // (0<m&&0<n)
//if (n > 0 && p->data <= q->data) {
//if (q == (p = p->succ)) break;
//n--;
//} else {  // (m>0 && q->data<p->data)
//insertBefore(p, q->data);
//q = q->succ;
//L.remove(q->pred);
//m--;
//}
//}
//p = pp->succ;
//}
//void mergeSort() {
//  auto h = header->succ;
//  mergeSort(h, _size);
//} //注意是header->succ的副本

}  // namespace ds_cpp

#endif