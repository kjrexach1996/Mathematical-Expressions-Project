// PostFixEvaluator.h - specification and implementation file for the PostFixEvaluator class.

#pragma once
#include <iostream>
#include <stack>
#include <sstream> //For tokenizing strings in postfix expression
#include <stdexcept>
#include "InfixToPostfixConverter.h"

using namespace std;

class PostFixEvaluator
{
private:
	//Stores postfix expression
	string postfix;

	//Result of evaluation postfix expression
	double postResult;

public:
	// Preconditions: Access to the member variables postfix and postResult are required to evaluate expression and store result;
	// proper formatting of the expression is necessary; the function must be able to tokenize every individual part of the string
	// to separate it as an individual token to be processed as an integer or operator; any improper syntax or invalid tokens will
	// result in an error message; any integers encountered must be converted from strings to doubles to perform operations.
	// Postconditions: The function will take the result of the expression and store it in the member variable postResult. 
	// Should any errors arise, an error message will be displayed, and evaluation for the current expression will end.
	void evalPostfix()
	{
		//Stack to store operands
		stack<double> st;

		//istringstream object to tokenize strings
		istringstream ss(postfix);

		string token;

		//While tokens can be created from the expression
		while (ss >> token)
		{
			//The first character of the token is an integer. If the expression follows proper formatting rules,
			//this will account for any single- and multi-digit integers.
			if (isdigit(token[0]))
			{
				//Converts the integer token from a string to a double
				double number = stod(token);

				//Stored in stack
				st.push(number);
			}
				
			//The token is an allowed operator
			else if (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/')
			{
				//Exceptions handles stack underflow
				if (st.empty())
					throw runtime_error("Stack is empty!");

				//Exception handles when there are too few operands to perform an operation
				if (st.size() < 2)
					throw runtime_error("Insufficient operands to perform operation.");
					
				//Takes top two operands in the stack to perform operation. Because of the order they were added to the stack,
				//the top operand must be the second in the expression, while the next top the first.
				double operand2 = st.top();
				st.pop();
				double operand1 = st.top();
				st.pop();

				//Performs operation depending on operator encountered
				if (token[0] == '+')
					st.push(operand1 + operand2);
				else if (token[0] == '-')
					st.push(operand1 - operand2);
				else if (token[0] == '*')
					st.push(operand1 * operand2);
				else if (token[0] == '/')
				{
					//Exception handles division by 0
					if (operand2 == 0)
						throw runtime_error("Cannot divide by 0.");
						
					st.push(operand1 / operand2);
				}
			}
			//Exception handles invalid tokens
			else
				throw runtime_error("Invalid token encountered in postfix expression.");
		}
		//Exception handles additional operands that have not had an operation performed on.
		if (st.size() > 1)
			throw runtime_error("Too many operands left in the stack.");

		//Stores final result
		postResult = st.top();
	}

	//Preconditions: Function must take in a string; postfix member variable must be accessible.
	//Postconditions: postfix member variable will be updated with the provided postfix expression.
	void setPostfix(string expr)
	{
		postfix = expr;
	}

	//Preconditions: postfix must be accessible and must be a string.
	//Postconditions: The function will return the value stored in postfix member variable.
	string getPostfix() 
	{
		return postfix;
	}

	//Preconditions: postResult must be accessible and must be a double.
	//Postconditions: The function will return the value stored in postResult.
	double getResult() 
	{
		return postResult;
	}

	//Preconditions: Function must accept a string; postfix member variable must be accessible to store string
	//Postconditions: PostFixEvaluator object is created
	PostFixEvaluator(string postfix = "2 2 +", double postResult = 4)
		: postfix(postfix), postResult(postResult) {}
};
