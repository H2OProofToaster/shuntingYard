#ifndef STRUCTS_CPP
#define STRUCTS_CPP

struct Node {

  char* data = nullptr;
  Node* left = nullptr;
  Node* right = nullptr;
  Node* next = nullptr;

  Node(char* d) : data(d) {}
  ~Node() {

    if (next != nullptr) { delete next; }
    delete data;
  }
};

struct Stack {

  Node* head = nullptr;

  ~Stack() { delete head; }

  void push(char* data) {

    Node* newNode = new Node(data);
    newNode->next = head;
    head = newNode;
  }

  void pop() {

    Node* delNode = head;
    head = head->next;
    delete delNode;
  }

  char* peek() { return head->data; }
};

struct Queue {

  Node* head = nullptr; //New things
  Node* tail = nullptr; //Old things

  void enqueue(char* data) {

    //Empty queue
    if (head == nullptr) {

      head = new Node(data);
      tail = head;
    }

    else {

      head->next = new Node(data);
      head = head->next;
    }
  }

  char* dequeue() {

    //Empty queue
    if (tail == nullptr) { return nullptr; }

    //One element
    else if (*tail == *head) {

      Node* temp = tail;
      tail = nullptr;
      head = nullptr;
      return temp;
    }

    else {

      Node* temp = tail->next;
      tail = tail->next;
      temp->next = nullptr;
      return temp;
    }
  }
};
      
      
#endif
