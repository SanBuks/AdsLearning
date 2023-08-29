#ifndef DS_CPP_AVL_IMPL_H_
#define DS_CPP_AVL_IMPL_H_

namespace ds_cpp {

template <typename T>
AVL<T>::AVL() : BST<T>() {}

template<typename T>
AVL<T>::AVL(const std::vector<T> &vec, const T &end) : BST<T>(vec, end) {}

template<typename T>
typename AVL<T>::BNP AVL<T>::Add(const T &e) {
  // 查找插入位置, 如果节点存在则直接返回
  auto & insert_ref = this->Search(e);
  if (insert_ref) return insert_ref;

  // 创建节点
  insert_ref = new BiNode<T>(e, this->hot_); ++this->size_;
  BNP pos = insert_ref;

  for (BNP g = insert_ref; g; g = g->parent()) {
    if (!AvlBalanced(g)){

      break;
    } else {

    }
  }
  return pos;
}

template<typename T>
bool AVL<T>::Remove(const T &e) {
  return true;
}

}

#endif
