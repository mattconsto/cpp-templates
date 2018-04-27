// Expression Template (p1.cpp)
// Compile and run with `g++ p1.cpp -o p1 && ./p1`
// By Matthew Consterdine <mc21g14@soton.ac.uk>

#include "p1.h"

int main() {
	// Example One
	std::cout << "f(x) = x + (x - 2)*(x - 3)\n"; // The expression to be evaluated
	typedef Add<Var, Mul<Sub<Var, Lit<2>>, Sub<Var, Lit<3>>>> f; // Build the expression saving in f

	std::cout << "f(1) = " << f().eval(1) << "\n"; // Evaluate f(1) and print to standard output
	std::cout << "f(4) = " << f().eval(4) << "\n";
	std::cout << "f(7) = " << f().eval(7) << "\n\n";

	// Example Two
	std::cout << "g(x) = x*4 + x/3 - 2" << "\n";
	typedef Add<Mul<Var, Lit<4>>, Sub<Div<Var, Lit<3>>, Lit<2>>> g;

	std::cout << "g(1) = " << g().eval(1) << "\n";
	std::cout << "g(4) = " << g().eval(4) << "\n";
	std::cout << "g(7) = " << g().eval(7) << "\n\n";
}
