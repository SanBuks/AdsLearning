#include <cstdio>
#include <cstdlib>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"

using namespace std;

char ch[33] = {"\0"};

int main() {
  int a, b, d;
  scanf("%d %d %d", &a, &b, &d);
  a += b;
  int index = 0;

  do {
    ch[index++] = '0' + a % d;
    a /= d;
  } while(a);

  for (int i = index - 1; i >= 0; --i) {
    printf("%c", ch[i]);
  }

  exit(EXIT_SUCCESS);
}