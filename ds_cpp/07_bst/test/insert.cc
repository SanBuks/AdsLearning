#include "gtest/gtest.h"
#include "bst.h"


TEST(BST_TEST, SEARCH) {
  using namespace std;
  using namespace ds_cpp;

  vector<int> vec{16,
                  10, 25,
                  5, 11, 19, 28,
                  2, 8, -1, 15, 17, 22, 27, 37,
                  -1, 4, -1, -1, 13, -1, -1, -1, -1, -1, -1, -1, 33, -1};
  BST<int> bst(vec, -1);

  bst.Add();

}

