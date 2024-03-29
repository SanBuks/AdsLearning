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

  // 返回 p 所指处 n 个位置中最大数的位置(包括 p 所指)
  LNP Max(LNP p, Size n) const;
  // 返回连接逆序数
  Size Disordered() const;

  /*--------------------------- 查找访问 ------------------------------------*/
  // 无序查找, 在 p 的真前缀 n 个节点中寻找靠后等于 elem 节点位置, 没有找到则返回 nullptr
  LNP FindBefore(T const &elem, Size n, LNP p) const;
  // 无序查找, 在 p 的真后缀 n 个节点中寻找靠前等于 elem 节点位置, 没有找到则返回 nullptr
  LNP FindAfter(T const &elem, LNP p, Size n) const;

  // 有序查找, 在 p 的真前缀 n 个节点中寻找靠后等于 elem 节点位置, 没有找到则返回 左边界
  LNP SearchBefore(T const &elem, Size n, LNP p) const;
  // 有序查找, 在 p 的真后缀 n 个节点中寻找靠前等于 elem 节点位置, 没有找到则返回 左边界
  LNP SearchAfter(T const &elem, LNP p, Size n) const;

  /*--------------------------- 可写访问 ------------------------------------*/
  // 头插入
  LNP InsertAsFirst(const T &elem);
  // 尾插入
  LNP InsertAsLast(const T &elem);

  // 在 p 之前插入, 返回插入后的节点位置或者返回 nullptr
  LNP InsertBefore(LNP p, const T &elem);
  // 在 p 之后插入, 返回插入后的节点位置或者返回 nullptr
  LNP InsertAfter(LNP p, const T &elem);

  // 把 p_source 所指元素移动到 p_target 之前
  LNP MoveBefore(LNP p_source, LNP p_target);
  // 把 p_source 所指元素移动到 p_target 之后
  LNP MoveAfter(LNP p_source, LNP p_target);

  // 区间转置 [p, p + n / trailer)
  Size Reverse(LNP p, Size n);
  Size Reverse();

  // 清空列表
  void Clear();
  // 删除指定位置的节点, 如果 p 非法则抛出异常, 返回 T 对性能和调用方便做了折中
  T Remove(LNP p);
  // 无序去重
  Size Deduplicate();
  // 有序去重
  Size Uniquify();

  /*---------------------------  排序  ------------------------------------*/
  // 选择排序 [p, p + n)
  void SelectSort(LNP p, Size n);
  void SelectSort();
  // 插入排序 [p, p + n)
  void InsertSort(LNP p, Size n);
  void InsertSort();
  // 归并排序 [p, p + n), 注意 p 为引用, 方便递归时更新头节点
  void MergeSort(LNP &p, Size n);
  void MergeSort();
  // 基数排序 [p, p + n)
  void RadixSort(LNP p, Size n);
  void RadixSort();

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
  /*--------------------------- 功能函数 ------------------------------------*/
  // 初始化 首尾哨兵
  void Init();
  // 从 p_source 所指处拷贝 num 个元素(包含所指) 插入到 p_pre 之后
  void CopyFrom(LNP p_source, Size num, LNP p_pre);
  // 将 pa 所指处 n 个元素, 与 list 中 pb 所指处 m 个元素合并到 pa 所指处
  void Merge(LNP pa, Size n, List<T> &list, LNP pb, Size m);

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
  if (!n || !CheckVisitPosition(p)) {
    return nullptr;
  }

  LNP max_p = p;
  for (--n, p = p->succ_; n && p!= trailer(); p = p->succ_, --n) {
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
    if (pp->data_ > p->data_) {
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
typename List<T>::LNP List<T>::FindAfter(T const &elem, LNP p, Size n) const {
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
typename List<T>::LNP List<T>::SearchAfter(T const &elem, LNP p, Size n) const {
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
typename List<T>::LNP List<T>::MoveBefore(LNP p_source, LNP p_target) {
  if (!CheckVisitPosition(p_source) || !p_target || p_target == header()) {
    return nullptr;
  }

  if (p_source != p_target) {
    // 脱离
    p_source->succ_->pred_ = p_source->pred_;
    p_source->pred_->succ_ = p_source->succ_;

    // 融入
    p_source->succ_ = p_target;
    p_source->pred_ = p_target->pred_;

    // 接洽
    p_target->pred_->succ_ = p_source;
    p_target->pred_ = p_source;
  }
  return p_source;
}

template <typename T>
typename List<T>::LNP List<T>::MoveAfter(LNP p_source, LNP p_target) {
  if (!CheckVisitPosition(p_source) || !p_target || p_target == trailer()) {
    return nullptr;
  }

  if (p_source != p_target) {
    p_source->succ_->pred_ = p_source->pred_;
    p_source->pred_->succ_ = p_source->succ_;

    p_source->succ_ = p_target->succ_;
    p_source->pred_ = p_target;

    p_target->succ_->pred_ = p_source;
    p_target->succ_ = p_source;
  }
  return p_source;
}

template <typename T>
typename List<T>::Size List<T>::Reverse(LNP p_start, Size n) {
  Size reverse_num = 0;
  if (!CheckVisitPosition(p_start) || !n) {
    return reverse_num;
  }

  auto p_end = p_start;
  while (p_end != trailer() && n--) {
    p_end = p_end->succ_;
  }

  auto ppp = p_start->pred_;  // 左边界
  auto pp = p_start;          // 前节点
  auto p = pp->succ_;         // 当前节点

  while (p != p_end && p != trailer()) {
    auto p_temp = p->succ_;
    p->succ_ = pp;
    pp->pred_ = p;
    pp = p;
    p = p_temp;
    ++reverse_num;
  }

  ppp->succ_->succ_ = p;
  p->pred_ = ppp->succ_;

  ppp->succ_ = pp;
  pp->pred_ = ppp;

  return reverse_num + 1;
}

template <typename T>
typename List<T>::Size List<T>::Reverse() {
  return Reverse(header()->succ_, size_);
}

template <typename T>
void List<T>::Clear() {
  // 由于 Remove 函数需要返回删除的对象, 为了性能这里手动删除
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
    if (pos) {       // 如果存在 重复元素, 有可能存在多个重复元素
      Remove(pos);
      p = p->pred_;  // 保持位置不动
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
void List<T>::SelectSort(LNP p, Size n) {
  if (n < 2 || !CheckVisitPosition(p)) {
    return;
  }

  Size len = 1;             // [p, p + n / trailer) 长度
  auto pre_pos = p->pred_;  // 左边界, 防止 p 所指元素移动
  auto end_pos = p;         // 右边界

  while ((end_pos = end_pos->succ_) != trailer()) {
    if (++len > n) {        // 取较小值
      len = n;
      break;
    }
  }

  while (len > 1) {
    end_pos = MoveBefore(Max(pre_pos->succ_, len), end_pos);
    --len;
  }
}

template <typename T>
void List<T>::SelectSort() {
  SelectSort(header()->succ(), size_);
}

template <typename T>
void List<T>::InsertSort(LNP p, Size n) {
  if (n < 2 || !CheckVisitPosition(p)) {
    return;
  }

  Size pred_num = 0;
  while (p != trailer() && n > 0) {
    auto p_temp = p->succ_;
    MoveAfter(p, SearchBefore(p->data_, pred_num, p));
    p = p_temp;
    ++pred_num, --n;
  }
}

template <typename T>
void List<T>::InsertSort() {
  InsertSort(header()->succ_, size_);
}

template <typename T>
void List<T>::MergeSort(LNP &p, Size n) {
  if (n < 2 || !CheckVisitPosition(p)) {
    return;
  }

  Size len = 1;             // [p, p + n / trailer) 长度
  auto pre_pos = p->pred_;  // 左边界, 防止 p 所指元素移动
  auto end_pos = p;         // 右边界

  while ((end_pos = end_pos->succ_) != trailer()) {
    if (++len > n) {        // 取较小值
      len = n;
      break;
    }
  }

  Size m = len >> 1;
  LNP pa = p, pb = p;
  for (Size i = 0; i < m; ++i) {
    pb = pb->succ_;
  }

  MergeSort(pa, m);
  MergeSort(pb, len - m);
  Merge(pa, m, *this, pb, len - m);

  p = pre_pos->succ_;        // 更新首节点
}

template <typename T>
void List<T>::MergeSort() {
  MergeSort(header()->succ_, size_);
}

template <typename T>
void List<T>::RadixSort(LNP p, Size n) {
  if (n < 2 || !CheckVisitPosition(p)) {
    return;
  }

  Size len = 1;             // [p, p + n / trailer) 长度
  auto pre_pos = p->pred_;  // 左边界, 防止 p 所指元素移动
  auto end_pos = p;         // 右边界

  while ((end_pos = end_pos->succ_) != trailer()) {
    if (++len > n) {        // 取较小值
      len = n;
      break;
    }
  }

  using RadixType = unsigned long long;

  auto p_max = Max(p, n);
  RadixType max_radix_bit = (1ULL << (sizeof(RadixType) * 8 - 1));
  while (!(max_radix_bit & p_max->data_)) {
    max_radix_bit >>= 1;
  }
  max_radix_bit <<= 1;

  for (RadixType radix_bit = 1;
       radix_bit != max_radix_bit && (p = pre_pos);
       radix_bit <<= 1) {
    for (int i = 0; i < len; ++i) {
      if (radix_bit & static_cast<RadixType>(p->succ_->data_)) {
        MoveBefore(p->succ_, end_pos);
      } else {
        p = p->succ_;
      }
    }
  }
}

template <typename T>
void List<T>::RadixSort() {
  RadixSort(header()->succ_, size_);
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

template <typename T>
void List<T>::Merge(LNP pa, Size n, List<T> &list, LNP pb, Size m) {
  while (0 < m && pa != pb) {  // pa != pb 对 pa, pb 同源优化
    if (0 < n && pa->data_ <= pb->data_) {
      pa = pa->succ_;
      --n;
    } else {
      InsertBefore(pa, pb->data_);
      pb = pb->succ_;
      Remove(pb->pred_);
      --m;
    }
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

}  // namespace ds_cpp

#endif