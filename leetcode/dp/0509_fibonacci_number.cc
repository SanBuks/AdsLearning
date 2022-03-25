int NON;
class Solution {
 public:
  static int Fib(int n, int &pre) {
    if (!n) {
      pre = 1;
      return 0;
    } else {
      int prepre;
      pre = Fib(n - 1, prepre);
      return pre + prepre;
    }
  }
  int fib(int n) {
    return Fib(n, NON);
  }
};
