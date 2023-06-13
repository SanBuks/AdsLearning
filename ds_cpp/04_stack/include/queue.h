#ifndef DS_CPP_QUEUE_H
#define DS_CPP_QUEUE_H

#include "list.h"

namespace ds_cpp {

struct queue_error {
  static constexpr const char *kPopOnEmpty
      = "[ds_cpp:queue]: pop on empty queue";
  static constexpr const char *kVisitOnEmpty
      = "[ds_cpp:queue]: visit on empty queue";
};

template <typename T, typename B = List<T>>
class Queue : protected B {  // 不暴露过多接口给用户
 public:
  using B::Empty;

  // 进队列
  void Enqueue(T const &e);
  // 出队列
  T Dequeue();

  // 返回队列第一个元素
  T &Front();
  const T &Front() const;
};

template <typename T, typename B>
void Queue<T, B>::Enqueue(T const &e) {
  this->InsertAsLast(e);
}

template <typename T, typename B>
T Queue<T, B>::Dequeue() {
  if (this->Empty()) {
    throw std::runtime_error(queue_error::kPopOnEmpty);
  }
  return this->Remove(this->header()->succ());
}

template <typename T, typename B>
T &Queue<T, B>::Front() {
  if (this->Empty()) {
    throw std::runtime_error(queue_error::kVisitOnEmpty);
  }
  return this->header()->succ()->data();
}

template <typename T, typename B>
const T &Queue<T, B>::Front() const {
  if (this->Empty()) {
    throw std::runtime_error(queue_error::kVisitOnEmpty);
  }
  return this->header()->succ()->data();
}

}  // namespace ds_cpp

#endif