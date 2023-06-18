#ifndef DS_CPP_BINODE_IMPL_H_
#define DS_CPP_BINODE_IMPL_H_

namespace ds_cpp {

template<typename T>
BiNode<T>::BiNode()
    : data_(), parent_(nullptr), lc_(nullptr), rc_(nullptr), height_(0) {}

template<typename T>
BiNode<T>::BiNode(const T &data, BNP parent, BNP lc, BNP rc, SizeType height)
    : data_(data), parent_(parent), lc_(lc), rc_(rc), height_(height) {}

template<typename T>
typename BiNode<T>::SizeType BiNode<T>::Size() {
  SizeType size = 1;
  if (lc_) size += lc_->Size();
  if (rc_) size += rc_->Size();
  return size;
}

template<typename T>
typename BiNode<T>::BNP BiNode<T>::InsertAsLc(const T &data) {
  return !lc_ ? lc_ = new BiNode<T>(data, this) : nullptr;
}

template<typename T>
typename BiNode<T>::BNP BiNode<T>::InsertAsRc(const T &data) {
  return !rc_ ? rc_ = new BiNode<T>(data, this) : nullptr;
}

}  // namespace ds_cpp

#endif