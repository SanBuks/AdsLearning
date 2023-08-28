#ifndef DS_CPP_AVL_IMPL_H_
#define DS_CPP_AVL_IMPL_H_

namespace ds_cpp {

template <typename T>
AVL<T>::AVL() : BST<T>(){ }

template<typename T>
AVL<T>::AVL(const std::vector<T> &vec, const T &end) : BST<T>(vec, end) {}

template<typename T>
typename AVL<T>::BNP AVL<T>::Add(const T &e) {
  return nullptr;

}

template<typename T>
bool AVL<T>::Remove(const T &e) {
  return true;
}

}

#endif
