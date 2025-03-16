// Mathematical Expressions Project.cpp : The purpose of Part 1 this project is to convert
// an infix mathematical expression into a postfix expression using the functions convertInfixToPostfix()
// and precedes(). Any correctly written expression should be handled regardless of proper spacing.
// The function should account for exceptions and display error messages when encountering expressions
// that included unpaired parentheses and improper formatting of operators and operands.

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "PostFixEvaluator.h"

int main()
{
    string postfix;
    ifstream input;
    input.open("RpnData.txt");
 
    while (getline(input, postfix))
    {
        try {
            //Testing for default constructor; default parameters set to "22+"
            PostFixEvaluator myExpression(postfix);
            cout << "Current postfix expression: " << myExpression.getPostfix() << endl;
            myExpression.evalPostfix();
            cout << "Final postfix result: " << fixed << setprecision(2) << myExpression.getResult() << endl;
            cout.unsetf(ios::fixed);
        }
        catch (runtime_error& e)
        {
            cout << "Error: " << e.what() << endl;
        }
        cout << endl;
    }

    input.close();
}


