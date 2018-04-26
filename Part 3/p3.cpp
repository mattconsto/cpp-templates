// Multiple Variables (p3.cpp)
// Compile and run with `g++ p3.cpp -o p3 && ./p3`
// By Matthew Consterdine <mc21g14@soton.ac.uk>

#include "p3.h"

// Get the size of an array
#define ARRAY_SIZE(array) (sizeof array / sizeof array[0])

// Convert an integer array to string using a joiner
std::string int_array_to_string(int array[], int size, std::string joiner) {
	std::string output = "";
	for(int i = 0; i < size; i++) {
		output += std::to_string(array[i]);
		if(i < size-1) output += joiner; // Conditional
	}
	return output;
}
std::string int_array_to_string(int array[], int size) {return int_array_to_string(array, size, "");}

int main() {
	// Example One
	std::cout << "f(x) = x_{0,4} + (y_{0,5} - 2)*(z_{0,6} - 3)\n"; // The expression that will be evaluated
	typedef Add<Var<0, 0, 4>, Mul<Sub<Var<1, 0, 5>, Lit<2>>, Sub<Var<2, 0, 6>, Lit<3>>>> f; // Build the expression saving in f
	std::cout << BOUNDS<f>::l << " <= f(x,y,z) <= " << BOUNDS<f>::u << "\n";
	
	try {
		std::cout << "f(1,2,3) = " << f().eval(new number[3] {1,2,3}) << "\n"; // Evaluate f(1,2,3) and prnumber to standard output
		std::cout << "f(4,5,5) = " << f().eval(new number[3] {4,5,6}) << "\n"; // Unfreed inline array declarations leak memory, used only for brevity!
		std::cout << "f(7,7,7) = " << f().eval(new number[3] {7,7,7}) << "\n\n"; // Ideally would use variadic functions, but the spec calls for arrays.
	} catch(std::out_of_range& e) {
		std::cout << e.what() << " is out of range in f(x)\n\n";
	}
	
	// Example Two
	std::cout << "g(x) = x_{0,7} + (y_{0,7} - 2)*(x_{0,7} - 3)\n";
	typedef Add<Var<0, 0, 7>, Mul<Sub<Var<1, 0, 7>, Lit<2>>, Sub<Var<0, 0, 7>, Lit<3>>>> g;
	std::cout << BOUNDS<g>::l << " <= g(x,y) <= " << BOUNDS<g>::u << "\n";
	
	try {
		std::cout << "g(1,2) = " << g().eval(new number[2] {1,2}) << "\n";
		std::cout << "g(4,5) = " << g().eval(new number[2] {4,5}) << "\n";
		std::cout << "g(7,7) = " << g().eval(new number[2] {7,7}) << "\n\n";
	} catch(std::out_of_range& e) {
		std::cout << e.what() << " is out of range in g(x)\n\n";
	}

	// Example Three
	std::cout << "h(x) = x_{0,3}*4 + x_{0,3}/3 - 2\n";
	typedef Add<Mul<Var<0, 0, 3>, Lit<4>>, Sub<Div<Var<0, 0, 3>, Lit<3>>, Lit<2>>> h;
	std::cout << BOUNDS<h>::l << " <= h(x) <= " << BOUNDS<h>::u << "\n";

	try {
		std::cout << "h(1) = " << h().eval(new number[1] {1}) << "\n";
		std::cout << "h(4) = " << h().eval(new number[1] {4}) << "\n";
		std::cout << "h(7) = " << h().eval(new number[1] {7}) << "\n\n";
	} catch(std::out_of_range& e) {
		std::cout << e.what() << " is out of range in h(x)\n\n";
	}

	// Array Example
	number inputs[][3] = {{0, 0, 0}, {1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 0, 0}, {0, 10, 10}, {-1, -2, -3}};
	int N = ARRAY_SIZE(inputs);
	number outputs[N] = {0};
	bool exceptions[N] = {false};

	// Execute
	for(int i = 0; i < N; i++) {
		try {
			// Reuse f(x,y,z) from earlier
			outputs[i] = f().eval(inputs[i]);
		} catch(std::out_of_range& e) {
			exceptions[i] = true;
		}
	}

	// Print
	for(int i = 0; i < N; i++) {
		if(!exceptions[i]) {
			std::cout << "f(" << int_array_to_string(inputs[i], ARRAY_SIZE(inputs[i]), ",") << ") = " << outputs[i] << "\n";
		} else {
			std::cout << "f(" << int_array_to_string(inputs[i], ARRAY_SIZE(inputs[i]), ",") << ") threw an exception!\n";
		}
	}
}
