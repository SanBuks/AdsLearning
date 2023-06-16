#ifndef DS_CPP_BITREE_IMPL_H_
#define DS_CPP_BITREE_IMPL_H_

namespace ds_cpp {


template<typename T>
BiTree<T>::BiTree() : size_(0), root_(nullptr) {}



template<typename T>
void swap(BiTree<T> &lhs, BiTree<T> &rhs) noexcept {
  using std::swap;
  swap(lhs.root_, rhs.root_);
  swap(lhs.size_, rhs.size_);
}

}  // namespace ds_cpp

#endif
