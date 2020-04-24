#include <iostream>
#include <cassert> // for assertions
#include <string>
#include <math.h>
using namespace std;

void realRoots_assert(double, double, double, double &, double &);
void realRoots_exception(double, double, double, double &, double &);

int main() {
	double a, b, c, x1, x2;
	cout << "input a: ";
	cin >> a;
	cout << "input b: ";
	cin >> b;
	cout << "input c: ";
	cin >> c;
	realRoots_assert(a, b, c, x1, x2);
	try {
		realRoots_exception(a, b, c, x1, x2);
	}
	catch (const exception& ex) {
		cerr << ex.what() << endl;
		exit(EXIT_FAILURE);
	}
	cout << "x1 is: " << x1 << endl;
	cout << "x2 is: " << x2 << endl;

	return EXIT_SUCCESS;
}

// pre: a is a nonzero and b^2 > 4ac
// post: value of x1 and x2 is returned
void realRoots_assert(double a, double b, double c, double &x1, double &x2) {
	assert(a != 0 && (pow(b, 2) > (4 * a * c)));
	x1 = ((-b - (sqrt(pow(b, 2) - (4 * a * c)))) / (2 * a));
	x2 = ((-b + (sqrt(pow(b, 2) - (4 * a * c)))) / (2 * a));
}

// pre: a is a nonzero and b^2 > 4ac
// post: value of x1 and x2 is returned
void realRoots_exception(double a, double b, double c, double &x1, double &x2) {
	if (a != 0 && (pow(b, 2) > (4 * a * c))) {
		x1 = ((-b - (sqrt(pow(b, 2) - (4 * a * c)))) / (2 * a));
		x2 = ((-b + (sqrt(pow(b, 2) - (4 * a * c)))) / (2 * a));
	}
	else
		throw exception("Error! check precondition.");
	
}