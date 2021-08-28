#include <stdexcept>
#include <iostream>

template <typename T>
struct ListNode{
	T data;
	ListNode<T> *next;
	ListNode(T d): data(d), next(nullptr){}
};

template <typename T>
struct List{
	ListNode<T> *head;
	List(): head(nullptr){}
	~List(){ 
		auto p=head;
		while(head){ 
			p=head;
			head=p->next;
			delete p;
		}
	}

	ListNode<T> *insertAsFirst(T d){
		if(!head) return head=new ListNode<T>(d);
		auto p=head;
		head=new ListNode<T>(d);
		head->next=p;
		return head;
	}

	template <typename VST>
	void traverse(VST &visit){
		auto p=head;
		while(p) { visit(p->data); p=p->next; }
	}
};

// k 超出长度
// k = 0
// 空指针
template <typename T>
ListNode<T> *FindKthToTail(ListNode<T> *phead, unsigned k){
	if(!phead||!k) return nullptr;

	unsigned length=1;
	auto firstp=phead, secondp=phead;
	while((firstp=firstp->next)) ++length; 
	if(length<k) throw std::runtime_error("FindKthToTail() : k is bigger than length ! \n");

	firstp=phead;
	for(unsigned i=0; i<k-1; ++i) firstp=firstp->next;

	while(firstp->next) {
		firstp=firstp->next; 
		secondp=secondp->next;
	}
	return secondp;
}

template <typename T>
struct Visit{
	void operator()(const T &e) const {
		std::cout<<e<<" ";
	}
};

Visit<char> visit;

int main(){
	List<char> lst;
	lst.insertAsFirst('5');
	lst.insertAsFirst('4');
	lst.insertAsFirst('3');
	lst.insertAsFirst('2');
	lst.insertAsFirst('1');
	lst.traverse<Visit<char>>(visit);
	std::cout<<std::endl;
	auto p=FindKthToTail(lst.head, 6);
	if(p) std::cout<<p->data;
	// FindKthToTail(p, 1);
	// FindKthToTail(p, 100);
	return 0;
}

