// Mathematical Expressions Project.cpp : The purpose of Part 2 this project is to evaluate a
// postfix expression. The function evalPostfix() will use a stack to push the integers encountered
// in the postfix expression, then perform an operation on the top two operands when the first operation
// is encountered in the expression. This result will then be pushed to the stack. This loop will repeat 
// until there are no more characters in the expression to process, and the final result is returned.

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "PostFixEvaluator.h"

int main()
{
    //Testing for default constructor; default parameters set to "2 2 +"
    PostFixEvaluator myExpression;
    cout << "Current postfix expression: " << myExpression.getPostfix() << endl;
    myExpression.evalPostfix();
    cout << "Final postfix result: " << myExpression.getResult() << endl;
    cout << endl;

    //Testing functions using user-defined parameters
    myExpression.setPostfix("25 43 17 + *");
    cout << "Current postfix expression: " << myExpression.getPostfix() << endl;
    myExpression.evalPostfix();
    cout << "Final postfix result: " << myExpression.getResult() << endl;
    cout << endl;

    //Reading and processing a file containing postfix expressions
    string postfix;
    ifstream input;
    input.open("RpnData.txt");
 
    while (getline(input, postfix))
    {
        try {
            myExpression.setPostfix(postfix);
            cout << "Current postfix expression: " << myExpression.getPostfix() << endl;
            myExpression.evalPostfix();
            cout << "Final postfix result: " << myExpression.getResult() << fixed << setprecision(5) << endl;
        }
        catch (runtime_error& e)
        {
            cout << "Error: " << e.what() << endl;
        }
        cout << endl;
    }
    input.close();

    //***EXCEPTIONS***//
    //Insufficient operands
    try {
        myExpression.setPostfix("3 4 6 - * +");
        cout << "Current postfix expression: " << myExpression.getPostfix() << endl;
        myExpression.evalPostfix();
        cout << "Final postfix result: " << myExpression.getResult() << fixed << setprecision(5) << endl;
    }
    catch (runtime_error& e)
    {
        cout << "Error: " << e.what() << endl;
    }
    cout << endl;

    //Too many operands in expression
    try {
        myExpression.setPostfix("3 4 5 +");
        cout << "Current postfix expression: " << myExpression.getPostfix() << endl;
        myExpression.evalPostfix();
        cout << "Final postfix result: " << myExpression.getResult() << fixed << setprecision(5) << endl;
    }
    catch (runtime_error& e)
    {
        cout << "Error: " << e.what() << endl;
    }
    cout << endl;

    //Division by 0
    try {
        myExpression.setPostfix("5 0 /");
        cout << "Current postfix expression: " << myExpression.getPostfix() << endl;
        myExpression.evalPostfix();
        cout << "Final postfix result: " << myExpression.getResult() << fixed << setprecision(5) << endl;
    }
    catch (runtime_error& e)
    {
        cout << "Error: " << e.what() << endl;
    }
    cout << endl;

    //Invalid token found
    try {
        myExpression.setPostfix("8 9 6 & -");
        cout << "Current postfix expression: " << myExpression.getPostfix() << endl;
        myExpression.evalPostfix();
        cout << "Final postfix result: " << myExpression.getResult() << fixed << setprecision(5) << endl;
    }
    catch (runtime_error& e)
    {
        cout << "Error: " << e.what() << endl;
    }
    cout << endl;

    //Stack underflow
    try {
        myExpression.setPostfix("+ 3 4");
        cout << "Current postfix expression: " << myExpression.getPostfix() << endl;
        myExpression.evalPostfix();
        cout << "Final postfix result: " << myExpression.getResult() << fixed << setprecision(5) << endl;
    }
    catch (runtime_error& e)
    {
        cout << "Error: " << e.what() << endl;
    }
    cout << endl;

    //Improper formatting
    try {
        myExpression.setPostfix("3  +  5");
        cout << "Current postfix expression: " << myExpression.getPostfix() << endl;
        myExpression.evalPostfix();
        cout << "Final postfix result: " << myExpression.getResult() << fixed << setprecision(5) << endl;
    }
    catch (runtime_error& e)
    {
        cout << "Error: " << e.what() << endl;
    }
    cout << endl;
}


