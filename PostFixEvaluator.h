// PostFixEvaluator.h - specification and implementation file for the PostFixEvaluator class.

#pragma once
#include <iostream>
#include <stack>
#include <sstream>
#include <stdexcept>
#include "InfixToPostfixConverter.h"

using namespace std;

class PostFixEvaluator
{
private:
	string postfix;
	//Result of evaluation postfix expression
	double postResult;
public:
	void evalPostfix()
	{

		stack<double> st;

		istringstream ss(postfix);
		string token;

		int index = 0;

		while (ss >> token)
		{
			if (isdigit(token[0]))
			{
				double number = stod(token);
				st.push(number);
			}
				
			else if (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/')
			{
				if (st.size() < 2)
					throw runtime_error("Insufficient operands to perform operation.");

				if (token[0] == postfix[0])
					throw runtime_error("Operator appears before operand");
					
				double operand2 = st.top();
				st.pop();
				double operand1 = st.top();
				st.pop();

				if (token[0] == '+')
					st.push(operand1 + operand2);
				else if (token[0] == '-')
					st.push(operand1 - operand2);
				else if (token[0] == '*')
					st.push(operand1 * operand2);
				else if (token[0] == '/')
				{
					if (operand2 == 0)
						throw runtime_error("Cannot divide by 0.");
						
					st.push(operand1 / operand2);
				}
			}
			else
				throw runtime_error("Invalid token encountered in postfix expression.");
		}
		if (st.size() > 1)
			throw runtime_error("Too many operands left in the stack.");

		postResult = st.top();
	}

	void setPostfix(string expr)
	{
		postfix = expr;
	}

	string getPostfix()
	{
		return postfix;
	}

	double getResult() const
	{
		return postResult;
	}

	PostFixEvaluator(string postfix = "22+", double postResult = 4)
		: postfix(postfix), postResult(postResult) {}
};
