#include <cstdio>
#include <cstdlib>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"

using namespace std;

const int MAX_NUM = 100010;
int info[MAX_NUM][1] = {0};

int main() {
  int n, index, score;
  score = 0;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d %d", &index, &score);
    info[index][0] += score;
  }
  if (n == 1) {
    printf("%d %d", index, score);
    return EXIT_SUCCESS;
  }
  index = 0;
  score = info[0][0];
  for (int i = 0; i < MAX_NUM; ++i) {
    if (info[i][0] > score) {
      score = info[i][0];
      index = i;
    }
  }
  printf("%d %d", index, score);
  return EXIT_SUCCESS;
}
