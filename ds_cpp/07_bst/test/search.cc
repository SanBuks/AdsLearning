#include "gtest/gtest.h"
#include "bst.h"

TEST(BST_TEST, SEARCH_EMPTY) {
  using namespace std;
  using namespace ds_cpp;

  vector<int> vec{};

  BST<int> bst(vec, -1);
  bst.Add(9);
  BiTreeTraverse<int> traverse(std::cout);
  bst.TraverseLevel(traverse);
  cout << "\n";
  bst.TraverseInIteration(traverse);
  cout << "\n";
  bst.TraversePreIteration(traverse);
}

TEST(BST_TEST, SEARCH_ROOT) {
  using namespace std;
  using namespace ds_cpp;

  vector<int> vec{1, -1, -1};

  BST<int> bst(vec, -1);
  bst.Add(9);
  BiTreeTraverse<int> traverse(std::cout);
  bst.TraverseLevel(traverse);
  cout << "\n";
  bst.TraverseInIteration(traverse);
  cout << "\n";
  bst.TraversePreIteration(traverse);
}



TEST(BST_TEST, SEARCH) {
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

