#include "gtest/gtest.h"
#include "bst.h"

TEST(BST_TEST, REMOVE_NODE_NONE) {
  using namespace std;
  using namespace ds_cpp;

  vector<int> vec{       16,
                      10,     25,
                   -1,  11, -1,  26,
                      -1, -1,  -1, -1};

  BST<int> bst(vec, -1);
  BiTreeTraverse<int> traverse(std::cout);

  if (bst.Remove(11)) {
    bst.TraverseLevel(traverse);
    cout << "\n";
    bst.TraverseInIteration(traverse);
  } else {
    FAIL();
  }
}

TEST(BST_TEST, REMOVE_NODE_ONE) {
  using namespace std;
  using namespace ds_cpp;

  vector<int> vec{       16,
                     10,     25,
                  -1,  11, -1,  26,
                     -1, -1,  -1, -1};

  BST<int> bst(vec, -1);
  BiTreeTraverse<int> traverse(std::cout);

  if (bst.Remove(10)) {
    ASSERT_EQ(4, bst.size());
    ASSERT_EQ(2, bst.root()->height());

    bst.TraverseLevel(traverse);
    cout << "\n";
    bst.TraverseInIteration(traverse);
  } else {
    FAIL();
  }
}

TEST(BST_TEST, REMOVE_NODE_TWO) {
  using namespace std;
  using namespace ds_cpp;

  vector<int> vec{       16,
                    10,     25,
                 -1,  11, -1,  26,
                    -1, -1,  -1, -1};
  BST<int> bst(vec, -1);
  BiTreeTraverse<int> traverse(std::cout);

  if (bst.Remove(16)) {
    ASSERT_EQ(4, bst.size());
    ASSERT_EQ(2, bst.root()->height());

    bst.TraverseLevel(traverse);
    cout << "\n";
    bst.TraverseInIteration(traverse);
  } else {
    FAIL();
  }
}
