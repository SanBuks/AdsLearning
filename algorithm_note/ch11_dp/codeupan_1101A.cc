#include <cstdio>

/**
 * 分治策略: 子问题没有重叠
 * 动态规划: 子问题重叠, 且存在最优子结构(问题的最优可以由子问题最优推出)
 *          自上而下: 递归
 *          自下而上: 迭代
 * 贪心策略: 子问题存在最优子结构, 但是每步的贪心一定是整体的最优步骤
 */
const int max = 31;
int fib[max] = {0, 1, 1};

int main() {
  int n;
  for (int i = 3; i < max; ++i) {
    fib[i] = fib[i - 1] + fib[i - 2];
  }
  while (scanf("%d", &n) != EOF) {
    printf("%d\n", fib[n]);
  }
  return 0;
}