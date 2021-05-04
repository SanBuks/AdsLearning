#include <vector>
#include <iostream>
#include <utility>

using namespace std;
void reverse(vector<int> &vec, unsigned long low, unsigned long high) {
  while (low < high) {
    std::swap(vec[low], vec[high - 1]);
    ++low;
    --high;
  }
}

void shift(vector<int> &vec, unsigned long n) {
  if (vec.empty() || vec.size() == 1) 
    return;
  n = n % vec.size();
  reverse(vec, 0, n);
  reverse(vec, n, vec.size());
  reverse(vec, 0, vec.size());
}

int main() {
  vector<int> vec{1};
  shift(vec, 2);
  for(const auto &it : vec) {
    std::cout << it << " ";
  }
  return 0;
}