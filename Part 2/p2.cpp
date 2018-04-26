// Bounds (p2.cpp)
// Compile and run with `g++ p2.cpp -o p2 && ./p2`
// By Matthew Consterdine <mc21g14@soton.ac.uk>

#include "p2.h"

int main() {
	// Example One
	std::cout << "f(x) = (x_{0,5} + 3)*(x_{0,5} + 5)\n"; // The expression that will be evaluated
	typedef Mul<Add<Var<0, 5>, Lit<3>>, Add<Var<0, 5>, Lit<5>>> f; // Build the expression saving in f
	std::cout << BOUNDS<f>::l << " <= f(x) <= " << BOUNDS<f>::u << "\n";
	
	try {
		std::cout << "f(1) = " << f().eval(1) << "\n"; // Evaluate f(1) and prnumber to standard output
		std::cout << "f(4) = " << f().eval(4) << "\n";
		std::cout << "f(7) = " << f().eval(7) << "\n\n";
	} catch(std::out_of_range& e) {
		std::cout << e.what() << " is out of range in f(x)\n\n";
	}
	
	// Example Two
	std::cout << "g(x) = x_{0,7} + (x_{0,7} - 2)*(x_{0,7} - 3)\n";
	typedef Add<Var<0, 7>, Mul<Sub<Var<0, 7>, Lit<2>>, Sub<Var<0, 7>, Lit<3>>>> g;
	std::cout << BOUNDS<g>::l << " <= g(x) <= " << BOUNDS<g>::u << "\n";
	
	try {
		std::cout << "g(1) = " << g().eval(1) << "\n";
		std::cout << "g(4) = " << g().eval(4) << "\n";
		std::cout << "g(7) = " << g().eval(7) << "\n\n";
	} catch(std::out_of_range& e) {
		std::cout << e.what() << " is out of range in g(x)\n\n";
	}

	// Example Three
	std::cout << "h(x) = x_{0,3}*4 + x_{0,3}/3 - 2\n";
	typedef Add<Mul<Var<0, 3>, Lit<4>>, Sub<Div<Var<0, 3>, Lit<3>>, Lit<2>>> h;
	std::cout << BOUNDS<h>::l << " <= h(x) <= " << BOUNDS<h>::u << "\n";

	try {
		std::cout << "h(1) = " << h().eval(1) << "\n";
		std::cout << "h(4) = " << h().eval(4) << "\n";
		std::cout << "h(7) = " << h().eval(7) << "\n\n";
	} catch(std::out_of_range& e) {
		std::cout << e.what() << " is out of range in h(x)\n\n";
	}
}
