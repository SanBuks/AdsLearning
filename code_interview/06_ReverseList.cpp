#include <vector>
#include <stack>
using namespace std;
vector<int> printListFromTailToHead(ListNode* head) {
	if(!head) return {};
	std::vector<int> vec;
	std::stack<ListNode*> stk;
	
	while(head){
		stk.push(head);
		head = head->next;
	}
	while(!stk.empty()){
		vec.push_back(stk.top()->val);
		stk.pop();
	}
	return vec;
}
