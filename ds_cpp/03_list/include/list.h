#ifndef DS_CPP_LIST_H
#define DS_CPP_LIST_H

#include "list_node.h"
#include "list_error.h"

namespace ds_cpp {

template <typename T>
class List {
  using typename ListNode<T>::LNP;
  using Rank = unsigned long long;

 protected:

 private:
  LNP header;  // 记录头部哨兵结点的指针
  LNP trailer;  // 记录尾部哨兵节点的指针
  int _size; // 记录总大小
};

//void init() {  // 初始化 首尾哨兵
//  header = new ListNode<T>;
//  trailer = new ListNode<T>;
//  header->pred = nullptr;
//  header->succ = trailer;
//  trailer->pred = header;
//  trailer->succ = nullptr;
//  _size = 0;
//}
//void copyNodes(LNP(T)p, int n) {  // 自p指针所指开始 复制n个节点
//  init();
//  while (n--) {
//    insertAsLast(p->data);  // 尾插法
//    p = p->succ;
//  }
//}
//void movetoFront(LNP(T)p) {
//  if (vaild(p))
//    insertAfter(header, remove(p));
//}
//
//public:
//List() { init(); }
//List(const List<T> &L, rank r, int n) { // 复制自L[r] 起的n项
//  auto p = L.first();
//  while (r--)
//    p = p->succ;
//  copyNodes(p, n);
//}
//~List() {
//  clear();
//  delete trailer;
//  delete header;
//}
//
//T remove(LNP(T)p) {  // 删除p所指的节点
//  T e = p->data;
//  p->succ->pred = p->pred; // 调整前后指针
//  p->pred->succ = p->succ;
//  delete p;
//  --_size; // 减少个数
//  return e;
//}
//int clear() { // 清空节点返回个数
//  int n = _size;
//  while (_size)
//    remove(header->succ);
//  return n;
//}
//
//rank size() const { return _size; }
//bool empty() const { return _size <= 0; }
//bool vaild(LNP(T)p) { return p && (trailer != p) && (header != p); }
//LNP(T)first() const { return header->succ; }
//LNP(T)last() const { return trailer->pred; }
//LNP(T)insertAsFirst(T const &e) {
//++_size;
//return header->insertAsSucc(e);
//}
//LNP(T)insertAsLast(const T &e) {
//  ++_size;
//  return trailer->insertAsPred(e);
//}
//LNP(T)insertBefore(LNP(T)p, const T &e) {
//++_size;
//return p->insertAsPred(e);
//}
//LNP(T)insertAfter(LNP(T)p, const T &e) {
//++_size;
//return p->insertAsSucc(e);
//}
//
//T &operator[](rank r) const { // 自适应访问
//  auto p = header->succ;
//  while (0 < r--) p = p->succ;
//  movetoFront(p);
//  return p->data;
//}
//const T &operator[](rank r) {  // 自适应访问, 对List是否是const 重载
//  auto p = header->succ;
//  while (0 < r--) p = p->succ;
//  movetoFront(p);
//  return p->data;
//}
//
//template <typename VST>
//void traverse(VST &visit) {
//  LNP(T)p = header;
//  while ((p = p->succ) != trailer) {
//    visit(p->data);
//  }
//}
//
//int disorder() const { // 返回紧邻无序对的数量
//  int sum = 0;
//  auto p = header->succ;
//  while ((p = p->succ) != trailer) {
//    if (p->pred->data > p->data)
//      ++sum;
//  }
//  return sum;
//}
//
//LNP(T)selectMax(LNP(T)p, int n) { // 返回 包括p在内的后n个节点中最大值位置
//LNP(T)max = p;
//n--;
//while (n--) {
//p = p->succ;
//if (p->data > max->data)
//max = p;
//}
//return max;
//}
//
//LNP(T)find(const T &e,
//           int n,
//           LNP(T)p) const { // 在 p 的n个真前驱中寻找e的位置 找不到返回nullptr
//  while (n--)
//    if ((p = p->pred)->data == e)
//      return p;
//  return nullptr;
//}
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
//
//int deduplicate() {  // 无序唯一化
//  if (_size < 2) return 0;
//  int oldSize = _size;
//  int pren = 1; // 真前驱个数
//  auto p = first()->succ; // 指向第二个节点
//  while (p != trailer) {
//    auto deletep = find(p->data, pren, p);
//    if (deletep) {
//      remove(deletep);
//      pren--;
//    } else {
//      p = p->succ;
//      pren++;
//    }
//  }
//  return oldSize - _size;
//}
//int uniqufy() {  // 有序唯一化
//  if (_size < 2) return 0;
//
//  int oldSize = _size;
//  LNP(T)p = first(); // p q 分别指向前后相邻节点
//  LNP(T)q = p->succ;
//  for (; q != trailer; p = q, q = q->succ) { // 边历一边list
//    if (q->data == p->data) { // 如果值相同删除q所指节点
//      remove(q);
//      q = p;  // 让p停留一步
//    }
//  }
//
//  return oldSize - _size;
//}
//
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