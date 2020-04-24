#pragma once
/*
Author: Jameson O'Malley
File: quadratic.h
Desc: Declaration/Specification file for the quadratic class.
09/05/2018 --- CRE create quadratic class
*/
#include <iostream>
#include <cmath>
using namespace std;

class quadratic {
private:
	// data members
	double a, b, c;
public:
	// constructors
	quadratic();
	quadratic(double, double, double);
	// destructor
	~quadratic();
	// accessors --> inline functions
	// const method qualifier indicates no change of object data
	double getA() const { return a; }
	double getB() const { return b; }
	double getC() const { return c; }
	// mutators
	void setA(double a);
	void setB(double b);
	void setC(double c);
	// evaluation method
	double evalQuadForX(double x);
	// operator overload
	quadratic operator +(const quadratic& q_rhs);
	// friend function
	friend quadratic operator *(double m, const quadratic& q);
};
/*
Input the values for the first quadratic expression.
a: 3
b: 4
c: 5

The quadratic expression is:
3x^2 + 4x + 5

Enter a value for x: 2
Evaluation of the quadratic expression is: 25

Input the values for the second quadratic expression
to add to the first.
a: 6
b: 7
c: 8

The quadratic expression is:
6x^2 + 7x + 8

Added quadratic expression is: 9x^2 + 11x + 13

Enter a value for x: 3

Evaluation of the quadratic expression is: 127

Input the multiplier value for the third quadratic expression
to multiply with the first: 4

The multiplied quadratic expression is: 12x^2 + 16x + 20

Please enter a value for x: 2

Evaluation of the quadratic expression is: 100
Press any key to continue . . .
*/