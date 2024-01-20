template<typename T>
bool AVL<T>::Remove(const T &e) {
  BNP &remove_ref = this->Search(e);
  if (!remove_ref) return false;
  this->BST<T>::RemoveAt(remove_ref); --this->size_;
  for (BNP g = this->hot_; g; g = g->parent_) {
    if (!AvlBalanced(g)) {
      BNP v = TallerChild(TallerChild(g));
      BNP &ref = this->FromParentTo(g);
      BNP parent = RotateAt(v);
      ref = parent;
    }
    this->UpdateHeight(g);
  }
  return true;
}