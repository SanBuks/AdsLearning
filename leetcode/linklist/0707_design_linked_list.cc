#include <memory>

class MyLinkedList {
 public:

  struct ListNode {
    ListNode(int val, ListNode *next) : val_(val), next_(next) {}
    ListNode() : ListNode(0, nullptr) {}
    explicit ListNode(int v) : ListNode(v, nullptr) {}

    int val_;
    ListNode *next_;
  };

  // MyLinkedList()
  // Initializes the MyLinkedList object.
  MyLinkedList() : size_(0), p_elem_(nullptr) {}

  ~MyLinkedList() {
    while (size_) {
      deleteAtIndex(0);
    }
  }

  // int get(int index)
  // Get the value of the indexth node in the linked list. If the index is invalid, return -1.
  int get(int index) {
    if (index >= size_ || index < 0) {
      return -1;
    }
    auto p = p_elem_;
    while (index) {
      p = p->next_;
      --index;
    }
    return p->val_;
  }

  // void addAtHead(int val)
  // Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list.
  void addAtHead(int val) {
    auto *p = new ListNode(val, p_elem_);
    p_elem_ = p;
    ++size_;
  }

  // void addAtTail(int val)
  // Append a node of value val as the last element of the linked list.
  void addAtTail(int val) {
    auto *p = new ListNode(val, nullptr);
    if (!size_) {
      p_elem_ = p;
      size_ = 1;
      return ;
    }

    auto pos = p_elem_;
    while(pos->next_) {
      pos = pos->next_;
    }
    pos->next_ = p;
    ++size_;
  }

  // void addAtIndex(int index, int val)
  // Add a node of value val before the indexth node in the linked list.
  // If index equals the length of the linked list, the node will be appended to the end of the linked list.
  // If index is greater than the length, the node will not be inserted.
  void addAtIndex(int index, int val) {
    if (index < 0 || index > size_) {
      return;
    }
    if (index == 0) {
      return addAtHead(val);
    }
    if (index == size_) {
      return addAtTail(val);
    }

    auto pos = p_elem_;
    --index;
    while (index) {
      pos = pos->next_;
      --index;
    }
    auto *p = new ListNode(val, pos->next_);
    pos->next_ = p;
    ++size_;
  }

  // void deleteAtIndex(int index)
  // Delete the indexth node in the linked list, if the index is valid.
  void deleteAtIndex(int index) {
    if (index < 0 || index >= size_) {
      return;
    }

    if (index == 0) {
      auto temp = p_elem_;
      p_elem_ = p_elem_->next_;
      delete temp;
      --size_;
      return;
    }

    auto pos = p_elem_;
    --index;
    while (index) {
      pos = pos->next_;
      --index;
    }
    auto temp = pos->next_;
    pos->next_ = temp->next_;
    delete temp;
    --size_;
  }

 private:
  int size_;
  ListNode *p_elem_;
};

int main() {
  MyLinkedList list;
  list.addAtHead(1);
  list.addAtTail(3);
  list.addAtIndex(1, 2);
  list.get(1);
  list.deleteAtIndex(1);
  list.get(1);
  return 0;
}