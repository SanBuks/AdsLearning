#include "gtest/gtest.h"
#include "avl.h"

TEST(AVL_TEST, REMOVE_RR) {
using namespace std;
using namespace ds_cpp;

vector<int> vec{       16,
                       10,     25,
                       -1,  11, -1, 27,
                       -1, -1, -1, -1};


AVL<int> avl(vec, -1);
avl.Remove(11);
avl.Remove(10);
std::ostringstream oss;
BiTreeTraverse<int> traverse(oss);
avl.TraverseLevel(traverse);
std::cout << oss.str() << "\n"; oss.clear(); oss.str("");
}

TEST(AVL_TEST, REMOVE_RL) {
using namespace std;
using namespace ds_cpp;

vector<int> vec{       16,
                       10,     25,
                       -1,  11, -1, 27,
                       -1, -1, -1, -1};


AVL<int> avl(vec, -1);
avl.Remove(11);
avl.Remove(10);
std::ostringstream oss;
BiTreeTraverse<int> traverse(oss);
avl.TraverseLevel(traverse);
std::cout << oss.str() << "\n"; oss.clear(); oss.str("");
}
