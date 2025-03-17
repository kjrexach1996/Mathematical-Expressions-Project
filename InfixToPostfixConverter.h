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
	// Preconditions: Access to the member variables infixExpr and postfixExpr are required; 
	// to correctly convert and format the postfix expression, a properly formatted infix expression
	// should be used; this involves correct use and order of parentheses, integers, and operators. 
	// Correct precedence rules between operators applies. The state of the stack used when storing 
	// characters from the expression should be monitored properly to prevent errors.
	// Postconditions: If no errors have occurred, a postfix expression will be outputted from the 
	// inputted infix expression. No parentheses should appear in the expression if used in the infix. 
	// If errors have occurred, the appropriate error message should display, and further conversion of 
	// the erroneous infix expression will end. 
	void convertInfixToPostfix()
	{
		//Create a stack
		stack<char> st;

		//Used to store final postfix
		string postfix;
		
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

				//Checks to see if two operators are placed next to each other in infix; will display error message
				//if two operators are seen next to each other
				if ((infixExpr[index + 1] == '+' || infixExpr[index + 1] == '-' || infixExpr[index + 1] == '*' || infixExpr[index + 1] == '/')
					|| (infixExpr[index - 1] == '+' || infixExpr[index - 1] == '-' || infixExpr[index - 1] == '*' || infixExpr[index - 1] == '/'))
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
			//Checks to see if ')' was processed in infix to pair with '('; displays error message if not
			if (st.top() == '(')
				throw runtime_error("No closing parentheses ')' found for '('");

			postfix += " "; //Adds whitespace between characters in postfix
			postfix += st.top(); //Top character in stack is added to postfix and removed from stack 
			st.pop();
		}
		//Final postfix expression is updated
		postfixExpr = postfix;
	}
	// Preconditions: The function convertInfixToPostfix must be able to call this function and pass along
	// the current infix character and the top stack character; access to the stack is necessary. The infix character
	// passed to the stack must be an operator. If comparing an operator and a non-operator, the function must return false.
	// Postconditions: The function will return true if the top stack character has a higher or equal precedence to the infix value.
	// If the infix value is of lower priority, or if the top stack character is a non-operator, the function returns false.
	bool precedes(char infix, char stack)
	{
		//Accounts for low-order operator precedence
		if (infix == '+' || infix == '-')
		{
			if (stack == '+' || stack == '-' || stack == '*' || stack == '/')
				return true;
		}

		//Accounts for high-order operator precedence
		else if (infix == '*' || infix == '/')
		{
			if (stack == '*' || stack == '/')
				return true;
			else
				return false;
		}

		//Accounts for '(' and ')'; these will not precede infix operators and not be added to the postfix expression
		if ((infix == '+' || infix == '-' || infix == '*' || infix == '/') && (stack == '(' || stack == ')'))
			return false;
	}

	// Preconditions: Function must take in a string; infixExpr must be accessible.
	// Postconditions: infixExpr will be updated with infix expression.
	void setInfix(string newExpression)
	{
		//Updates infix expressions
		infixExpr = newExpression;
	}

	// Preconditions: infixExpr must be accessible and must be a string.
	// Postconditions: The function will return the value stored in infixExpr.
	string getInfix()
	{
		//Returns infix expression
		return infixExpr;
	}

	// Preconditions: postfixExpr must be accessible and must be a string.
	// Postconditions: The function will return the value stored in postfixExpr.
	string getPostfix()
	{
		//Returns postfix expression 
		return postfixExpr;
	}

	//Default and user-defined constructor
	// Preconditions: Function must accept a string; infixExpr must be accessible to store string
	// Postconditions: InfixToPostfixConverter object is created
	InfixToPostfixConverter(string infixExpr = "2 + 2")
		: infixExpr(infixExpr) {}
};


