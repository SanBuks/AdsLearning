#ifndef DS_CPP_LIST_NODE_H
#define DS_CPP_LIST_NODE_H

namespace ds_cpp {

template <typename T> class List;

template <typename T>
class ListNode {

  friend class List<T>;

 public:
  // 节点指针 模板别名
  using LNP = ListNode *;

  explicit ListNode(T data = T(), LNP pred = nullptr, LNP succ = nullptr);

  // 获取数据
  T &data();
  const T &data() const;

  LNP pred() const;
  LNP succ() const;

 private:
  // 前方插入
  LNP InsertAsPred(const T &data);
  // 后方插入
  LNP InsertAsSucc(const T &data);

  T data_;    // 数据
  LNP pred_;  // 前驱指针
  LNP succ_;  // 后继指针
};


template<typename T>
ListNode<T>:: ListNode(T data, LNP pred, LNP succ) :
    data_(data), pred_(pred), succ_(succ) {}

template<typename T>
typename ListNode<T>::LNP ListNode<T>::InsertAsPred(const T &data) {
  LNP p = new ListNode(data, pred_, this);
  pred_->succ_ = p;
  pred_ = p;
  return p;
}

template<typename T>
typename ListNode<T>::LNP ListNode<T>::InsertAsSucc(const T &data) {
  LNP p = new ListNode(data, this, succ_);
  succ_->pred_ = p;
  succ_ = p;
  return p;
}

template<typename T>
T &ListNode<T>::data() {
  return data_;
}

template<typename T>
const T &ListNode<T>::data() const {
  return data_;
}

template<typename T>
typename ListNode<T>::LNP ListNode<T>::pred() const {
  return pred_;
}

template<typename T>
typename ListNode<T>::LNP ListNode<T>::succ() const {
  return succ_;
}

}  // namespace ds_cpp

#endif