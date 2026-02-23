#ifndef STRUCTS_CPP
#define STRUCTS_CPP

#include <string>

using namespace std;

struct Node {

  string data = nullptr;
  Node* left = nullptr;
  Node* right = nullptr;
  Node* next = nullptr;

  Node(string d) : data(d) {}
  ~Node() {

    if (next != nullptr) { delete next; }
  }

  bool operator==(Node& other) { return data == other.data; }
};

struct Stack {

  Node* head = nullptr;

  ~Stack() { delete head; }

  void push(string data) { push(new Node(data)); }
  
  void push(Node* newNode) {

    newNode->next = head;
    head = newNode;
  }

  Node* pop() {

    Node* delNode = head;
    head = head->next;
    delNode->next = nullptr;
    return delNode;
  }

  void discard() {

    Node* delNode = head;
    head = head->next;
    delete delNode;
  }

  Node* peek() { return head; }

  bool isEmpty() { return (head == nullptr) ? true : false; }
};

struct Queue {

  //Make constructor for errors from shunting
  Node* head = nullptr; //New things
  Node* tail = nullptr; //Old things

  Queue() {}
  Queue(string in) { enqueue(in); }
  
  void enqueue(string data) { enqueue(new Node(data)); }
  
  void enqueue(Node* data) {

    //Empty queue
    if (head == nullptr) {

      head = data;
      tail = head;
    }

    else {

      head->next = data;
      head = head->next;
    }
  }

  Node* dequeue() {

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

  bool isEmpty() { return (head == nullptr) ? true : false; }
};
            
#endif
