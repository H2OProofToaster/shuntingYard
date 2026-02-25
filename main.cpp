#include <iostream>
#include <string>
#include <sstream>

#include "structs.cpp"

using namespace std;

Queue* shuntingYard(string input);
Node* makeExpressionTree(Queue* input);

string getInfix(Node* input);
string getPostfix(Node* input);
string getPrefix(Node* input);

bool isEqual(string o1, string o2);
int getPrecedence(string o1);

int main() {

  //Ask for input
  string input;
  cout << "What is the input (infix)? ";
  getline(cin, input);

  //Do shunting yard algorithm
  cout << "Shunting..." << endl;

  Queue* shuntingOut = shuntingYard(input);
  
  cout << "Done" << endl;

  //Catch mismatched parenthesis
  if (shuntingOut->head->data == "Mismatched Parenthesis") { cout << "Mismatched Parenthesis"; return 1; }

  //Make binary expression tree
  cout << "Making tree..." << endl;

  Node* tree = makeExpressionTree(shuntingOut);

  //Cleanup
  delete shuntingOut;

  cout << "Done" << endl;

  //Ask for output
  string outputType;
  while (outputType.empty()) {
    cout << "INFIX, POSTFIX, PREFIX, or QUIT? ";
    cin >> outputType;

    if (outputType == "INFIX" or outputType == "in") { cout << getInfix(tree) << endl; }
    else if (outputType == "POSTFIX" or outputType == "post") { cout << getPostfix(tree) << endl; }
    else if (outputType == "PREFIX" or outputType == "pre") { cout << getPrefix(tree) << endl; }
    else if (outputType == "QUIT" or outputType == "q") { cout << "Quitting..." << endl; break; }
    else { cout << "Not an option" << endl; }

    outputType.clear();
  }
    
  return 0;
}

Queue* shuntingYard(string input) {

  //Setup input stream, output queue, and operator stack
  stringstream ss(input);
  string word;
  Queue* output = new Queue();
  Stack* operatorStack = new Stack();
  
  while (ss >> word) {

    //Number, add to queue
    if (word == "0" or word == "1" or word == "2" or word == "3" or word == "4" or word == "5" or word == "6" or word == "7" or word == "8" or word == "9") { output->enqueue(word); }

    else if (word == "+" or word == "-" or word  == "*" or word == "/" or word == "^") {

      while (
              ( operatorStack->peek() == nullptr ? false : operatorStack->peek()->data != "(" ) //o2 at the top of the stack is not a left parenthesis
              and
              (
                operatorStack->peek() == nullptr ? false : getPrecedence(operatorStack->peek()->data) > getPrecedence(word) //o2 has greater precedence than o1
                or
                (
                  operatorStack->peek() == nullptr ? false : getPrecedence(operatorStack->peek()->data) == getPrecedence(word) //o1 and o2 have the same precedence
                  and
                  (word == "+" or word == "-" or word == "*" or word == "/") //o1 is left associative (not "^")
                )
              )
            )
      { output->enqueue(operatorStack->pop()); } //add top operator to queue
      operatorStack->push(word); //curren token to stack
    }

    else if (word == "(") { operatorStack->push(word); }

    else if (word == ")") {

      while (operatorStack->peek()->data != "(") { //o2 is not a left parenthesis

	      if (operatorStack->isEmpty()) { output->enqueue("Mismatched Parenthesis"); delete operatorStack; return output; } //stack is not empty
	      output->enqueue(operatorStack->pop());
      }

      if (operatorStack->peek()->data != "(") { output->enqueue("Mismatched Parenthesis"); delete operatorStack; return output; } //there is not a left parenthesis at the top of the stack

      operatorStack->discard();
    }
  }

  while (!operatorStack->isEmpty()) { //operators in stack

    if (operatorStack->peek()->data == "(" or operatorStack->peek()->data == ")") { output->enqueue("Mismatched Parenthesis"); delete operatorStack; return output; } //o2 is not a parenthesis
    output->enqueue(operatorStack->pop());
  }

  //Cleanup and return output
  delete operatorStack;
  return output;
}

Node* makeExpressionTree(Queue* input) {

  Stack* stack = new Stack();

  //while stack is not empty, process next node
  while (!input->isEmpty()) {

    Node* next = input->dequeue();

    //make new tree if it's an operator
    if (next->data == "+" or next->data == "-" or next->data == "*" or next->data == "/" or next->data == "^") {

      Node* n2 = stack->pop();
      Node* n1 = stack->pop();

      stack->push(next);
      stack->peek()->left = n1;
      stack->peek()->right = n2;
    }

    //add number to stack (input should be validated already)
    else { stack->push(next); }
  }

  //cleanup
  Node* temp = stack->head;
  stack->head = nullptr;
  delete stack;
  return temp;
}

string getInfix(Node* input) {

  string output;

  if (input->data == "+" or input->data == "-" or input->data == "*" or input->data == "/" or input->data == "^") {

    //print left subtree
    output.append("(");
    output.append(getInfix(input->left));
    output.append(")");

    output.append(input->data);

    //print right subt
    output.append("(");
    output.append(getInfix(input->right));
    output.append(")");
  }

  else { return input->data; }

  return output;
}

string getPostfix(Node* input) {

  string output;

  if (input->left != nullptr) { output.append(getPostfix(input->left)); }
  if (input->right != nullptr) { output.append(getPostfix(input->right)); }
  output.append(input->data);

  return output;
}

string getPrefix(Node* input) {

  string output;

  output.append(input->data);
  if (input->left != nullptr) { output.append(getPostfix(input->left)); }
  if (input->right != nullptr) { output.append(getPostfix(input->right)); }

  return output;
}

bool isEqual(string o1, string o2) {

  if ( getPrecedence(o1) == getPrecedence(o2) ) { return true; }
  return false;
}
      
int getPrecedence(string o1) {
  
  if (o1 == "^") { return 4; }
  if (o1 == "*" or o1 == "/") { return 3; }
  return 2;
}
