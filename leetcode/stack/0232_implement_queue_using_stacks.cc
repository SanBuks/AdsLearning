#include <stack>

using namespace std;

class MyQueue {
 public:
  MyQueue() = default;

  void push(int x) {
    ins.push(x);
  }

  int pop() {
    if (ous.empty()) {
      while (!ins.empty()) {
        ous.push(ins.top());
        ins.pop();
      }
    }
    int temp = ous.top();
    ous.pop();
    return temp;
  }

  int peek() {
    if (ous.empty()) {
      while (!ins.empty()) {
        ous.push(ins.top());
        ins.pop();
      }
    }
    return ous.top();
  }

  bool empty() {
    return ins.empty() && ous.empty();
  }
 private:
   stack<int> ins;
   stack<int> ous;
};