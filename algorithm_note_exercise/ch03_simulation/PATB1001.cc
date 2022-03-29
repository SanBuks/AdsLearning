#include <cstdio>
#include <cstdlib>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"

using namespace std;

int main() {
  long n, steps = 0;
  char *p = new char[10];

  scanf("%s", p);
  n = strtol(p, nullptr, 0);

  while (n != 1) {
    n = n & 1 ? (3 * n + 1) >> 1 : n >> 1;
    ++steps;
  }

  printf("%ld", steps);
  exit(EXIT_SUCCESS);
}