#include <iostream>
#include <string>

#include "structs.cpp"

string shuntingYard(string input);
Node* makeExpressionTree(string input);

void printInfix(Node* input);
void printPostfix(Node* input);
void printPrefix(Node* input);

int main() {

  //Ask for input
  string input;
  cout << "What is the input (infix)? ";
  cin >> input;

  //Do shunting yard algorithm
  cout << "Shunting..." << endl;

  string postfix = shuntingYard(input);
  cout << "Shunting yard postfix: " << postfix << endl;
  
  cout << "Done" << endl;

  //Make bianry expression tree
  cout << "Making tree..." << endl;

  Node* tree = makeExpressionTree(postfix);

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
