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

  //Make take string
  void push(char* data) {

    Node* newNode = new Node(data);
    newNode->next = head;
    head = newNode;
  }

  //Make return node
  //Make discard function
  void pop() {

    Node* delNode = head;
    head = head->next;
    delete delNode;
  }

  char* peek() { return head->data; }
};

struct Queue {

  //Make constructor for errors from shunting
  Node* head = nullptr; //New things
  Node* tail = nullptr; //Old things

  //Make overload for popping from stack
  //Make take string
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

  //Make return string
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
