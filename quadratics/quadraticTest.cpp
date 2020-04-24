// File: Lab2.cpp
// Desc: A program which asks user to input values for a quadratic
//		expression before returning that expression and evaluating
//		the expression for a user input value of x. It then asks
//		the user to add a value to the expression and multiply the
//		expression by a certain value, both chosen by the user.

#include <iostream>
#include "quadratic.h"
using namespace std;

// overloading output as non-member and non-friend function
std::ostream& operator <<(std::ostream& out, const quadratic& quad)
// Postcondition: The a, b, and c coefficients have been written to outs in quadratic form.  The return value is output.
// Library facilities used: iostream
{
	out << quad.getA() << "x^2 + " << quad.getB() << "x + " << quad.getC() << endl;
	return out;
}

// create and display a quadratic expression
void createQuad(quadratic& quad) {
	double a, b, c;
	cout << "\ta: ";
	cin >> a;
	cout << "\tb: ";
	cin >> b;
	cout << "\tc: ";
	cin >> c;
	quad.setA(a);
	quad.setB(b);
	quad.setC(c);
	cout << "\nThe quadratic expression is: \n" << quad << endl;
}

int main()
{
	double x, multiplier;
	quadratic eq1, eq2, eq1a2, eq1m;

	// create first quadratic
	cout << "Input the values for the first quadratic expression." << endl;
	createQuad(eq1);
	cout << "Enter a value for x: ";
	cin >> x;
	cout << "Evaluation of the quadratic expression is: " << eq1.evalQuadForX(x) << endl;

	// create second quadratic to add with first
	cout << "\nInput the values for the second quadratic expression\n\t to add to the first." << endl;
	createQuad(eq2);
	eq1a2 = eq1 + eq2;
	cout << "Added quadratic expression is: " << eq1a2 << endl;
	cout << "Enter a value for x: ";
	cin >> x;
	cout << "\nEvaluation of the quadratic expression is: " << eq1a2.evalQuadForX(x) << endl;

	// create third quadratic to multiply value with first
	cout << "\nInput the multiplier value for the third quadratic expression\n\t to multiply with the first: ";
	cin >> multiplier;
	eq1m = multiplier * eq1;
	cout << "\nThe multiplied quadratic expression is: " << eq1m << endl;
	cout << "Please enter a value for x: ";
	cin >> x;
	cout << "\nEvaluation of the quadratic expression is: " << eq1m.evalQuadForX(x) << endl;
	
	return EXIT_SUCCESS;
}