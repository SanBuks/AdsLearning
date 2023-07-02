#include "gtest/gtest.h"
#include "bst.h"

TEST(BST_TEST, INSERT) {
  using namespace std;
  using namespace ds_cpp;

  vector<int> vec{       16,
                     10,     25,
                  -1,  11, -1, 26,
                     -1, -1, -1, -1};

  BST<int> bst(vec, -1);
  bst.Add(9);
  BiTreeTraverse<int> traverse(std::cout);
  bst.TraverseLevel(traverse);
  cout << "\n";
  bst.TraverseInIteration(traverse);
  cout << "\n";
  bst.TraversePreIteration(traverse);
}


TEST(BST_TEST, ADD_TO_TREE) {
  using namespace std;
  using namespace ds_cpp;

  BST<int> bst;
  bst.Add(16);
  bst.Add(10);
  bst.Add(25);
  bst.Add(11);
  bst.Add(26);

  BiTreeTraverse<int> traverse(std::cout);
  bst.TraverseLevel(traverse);
  cout << "\n";
  bst.TraverseInIteration(traverse);
}