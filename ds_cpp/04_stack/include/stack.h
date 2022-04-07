#ifndef DS_CPP_STACK_H
#define DS_CPP_STACK_H

#include "vector.h"

namespace ds_cpp {

struct stack_error {
  static constexpr const char *kPopOnEmpty
      = "[ds_cpp:stack]: pop on empty stack";
  static constexpr const char *kVisitOnEmpty
      = "[ds_cpp:stack]: visit on empty stack";
};

template <typename T, typename B = Vector<T>>
class Stack : protected B {  // 不暴露过多接口给用户
 public:
  using B::Empty;

  // 压栈
  void Push(T const &e);
  // 出栈
  T Pop();

  // 返回栈顶元素
  T &Top();
  const T &Top() const ;
};

template <typename T, typename B>
void Stack<T, B>::Push(T const &e){
  this->Insert(this->size(), e);
}

template <typename T, typename B>
T Stack<T, B>::Pop() {
  if (this->Empty()) {
    throw std::runtime_error(stack_error::kPopOnEmpty);
  }
  return this->Remove(this->size() - 1);
}

template <typename T, typename B>
T &Stack<T, B>::Top() {
  if (this->Empty()) {
    throw std::runtime_error(stack_error::kVisitOnEmpty);
  }
  return (*this)[this->size() - 1];
}

template <typename T, typename B>
const T &Stack<T, B>::Top() const {
  if (this->Empty()) {
    throw std::runtime_error(stack_error::kVisitOnEmpty);
  }
  return (*this)[this->size() - 1];
}

}  // namespace ds_cpp

#endif