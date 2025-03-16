//InfixToPostfixConverter.h - specifications and implementations for the InfixToPostfixConverter class.
//This class will convert an infix mathematical expression and convert it into a 
//postfix expression through the use of a stack.

#pragma once
#include <iostream>
#include <stack>
#include <stdexcept>

using namespace std;

class InfixToPostfixConverter
{
private:
	//Stores initial infix expression
	string infixExpr; 

	//Stores postfix expression after converting infix
	//Can be accessed using getter function getPostfix
	//Can only be updated infix expression conversion
	string postfixExpr; 
public:
	//Function used to convert infix expression to postfix
	void convertInfixToPostfix()
	{
		//Create a stack
		stack<char> st;

		//Used to store final postfix
		string postfix;

		//
		int operand;
		
		//Used to track characters in infix expression string
		int index = 0;

		//For every character in the string
		for (char a : infixExpr)
		{
			//If the character is an integer
			if (isdigit(a))
			{
				postfix += a;
			}

			//If the character is an operator
			else if (a == '+' || a == '-' || a == '*' || a == '/')
			{
				//Checks to see whether the first or last character in the infix expression is an operator
				//Will display error message
				if (infixExpr[0] == a || infixExpr[infixExpr.size() - 1] == a)
					throw runtime_error("Improper placement of operator in infix expression");

				//While the list is not empty and the operator on the stack precedes the current operator
				while (!st.empty() && precedes(a, st.top()))
				{
					//Top operator on the stack is added to postfix and removed from stack 
					postfix += st.top();
					st.pop();
				}
				//Current operator in infix is added to stack 
				st.push(a);
			}
			//If character is '(', added to stack
			else if (a == '(')
			{
				st.push(a);
			}
			//If character is ')'
			else if (a == ')')
			{
				//Checks to see there is a '(' in the stack to pair with ')' while stack is empty; will display error message if absent
				if (st.empty())
					throw runtime_error("Mismatched parentheses: No opening parentheses '(' found for closing ')'");

				//While stack is empty and top character in stack is not '('
				//Top character in stack is added to postfix and removed from stack
				while (!st.empty() && st.top() != '(')
				{
					postfix += " "; //Adds whitespace between characters in postfix
					postfix += st.top();
					st.pop();
				}
				//Checks to see there is a '(' in the stack to pair with ')' after all other operators have been processed;
				//Will display error message if absent
				if (st.empty())
					throw runtime_error("Mismatched parentheses: No opening parentheses '(' found for closing ')'");
				st.pop();
			}
			else if (isspace(a))
			{
				//Checks to see if two integers are placed next to each other in infix; will display error message
				//when two integers are seen next to each other
				if (isdigit(infixExpr[index + 1]) && isdigit(infixExpr[index - 1]))
					throw runtime_error("Improper placement of operand in infix expression");

				//Checks to see if two operators are placed next to each other in infix; will display error message
				//if two operators are seen next to each other
				if ((infixExpr[index + 1] == '+' || infixExpr[index + 1] == '-' || infixExpr[index + 1] == '*' || infixExpr[index + 1] == '/')
					&& (infixExpr[index - 1] == '+' || infixExpr[index - 1] == '-' || infixExpr[index - 1] == '*' || infixExpr[index - 1] == '/'))
					throw runtime_error("Improper placement of operator in infix expression");

				//Adds a first whitespace to postfix
				//*All other whitespaces are added to postfix when emptying stack*
				if (!isspace(postfix[postfix.size() - 1]))
					postfix += a;
			}
			//Accounts for any characters that are not integers, operators, or '(' or ')'
			else
				throw runtime_error("Invalid character detected in expression"); 

			//Updates index for next character
			index++;
		}
		//After processing infix, while the stack is still not empty
		while (!st.empty())
		{
			//Checks to see if ')' was processed in infix to pair with ')'; displays error message if not
			if (st.top() == '(')
				throw runtime_error("No closing parentheses ')' found for '('");

			postfix += " "; //Adds whitespace between characters in postfix
			postfix += st.top(); //Top character in stack is added to postfix and removed from stack 
			st.pop();
		}
		//Final postfix expression is updated
		postfixExpr = postfix;
	}

	bool precedes(char infix, char stack)
	{
		//Accounts for low-order operator precedence
		if (infix == '+' || infix == '-')
		{
			if (stack == '+' || stack == '-' || stack == '*' || stack == '/')
				return true;
		}

		//Accounts for high-order operator precedence
		if (infix == '*' || infix == '/')
		{
			if (stack == '*' || stack == '/')
				return true;
			else
				return false;
		}

		//Accounts for '(' and ')'; these will not precede infix operators and not be added to the postfix expression
		if ((infix == '+' || infix == '-' || infix == '*' || infix == '/') && (stack == '(' || stack == ')') || isspace(stack))
			return false;
	}

	void setInfix(string newExpression)
	{
		//Updates infix expressions
		infixExpr = newExpression;
	}

	string getInfix()
	{
		//Returns infix expression
		return infixExpr;
	}

	string getPostfix()
	{
		//Returns postfix expression 
		return postfixExpr;
	}

	//Default and user-defined constructor
	InfixToPostfixConverter(string infixExpr = "2 + 2")
		: infixExpr(infixExpr) {}
};


