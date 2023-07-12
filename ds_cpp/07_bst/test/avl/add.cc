#include "gtest/gtest.h"
#include "avl.h"

TEST(AVL_TEST, INSERT) {
  using namespace std;
  using namespace ds_cpp;

  vector<int> vec{       16,
                     10,     25,
                  -1,  11, -1, 26,
                     -1, -1, -1, -1};

  AVL<int> avl(vec, -1);
  avl.Add(9);
  BiTreeTraverse<int> traverse(std::cout);
  avl.TraverseLevel(traverse);
  cout << "\n";
  avl.TraverseInIteration(traverse);
  cout << "\n";
  avl.TraversePreIteration(traverse);
}


//TEST(AVL_TEST, ADD_TO_TREE) {
//  using namespace std;
//  using namespace ds_cpp;
//
//  AVL<int> bst;
//  bst.Add(16);
//  bst.Add(10);
//  bst.Add(25);
//  bst.Add(11);
//  bst.Add(26);
//
//  BiTreeTraverse<int> traverse(std::cout);
//  bst.TraverseLevel(traverse);
//  cout << "\n";
//  bst.TraverseInIteration(traverse);
//}