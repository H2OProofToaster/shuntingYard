#include <iostream>
#include <string>
#include <sstream>

#include "structs.cpp"

using namespace std;

Queue* shuntingYard(string input);
Node* makeExpressionTree(Queue* input);

void printInfix(Node* input);
void printPostfix(Node* input);
void printPrefix(Node* input);

bool isEqual(string o1, string o2);
int getGreater(string o1, string o2);

int main() {

  //Ask for input
  string input;
  cout << "What is the input (infix)? ";
  cin >> input;

  //Do shunting yard algorithm
  cout << "Shunting..." << endl;

  Queue* shuntingOut = shuntingYard(input);
  cout << "Shunting yard postfix: " << postfix << endl;
  
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

    if (outputType == "INFIX" or outputType == "i") { printInfix(tree); }
    else if (outputType == "POSTFIX" or outputType == "post") { printPostfix(tree); }
    else if (outputType == "PREFIX" or outputType == "pre") { printPrefix(tree); }
    else { cout << "Not an option" << endl; }

    outputType.clear();
  }
    
  return 0;
}

string shuntingYard(string input) {

  stringstream ss(input);
  string word;
  Queue* output = new Queue();
  Stack* operatorStack = new Stack();
  
  while (ss >> word) {

    if (word == "0" or word == "1" or word == "2" or word == "3" or word == "4" or word == "5" or word == "6" or word == "7" or word == "8" or word == "9") { output->enqueue(word); }

    else if (word == "+" or word == "-" or word  == "*" or word == "/" or word == "^") {

      while ( (operatorStack->peek() != "(") and \ //top operator (o2) is not "("
	      (
	        getGreater(word, operatorStack->peek()) != word or	\ //o2 has greater precedence than o1

		  isEqual(word, operatorStack->peek()) and		\ //o1 and o2 have same precedence
		  (word == "+" or word == "-" or word == "*" or word == "/") //o1 is left associative
	      )
	    ) { output->enqueue(operatorStack->pop()); }
      operatorStack->push(word);
    }

    else if (word == "(") { operatorStack->push(word); }

    else if (word == ")") {

      while (operatorStack->peek() != "(") {

	if (operatorStack->isEmpty()) { return new Queue("Mismatched parenthesis"); }

	output->enqueue(operatorStack->pop());
      }

      if (operatorStack->peek() != "(") { return new Queue("Mismatched parenthesis"); }

      operatorStack->discard();
    }
  }

  while (!operatorStack->isEmpty()) {

    if (operatorStack->peek() == "(" or operatorStack->peek() == ")") {

      return new Queue("Mismatched parenthesis");
    }

    output->enqueue(operatorStack->pop());
  }

  return output;
}

bool isEqual(string o1, string o2) {

  if (o1 == o2) { return true; }
  else if ( (o1 == "*" and o2 == "/") or (o1 == "/" and o2 == "*") ) { return true; }
  else if ( (o1 == "+" and o2 == "-") or (o1 == "-" and o2 == "+") ) { return true; }
  else { return false; }
}
      
string getGreater(string o1, string o2) {

  int op1;
  int op2;
  
  if (o1 == "^") { op1 = 4; }
  else if (o1 == "*" or o1 == "/") { op1 = 3; }
  else { op1 = 2; }

  if (o2 = "^") { op2 = 4; }
  else if (o2 == "*" or o2 == "/") { op2 = 3; }
  else { op2 = 2; }

  if (op1 > op2) { return o1; }
  else if (op2 > op1) { return op2; }
  else if (op1 == op2) { return op1; }
}
