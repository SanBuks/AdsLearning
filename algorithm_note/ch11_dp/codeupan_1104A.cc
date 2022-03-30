#include <cstdio>
#include <cstring>

const int max = 110;
char str_a[max] = {};
char str_b[max] = {};
int dp[max][max] = {0};

// 每个字符串的长度不超过100
// abcfbc abfcab

int main() {
  int n, len_a, len_b;
  while (scanf("%s %s", str_a, str_b) != EOF) {
    n = 0;
    len_a = strlen(str_a);
    len_b = strlen(str_b);

    dp[0][0] = str_a[0] == str_b[0] ? 1 : 0;
    for (int i = 1; i < len_a; ++i) {
      if (str_a[i] == str_b[0]) {
        dp[0][i] = 1;
      } else {
        dp[0][i] = dp[0][i - 1];
      }
    }
    for (int i = 1; i < len_b; ++i) {
      if (str_b[i] == str_a[0]) {
        dp[i][0] = 1;
      } else {
        dp[i][0] = dp[i - 1][0];
      }
    }


    for (int i = 1; i < len_a; ++i) {
      for (int j = 1; j < len_b; ++j) {
        if (str_a[i] == str_b[j]) {
          if (i - 1 >= )

        } else {

        }
      }
    }
    printf("%d\n", dp[len_a - 1][len_b - 1]);
  }
  return 0;
}