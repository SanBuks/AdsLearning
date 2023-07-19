#include <unordered_map>
using namespace std;
class LRUCache {
 public:
  LRUCache(int capacity) : size_(capacity), L(new Node()), R(new Node()), hash_() {
    L->next_ = R;
    R->prev_ = L;
  }

  ~LRUCache() {
    auto p = L->next_;
    while (p) {
      auto q = p;
      p = p->next_;
      delete q;
    }
    delete L;
  }

  int get(int key) {
    if (hash_.count(key)) {
      auto p = hash_[key];
      p = remove(p);
      insertAfter(L, p);
      return hash_[key]->val_;
    } else {
      return -1;
    }
  }

  void put(int key, int value) {
    if (hash_.count(key)) {
      hash_[key]->val_ = value;
      auto p = remove(hash_[key]);
      insertAfter(L, p);
    } else {
      auto p = new Node(key, value);
      insertAfter(L, p);
      hash_[key] = p;

      if (hash_.size() > size_) {
        hash_.erase(R->prev_->key_);
        delete remove(R->prev_);
      }
    }
  }

 private:
  struct Node {
    int key_, val_;
    Node *prev_;
    Node *next_;
    explicit Node(int key = 0, int val = 0, Node *prev = nullptr, Node *next = nullptr) :
        key_(key), val_(val), prev_(prev), next_(next) {}
  };

  Node *remove(Node *p) {
    auto prev = p->prev_;
    auto next = p->next_;
    prev->next_ = next;
    next->prev_ = prev;
    return p;
  }

  Node *insertAfter(Node *p, Node *target) {
    auto newNext = p->next_;
    p->next_ = target;
    newNext->prev_ = target;
    target->prev_ = p;
    target->next_ = newNext;
    return p;
  }

  int size_;
  Node *L, *R;
  unordered_map<int, Node *> hash_;
};