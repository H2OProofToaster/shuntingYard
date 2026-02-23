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
string getGreater(string o1, string o2);

int main() {

  //Ask for input
  string input;
  cout << "What is the input (infix)? ";
  cin >> input;

  //Do shunting yard algorithm
  cout << "Shunting..." << endl;

  Queue* shuntingOut = shuntingYard(input);
  
  cout << "Done" << endl;

  //Make bianry expression tree
  cout << "Making tree..." << endl;

  Node* tree = makeExpressionTree(shuntingOut);

  cout << "Done" << endl;

  //Ask for output
  string outputType;
  while (outputType.empty()) {
    cout << "INFIX, POSTFIX, or PREFIX? ";
    cin >> outputType;

    if (outputType == "INFIX" or outputType == "in") { cout << getInfix(tree) << endl; }
    else if (outputType == "POSTFIX" or outputType == "post") { cout << getPostfix(tree) << endl; }
    else if (outputType == "PREFIX" or outputType == "pre") { cout << getPrefix(tree) << endl; }
    else { cout << "Not an option" << endl; }

    outputType.clear();
  }
    
  return 0;
}

Queue* shuntingYard(string input) {

  stringstream ss(input);
  string word;
  Queue* output = new Queue();
  Stack* operatorStack = new Stack();
  
  while (ss >> word) {

    if (word == "0" or word == "1" or word == "2" or word == "3" or word == "4" or word == "5" or word == "6" or word == "7" or word == "8" or word == "9") { output->enqueue(word); }

    else if (word == "+" or word == "-" or word  == "*" or word == "/" or word == "^") {

      while ( (operatorStack->peek()->data != "(") and //top operator (o2) is not "("
	      (
	        getGreater(word, operatorStack->peek()->data) != word or //o2 has greater precedence than o1

		  isEqual(word, operatorStack->peek()->data) and //o1 and o2 have same precedence
		  (word == "+" or word == "-" or word == "*" or word == "/") //o1 is left associative
	      )
	    ) { output->enqueue(operatorStack->pop()); }
      operatorStack->push(word);
    }

    else if (word == "(") { operatorStack->push(word); }

    else if (word == ")") {

      while (operatorStack->peek()->data != "(") {

	if (operatorStack->isEmpty()) { return new Queue("Mismatched parenthesis"); }

	output->enqueue(operatorStack->pop());
      }

      if (operatorStack->peek()->data != "(") { return new Queue("Mismatched parenthesis"); }

      operatorStack->discard();
    }
  }

  while (!operatorStack->isEmpty()) {

    if (operatorStack->peek()->data == "(" or operatorStack->peek()->data == ")") {

      return new Queue("Mismatched parenthesis");
    }

    output->enqueue(operatorStack->pop());
  }

  return output;
}

Node* makeExpressionTree(Queue* input) {

  Stack* stack = new Stack();

  while (!input->isEmpty()) {

    Node* next = input->dequeue();

    if (next->data == "+" or next->data == "-" or next->data == "*" or next->data == "/") {

      Node* n2 = stack->pop();
      Node* n1 = stack->pop();

      stack->push(next);
      stack->peek()->left = n1;
      stack->peek()->right = n2;
    }

    else { stack->push(next); }
  }

  Node* temp = stack->head;
  stack->head = nullptr;
  delete stack;
  return temp;
}

string getInfix(Node* input) {

  string output;

  if (input->data == "+" or input->data == "-" or input->data == "*" or input->data == "/") {

    output.append("(");
    output.append(getInfix(input->left));
    output.append(")");

    output.append(input->data);

    output.append("(");
    output.append(getInfix(input->right));
    output.append(")");
  }

  else { return input->data; }

  return output;
}

string getPostfix(Node* input) {

  string output;

  output.append(getPostfix(input->left));
  output.append(getPostfix(input->right));
  output.append(input->data);

  return output;
}

string getPrefix(Node* input) {

  string output;

  output.append(input->data);
  output.append(getPrefix(input->left));
  output.append(getPrefix(input->right));

  return output;
}

bool isEqual(string o1, string o2) {

  if (o1 == o2) { return true; }
  else if ( (o1 == "*" and o2 == "/") or (o1 == "/" and o2 == "*") ) { return true; }
  else if ( (o1 == "+" and o2 == "-") or (o1 == "-" and o2 == "+") ) { return true; }
  else { return false; }
}
      
string getGreater(string o1, string o2) {

  int num1;
  int num2;
  
  if (o1 == "^") { num1 = 4; }
  else if (o1 == "*" or o1 == "/") { num1 = 3; }
  else { num1 = 2; }

  if (o2 == "^") { num2 = 4; }
  else if (o2 == "*" or o2 == "/") { num2 = 3; }
  else { num2 = 2; }

  if (num1 > num2) { return o1; }
  else if (num2 > num1) { return o2; }
  else if (num1 == num2) { return o1; }
  else { return "err"; }
}
