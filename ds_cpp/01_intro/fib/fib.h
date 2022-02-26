#include <stdexcept>

// fib 数列 : >= 0
// 超出 上限 或 下限会抛出异常
class Fib {
public:
  using ST = unsigned long;
	Fib(ST n); // 获取不小于 n 的最小项 Fib 数
	ST get() { return f; };
	ST next();
	ST prev();
private:
	ST f; // 前一个数
	ST g; // 后一个数
};


// 1 二分法 递归版
Fib::ST fib_R1(unsigned long n);
// 2 状态转移方程 递归版 O(n)  额外需要 O(n) 空间
Fib::ST fib_R2(unsigned long n, unsigned long &pre);
