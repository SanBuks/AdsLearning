#include <cstdio>

const int max = 1010;
int array[max] = {0};
int dp[max] = {0};

//输入包含两行，第一行只有一个整数N（1 <= N <= 1000），表示数列的长度。
//第二行有N个自然数ai，0 <= ai <= 10000，两个数之间用空格隔开。

int main() {
  int n, len = 1;
  scanf("%d", &n);

  scanf("%d", &array[0]);
  dp[0] = 1;

  for (int i = 1; i < n; ++i) {
    scanf("%d", &array[i]);
    dp[i] = 1;
    for (int j = 0; j < i; ++j) {
      if (array[j] < array[i] && 1 + dp[j] > dp[i]) {
        dp[i] = 1 + dp[j];
      }
    }
    if (dp[i] > len) {
      len = dp[i];
    }
  }
  printf("%d", len);
  return 0;
}