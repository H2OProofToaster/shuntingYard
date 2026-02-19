#ifndef STRUCTS_CPP
#define STRUCTS_CPP

template <typename T>
struct Node {

  T* data = nullptr;
  Node* next = nullptr;

  Node(T* d) : data(d) {}
  ~Node() {

    if (next != nullptr) { delete next; }
    delete data;
  }
};

struct Stack {

  Node* head = nullptr;

  ~Stack() { delete head; }

  void push(T* data) {

    Node<T>* newNode = new Node<T>(data);
    newNode->next = head;
    head = newNode;
  }

  void pop() {

    NodeT>* delNode = head;
    head = head->next;
    delete delNode;
  }

  T* peek() { return head->data; }
};

struct Queue {

  Node* head = nullptr;
  Node* tail = nullptr;

  void enqueue(T* data) {

    //Empty queue
    if (head == nullptr) {

      head = new Node<T>(data);
      tail = head;
    }

    //One element
    if (*head == *tail) {

      tail = new Node<T>(data);
      

#endif
