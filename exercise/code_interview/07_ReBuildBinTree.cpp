#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


TreeNode* reConstructBinaryTree(vector<int> pre,vector<int> vin) {
	if(pre.empty() || vin.empty()) return nullptr;
	TreeNode  *root = buildRoot(pre, vin, 0u, pre.size(), 0u, vin.size());
	return root;
}

TreeNode* buildRoot(vector<int> &pre, vector<int> &vin,
		unsigned b1, unsigned e1, unsigned b2, unsigned e2){
	// pre : [b1, e1)  vin : [b2, e2)
	if(b1 == e1) return nullptr;	

	int rootValue = pre[b1];
	TreeNode *root = new TreeNode(rootValue); 

	unsigned mid;
	for(unsigned i = b2; i < e2; ++i)
		if(vin[i] == rootValue){
			mid = i;
			break;
		}

	unsigned numLeft = mid - b2;	
	root->left  = buildRoot(pre, vin, b1 + 1, 			b1 + 1 + numLeft, 	b2, 	mid);
	root->right = buildRoot(pre, vin, b1 + 1 + numLeft, e1, 				mid+1, 	e2);
	return root;
}

int main(){
	vector<int> pre{1,2,3,4,5,6,7};
	vector<int> vin{3,2,4,1,6,5,7};

	auto p = reConstructBinaryTree(pre, vin);

	return 0;
}
