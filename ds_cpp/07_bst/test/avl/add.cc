#include "gtest/gtest.h"
#include "avl.h"

TEST(AVL_TEST, INSERT_RR) {
  using namespace std;
  using namespace ds_cpp;

  vector<int> vec{       16,
                     10,     25,
                  -1,  11, -1, 27,
                     -1, -1, -1, -1};

  AVL<int> avl(vec, -1);
  avl.Add(27);
  std::ostringstream oss;
  BiTreeTraverse<int> traverse(oss);
  avl.TraverseLevel(traverse);
  std::cout << oss.str() << "\n"; oss.clear(); oss.str("");
}

TEST(AVL_TEST, INSERT_RL) {
  using namespace std;
  using namespace ds_cpp;

  vector<int> vec{       16,
                         10,     25,
                         -1,  11, -1, 27,
                         -1, -1, -1, -1};


  AVL<int> avl(vec, -1);
  avl.Add(27);
  std::ostringstream oss;
  BiTreeTraverse<int> traverse(oss);
  avl.TraverseLevel(traverse);
  std::cout << oss.str() << "\n"; oss.clear(); oss.str("");
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