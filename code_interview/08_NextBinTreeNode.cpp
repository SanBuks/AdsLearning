TreeLinkNode* GetNext(TreeLinkNode* pNode) {
	// 1. has right child : 
	if(pNode->right){
		pNode = pNode->right;
		while(pNode->left)
			pNode = pNode->left;
		return pNode;
	}else{ 
	// 2. has no right child : 
        // single node : 
		if(!pNode->next) return nullptr;
		return flyAlongRight(pNode);
	}
}


TreeLinkNode *flyAlongRight(TreeLinkNode *pNode){
	while(pNode->next &&  pNode->next->right == pNode)
		pNode = pNode->next;
	return pNode->next;
}
