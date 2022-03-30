#include <cstdio>

const int max = 10010;
int array[max] = {0};
int dp[max][3] = {0};

// 0 < K <= 10000
// 每个数的绝对值不超过100
int main() {
  int n, first, last, sum;
  while (scanf("%d", &n) != EOF) {
    if (n == 0) {
      break;
    }

    scanf("%d", &array[0]);
    dp[0][0] = array[0];  // value
    dp[0][1] = 0;  // start index
    dp[0][2] = 0;  // end index

    for (int i = 1; i < n; ++i) {
      scanf("%d", &array[i]);
      if (array[i] >= dp[i - 1][0] + array[i]) {
        dp[i][0] = array[i];
        dp[i][1] = i;
        dp[i][2] = i;
      } else {
        dp[i][0] = dp[i - 1][0] + array[i];
        dp[i][1] = dp[i - 1][1];
        dp[i][2] = i;
      }
    }

    sum = dp[0][0];
    first = dp[0][1];
    last = dp[0][2];
    for (int i = 1; i < n; ++i) {
      if (dp[i][0] > sum) {
        sum = dp[i][0];
        first = dp[i][1];
        last = dp[i][2];
      }
    }
    if (sum < 0) {
      printf("0 %d %d\n", array[0], array[n - 1]);
    } else {
      printf("%d %d %d\n", sum, array[first], array[last]);
    }
  }
  return 0;
}