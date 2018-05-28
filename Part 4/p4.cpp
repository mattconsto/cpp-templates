// Integer Declarations (p4.cpp)
// Compile and run with `g++ p4.cpp -o p4 && ./p4`
// By Matthew Consterdine <mc21g14@soton.ac.uk>

#include <string>
#include "p4.h"
#include "array_to_string.h"

int main() {
	// Array Example with IntDecl
	std::cout << "f(x) = x_{0,4} + (y_{0,5} - 2)*(z_{0,6} - 3)\n"; // The expression to be evaluated
	typedef Add<Var<BOUNDS<0,4>>, Mul<Sub<Var<BOUNDS<0,5>>, Lit<2>>, Sub<Var<BOUNDS<0,6>>, Lit<3>>>> f; // Build as f
	std::cout << f::l << " <= f(x,y,z) <= " << f::u << "\n";
	
	typedef IntBounded<f>::RET minimum_number_datatype;

	number inputs[][3] = {{0,0,0}, {1,2,3}, {4,5,6}, {7,8,9}, {10,0,0}, {0,10,0}, {-1,-2,-3}};
	int N = ARRAY_SIZE(inputs); // Cache
	minimum_number_datatype outputs[N] = {0};
	bool exceptions[N] = {false};

	// Execute for each input
	for(int i = 0; i < N; i++) {
		// Catch exception if bounds are exceeded!
		try {
			outputs[i] = f().eval(inputs[i]); // Evaluate
		} catch(std::out_of_range& e) {
			exceptions[i] = true; // Save exceptions
		}
	}

	// Print to console
	for(int i = 0; i < N; i++) {
		std::cout << "f(" << array_to_string<int>(inputs[i], ARRAY_SIZE(inputs[i]), ",")  << ")" << 
			(!exceptions[i] ? " = " + std::to_string(outputs[i]) : "threw an exception!") << "\n";
	}

	// Example One (f is reused)
	try {
		// Evaluate f(1,2,3) and print to standard output. Unfreed inline array declarations leak 
		// memory, used for brevity! Ideally would use variadic functions, but the spec asks for arrays.
		std::cout << "f(1,2,3) = " << f().eval(new number[3] {1,2,3}) << "\n";
		std::cout << "f(4,5,6) = " << f().eval(new number[3] {4,5,6}) << "\n";
		std::cout << "f(7,7,7) = " << f().eval(new number[3] {7,7,7}) << "\n\n";
	} catch(std::out_of_range& e) {
		std::cout << e.what() << " is out of range in f(x)\n\n";
	}
	
	// Example Two
	std::cout << "g(x,y,z) = x_{0,7} + (y_{0,7} - 2)*(z_{0,7} - 3)\n";
	typedef Add<Var<BOUNDS<0,7>>, Mul<Sub<Var<BOUNDS<0,7>>, Lit<2>>, Sub<Var<BOUNDS<0,7>>, Lit<3>>>> g;
	std::cout << g::l << " <= g(x,y) <= " << g::u << "\n";
	
	try {
		std::cout << "g(1,2,1) = " << g().eval(new number[3] {1,2,1}) << "\n";
		std::cout << "g(4,5,4) = " << g().eval(new number[3] {4,5,4}) << "\n";
		std::cout << "g(7,7,7) = " << g().eval(new number[3] {7,7,7}) << "\n\n";
	} catch(std::out_of_range& e) {
		std::cout << e.what() << " is out of range in g(x)\n\n";
	}

	// Example Three
	std::cout << "h(x) = x_{0,3}*4 + y_{0,3}/3 - 2\n";
	typedef Add<Mul<Var<BOUNDS<0,3>>, Lit<4>>, Sub<Div<Var<>, Lit<3>>, Lit<2>>> h;
	std::cout << h::l << " <= h(x) <= " << h::u << "\n";

	try {
		std::cout << "h(1,1) = " << h().eval(new number[2] {1,1}) << "\n";
		std::cout << "h(4,4) = " << h().eval(new number[2] {4,4}) << "\n";
		std::cout << "h(7,7) = " << h().eval(new number[2] {7,7}) << "\n\n";
	} catch(std::out_of_range& e) {
		std::cout << e.what() << " is out of range in h(x)\n\n";
	}
}
