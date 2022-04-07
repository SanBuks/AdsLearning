#include <queue>

using namespace std;

class MyStack {
 public:
  explicit MyStack() = default;

  void push(int x) {
    out_queue.push(x);
  }

  int pop() {
    if (out_queue.empty()) {
      std::swap(out_queue, in_queue);
    }

    int temp = out_queue.front();
    out_queue.pop();

    while (!out_queue.empty()) {
      in_queue.push(temp);
      temp = out_queue.front();
      out_queue.pop();
    }
    return temp;
  }

  int top() {
    if (out_queue.empty()) {
      std::swap(out_queue, in_queue);
    }

    int temp = out_queue.front();
    out_queue.pop();

    while (!out_queue.empty()) {
      in_queue.push(temp);
      temp = out_queue.front();
      out_queue.pop();
    }
    out_queue.push(temp);
    return temp;
  }

  bool empty() {
    return out_queue.empty() && in_queue.empty();
  }

 private:
  queue<int> out_queue;
  queue<int> in_queue;
};