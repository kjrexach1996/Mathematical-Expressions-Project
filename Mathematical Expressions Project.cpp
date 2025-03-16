// Mathematical Expressions Project.cpp : The purpose of Part 1 this project is to convert
// an infix mathematical expression into a postfix expression using the functions convertInfixToPostfix()
// and precedes(). Any correctly written expression should be handled regardless of proper spacing.
// The function should account for exceptions and display error messages when encountering expressions
// that included unpaired parentheses and improper formatting of operators and operands.

#include <iostream>
#include "InfixToPostfixConverter.h"

int main()
{
    //Testing for default constructor; default parameters set to "2+2"
    InfixToPostfixConverter myExpression;
    cout << "Current infix expression: " << myExpression.getInfix() << endl;
    myExpression.convertInfixToPostfix();
    cout << "Final postfix expression: " << myExpression.getPostfix() << endl;
    cout << endl;

    //Resetting infix expression
    myExpression.setInfix("4 + 5 * 6");

    //Testing for operator precedence, parentheses NOT INCLUDED
    cout << "Current infix expression: " << myExpression.getInfix() << endl;
    myExpression.convertInfixToPostfix();
    cout << "Final postfix expression: " << myExpression.getPostfix() << endl;
    cout << endl;

    //Testing for operator precedence, parentheses INCLUDED
    myExpression.setInfix("12 * (5 + 10) / 3");
    cout << "Current infix expression: " << myExpression.getInfix() << endl;
    myExpression.convertInfixToPostfix();
    cout << "Final postfix expression: " << myExpression.getPostfix() << endl;
    cout << endl;

    //Testing for operator precedence, MULTIPLE parentheses INCLUDED
    myExpression.setInfix("(7 + 8 * (19 - 3)) / 4");
    cout << "Current infix expression: " << myExpression.getInfix() << endl;
    myExpression.convertInfixToPostfix();
    cout << "Final postfix expression: " << myExpression.getPostfix() << endl;
    cout << endl;

    //Same infix expression as above with some whitespaces removed
    myExpression.setInfix("(7 +8 * (19 -3))/ 4");
    cout << "Current infix expression: " << myExpression.getInfix() << endl;
    myExpression.convertInfixToPostfix();
    cout << "Final postfix expression: " << myExpression.getPostfix() << endl;
    cout << endl;

    //***EXCEPTIONS***//
    
    //No closing parentheses
    try {
        
        myExpression.setInfix("(10 * 11 - 12");
        cout << "Current infix expression: " << myExpression.getInfix() << endl;
        myExpression.convertInfixToPostfix();
        cout << "Final postfix expression: " << myExpression.getPostfix() << endl;
        cout << endl;
    } 
    catch (runtime_error& e)
    {
        cout << "Error: " << e.what() << endl;
    }
    cout << endl;

    //No opening parentheses
    try {
        
        myExpression.setInfix("98 + 99 * 100)");
        cout << "Current infix expression: " << myExpression.getInfix() << endl;
        myExpression.convertInfixToPostfix();
        cout << "Final postfix expression: " << myExpression.getPostfix() << endl;
        cout << endl;
    }
    catch (runtime_error &e)
    {
        cout << "Error: " << e.what() << endl;
    }
    cout << endl;

    //Invalid token found in infix expression
    try {

        myExpression.setInfix("1 + 2 & 3");
        cout << "Current infix expression: " << myExpression.getInfix() << endl;
        myExpression.convertInfixToPostfix();
        cout << "Final postfix expression: " << myExpression.getPostfix() << endl;
        cout << endl;
    }
    catch (runtime_error& e)
    {
        cout << "Error: " << e.what() << endl;
    }
    cout << endl;

    //Misplaced operators/operands
    try {

        myExpression.setInfix("1 + * 2");
        cout << "Current infix expression: " << myExpression.getInfix() << endl;
        myExpression.convertInfixToPostfix();
        cout << "Final postfix expression: " << myExpression.getPostfix() << endl;
        cout << endl;
    }
    catch (runtime_error& e)
    {
        cout << "Error: " << e.what() << endl;
    }
    cout << endl;

    try {

        myExpression.setInfix("1 2 +");
        cout << "Current infix expression: " << myExpression.getInfix() << endl;
        myExpression.convertInfixToPostfix();
        cout << "Final postfix expression: " << myExpression.getPostfix() << endl;
        cout << endl;
    }
    catch (runtime_error& e)
    {
        cout << "Error: " << e.what() << endl;
    }
    cout << endl;

    try {

        myExpression.setInfix("+ 4 5");
        cout << "Current infix expression: " << myExpression.getInfix() << endl;
        myExpression.convertInfixToPostfix();
        cout << "Final postfix expression: " << myExpression.getPostfix() << endl;
        cout << endl;
    }
    catch (runtime_error& e)
    {
        cout << "Error: " << e.what() << endl;
    }
    cout << endl;

    //If stack is empty
    try {

        myExpression.setInfix("1 + ) 2 * 3 (");
        cout << "Current infix expression: " << myExpression.getInfix() << endl;
        myExpression.convertInfixToPostfix();
        cout << "Final postfix expression: " << myExpression.getPostfix() << endl;
        cout << endl;
    }
    catch (runtime_error& e)
    {
        cout << "Error: " << e.what() << endl;
    }
    cout << endl;

}


