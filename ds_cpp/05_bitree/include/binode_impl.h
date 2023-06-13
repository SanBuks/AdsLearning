#ifndef DS_CPP_BINODE_IMPL_H_
#define DS_CPP_BINODE_IMPL_H_

namespace ds_cpp {

template <typename T>
BiNode<T>::BiNode(T data, BNP parent , BNP lc, BNP rc, HeightType height)
    : data_(data), parent_(parent), lc_(lc), rc_(rc), height_(height) {}

template <typename T>
T &BiNode<T>::data() {
  return data_;
}

template <typename T>
const T &BiNode<T>::data() const {
  return data_;
}

template <typename T>
typename BiNode<T>::BNP BiNode<T>::parent() {
  return parent_;
}

template <typename T>
typename BiNode<T>::CBNP BiNode<T>::parent() const {
  return parent_;
}

template <typename T>
typename BiNode<T>::BNP BiNode<T>::lc() {
  return lc_;
}

template <typename T>
typename BiNode<T>::CBNP BiNode<T>::lc() const {
  return lc_;
}

template <typename T>
typename BiNode<T>::BNP BiNode<T>::rc() {
  return rc_;
}

template <typename T>
typename BiNode<T>::CBNP BiNode<T>::rc() const {
  return rc_;
}

template <typename T>
typename BiNode<T>::HeightType BiNode<T>::height() const {
  return height_;
}

template <typename T>
typename BiNode<T>::BNP BiNode<T>::InsertAsLc(const T &data) {
  if (!lc_) {
    return lc_ = new BiNode<T>(data, this);
  } else {
    return nullptr;
  }
}

template <typename T>
typename BiNode<T>::BNP BiNode<T>::InsertAsRc(const T &data) {
  if (!rc_) {
    return rc_ = new BiNode<T>(data, this);
  } else {
    return nullptr;
  }
}

}  // namespace ds_cpp

#endif