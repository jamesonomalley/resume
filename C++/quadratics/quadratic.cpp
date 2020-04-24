/*
Author: Jameson O'Malley
File: quadratic.cpp
Desc: Implementation file for the quadratic class.
09/05/2018 --- CRE create quadratic class
*/

#include "quadratic.h" // NOTE: header file in same directory
#include <iostream>
// constructors
quadratic::quadratic() : a(0.0F), b(0.0F), c(0.0F) {}
// parameterized constructor
quadratic::quadratic(double a, double b, double c) {
	setA(a);
	setB(b);
	setC(c);
}
// deconstructor
quadratic::~quadratic() {
}

// mutator methods for private data
void quadratic::setA(double a) {
	this->a = a;
}

void quadratic::setB(double b) {
	this->b = b;
}

void quadratic::setC(double c) {
	this->c = c;
}

// evaluation method
double quadratic::evalQuadForX(double x) {
	double eval = 0;
	eval = (a * (pow(x,2))) + (b * x) + (c);
	return eval;
}

// operator overload

quadratic quadratic::operator+(const quadratic& q_rhs)
{
	quadratic temp;
	temp.a = a + q_rhs.getA();
	temp.b = b + q_rhs.getB();
	temp.c = c + q_rhs.getC();
	return temp;
	
}

quadratic operator*(double m, const quadratic& q)
{
	quadratic temp;
	temp.a = q.a * m;
	temp.b = q.b * m;
	temp.c = q.c * m;
	return temp;
}
