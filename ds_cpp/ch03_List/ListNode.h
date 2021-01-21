typedef int rank;
# define LNP(T) ListNode<T>*

template <typename T> class List;
template<typename T>
class ListNode{
	friend class List<T>;
private:
	T data;  // 存取数据
	LNP(T) pred;  // 前驱指针
	LNP(T) succ;  // 后继指针
	
public:
	ListNode(){}
	ListNode(T e, LNP(T) p=nullptr, LNP(T) s=nullptr):
		data(e), pred(p), succ(s){}
	
	LNP(T) insertAsPred(const T &e){  // 前方插入
		LNP(T) p=new ListNode(e, pred, this);
		pred->succ=p;
		pred=p;
		return p;
	}
	LNP(T) insertAsSucc(const T &e){  // 后方插入
		LNP(T) p=new ListNode(e, this, succ);
		succ->pred=p;
		succ=p;
		return p;
	}
};

