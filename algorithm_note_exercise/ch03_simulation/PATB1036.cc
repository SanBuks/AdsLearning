#include <cstdlib>
#include <cstdio>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"

using namespace std;

int main() {
  char x;
  int c, r;
  scanf("%d %c", &c, &x);
  r = (c * 10 / 2 % 10 > 4) ? c / 2 + 1 : c / 2;
  for (int i = 0; i < c; ++i) {
    printf("%c", x);
  }

  for (int i = 0; i < r - 2; ++i) {
    printf("\n%c", x);
    for (int j = 0; j < c - 2; ++j) {
      printf(" ");
    }
    printf("%c", x);
  }

  printf("\n");
  for (int i = 0; i < c; ++i) {
    printf("%c", x);
  }
  exit(EXIT_SUCCESS);
}