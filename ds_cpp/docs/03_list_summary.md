## 设计注意
- 列表比数组更注重于动态性, 插入与删除等操作的时间复杂度均为 O(1), 但是寻秩访问操作需要扫描迭代时间复杂度为 O(n)
- 为了弥补这种性能损失, 以首尾节点, 前后指针来加快相邻元素之间的访问, 虽然会在一定程度上占据类的存储空间
- ListNode 类的指针在一定程度上充当了迭代器的作用, 因此需要暴露一些访问成员接口, ListNode 的构造函数一定程度简化了插入步骤 

## 参数范围的处理
- 对于 [p, p + n) 参数范围的限制: 
```c++
// 由于尾哨兵的存在, 可以放宽对 n 的限制, n 可以远远大于实际元素个数
template <typename T>
typename List<T>::LNP List<T>::Max(LNP p, Size n) const {
  // p 一定为非空指针, 其次一定不是首尾哨兵, 最后 n != 0
  if (!n || !CheckVisitPosition(p)) {
    return nullptr;
  }

  // 这里 n 和 trailer 都是限制条件
  LNP max_p = p;
  for (--n, p = p->succ_; n && p!= trailer(); p = p->succ_, --n) {
    if (p->data_ > max_p->data_) {
      max_p = p;
    }
  }
  return max_p;
}
```

- 对于 (p , p + n] 参数范围限制: 
```c++
// 由于尾哨兵的存在, 可以放宽对 n 的限制, n 可以远远大于实际元素个数
template <typename T>
typename List<T>::LNP List<T>::FindAfter(T const &elem, LNP p, Size n) const {
  if (!p) {  // p 是 header 是有效的, n = 0 或者 trailer 可以规约在下面循环中
    return nullptr;
  }

  // 实际效果
  // p 4 3 2 1 0/trailer/nullptr 
  // a b c d e        x
  
  for (p = p->succ_; n && p && p->data_ != elem; --n, p = p->succ_);
  // 只用判断唯一合格的状态即可, 其他都是 nullptr
  return n && p && p != trailer() ? p : nullptr;
}

template <typename T>
typename List<T>::LNP List<T>::SearchAfter(T const &elem, LNP p, Size n) const {
  if (!p) {
    throw std::runtime_error(list_error::kNullptrError);
  }
  
  // 与上个函数类似, nullptr 可看作是尾节点
  for (p = p->succ_; n && p && p->data_ < elem; --n, p = p->succ_);
  // 返回 目标插入位置的前驱方便统一调用
  return p ? p->pred_ : trailer()->pred_;  
}
```