#include <cstdio>
#include <cstdlib>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"

using namespace std;
char saying[80][80];

int main() {
  int index = 0;
  while (scanf("%s", saying[index]) != EOF) {
    ++index;
  }
  for (int i = index - 1; i >= 0; --i) {
    printf("%s", saying[i]);
    if (i != 0) {
      printf(" ");
    }
  }
  exit(EXIT_SUCCESS);
}
