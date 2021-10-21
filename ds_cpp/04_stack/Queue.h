#include "../ch03_List/List.h"
template <typename T>
class Queue: public List<T>{
public:
	using List<T>::insertAsLast;
	using List<T>::remove;
	using List<T>::first;
	using List<T>::empty;

	void enqueue(T const &e){ insertAsLast(e); } 
	T dequeue() { return remove(first()); }
	T &front() { return first()->data; }
};
