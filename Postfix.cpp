#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <stack>
#include <cctype>
using namespace std;

class Calculator
{
  string infix;
  string postfix;
public:
  Calculator(){ infix = postfix = ""; }
  string getInfix(){ return infix; }
  void setInfix(string i){ infix = i; }

  void showInfix(string expression){ cout << expression << endl; }
  void showPostfix();
  string converToPostfix(string);
  bool precedence(char, char);
};
bool IsOperator(char);
bool IsOperand(char);

bool Calculator::precedence(char operator1, char operator2)//if */, true; +-, false//s.top(), expression[i]
{
  int flag1 = 0;
  int flag2 = 0;

  if ((operator1 == '*') || (operator1 == '/'))
    flag1 = 1;//flag2 = 0
  else if ((operator1 == '+') || (operator1 == '-'))
  {
    if ((operator2 == '*') || (operator2 == '/'))
      flag2 = 1;//flag1 = 0;
    else
      flag1 = 1;
  }

  if (flag1 >= flag2)
    return true;
  else
    return false;
}

bool IsOperator(char operatorX)
{
  if (operatorX == '+' || operatorX == '-' || operatorX == '*' || operatorX == '/')
    return true;
  else
    return false;
}

bool IsOperand(char operand)
{
  if (operand >= '0' && operand <= '9') return true;
  else if (operand >= 'a' && operand <= 'z') return true;
  else if (operand >= 'A' && operand <= 'Z') return true;
  else return false;
}

string Calculator::converToPostfix(string expression)
{
  string postfix = "";
  stack <char> s;

  char sym;
  for (int i = 0; i < expression.length(); i++) 
  {
    if (expression[i] == ' ' || expression[i] == ',') continue;
    else if (IsOperand(expression[i]))//if an operand
      postfix += expression[i];
    else if (expression[i] == '(')
      s.push(expression[i]);
    else if (expression[i] == ')')
    {
      while (!s.empty() && s.top() != '(')
      {
        postfix += s.top();
        s.pop();
      }
      s.pop();
    }
    else if (IsOperator(expression[i]))//if an operator
    {
      while (!s.empty() && s.top() != '(' &&precedence(s.top(), expression[i]))//s.top(), expression[i]
      {
 //       cout << "expression" << expression[i] << endl;
 //       cout << "s.top()" << s.top() << endl;
        postfix += s.top();
        s.pop();
      }
      s.push(expression[i]);//push operator in when it is empty
    }
    //cout << "working" << endl;
    else
      continue;
  }
  while (!s.empty()) 
  {
    postfix += s.top();
    s.pop();
  }
  return postfix;
}


int main()
{
  string infix;
  Calculator c;
  while (true)
  {
    cout << "Enter your infix expression (Enter Q or q to quit):" << endl;
    getline(cin, infix);
    c.setInfix(infix);
    if (infix == "Q" || infix == "q")
      break;
    cout << "Infix expression: ";
    c.showInfix(infix);
    string postfix = c.converToPostfix(infix);
    cout << "Postfix expression: " << postfix << endl << endl;
  }

}


