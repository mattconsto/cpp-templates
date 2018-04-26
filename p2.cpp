// Bounds (p2.cpp)
// Compile and run with `g++ p2.cpp -o p2 && ./p2`
// By Matthew Consterdine <mc21g14@soton.ac.uk>

#include <iostream> // Required for console input and output
#include <string> // Required for to_string
#include <stdexcept> // Standard exceptions
#include <limits> // Default values

typedef int number; // The datatype used.

// Templated Maths
// @TODO: Why does L and U need to be stored in the variable and not in BOUNDS? Fix this!
template<number L=std::numeric_limits<number>::min(), number U=std::numeric_limits<number>::max()> struct Var {static inline number eval(number i) {if(i < L || i > U) throw std::out_of_range(std::to_string(i)); else return i;};}; // A single variable
template<number N=0> struct Lit {static inline number eval(number i) {return N;};}; // An numbereger literal
// Addition, Subtraction, Multiplication, and Division binary operators
template<class A, class B> struct Add {static inline number eval(number i) {return A::eval(i) + B::eval(i);};};
template<class A, class B> struct Sub {static inline number eval(number i) {return A::eval(i) - B::eval(i);};};
template<class A, class B> struct Mul {static inline number eval(number i) {return A::eval(i) * B::eval(i);};};
template<class A, class B> struct Div {static inline number eval(number i) {return A::eval(i) / B::eval(i);};};
// Additional Maths Operators have been removed as they are not constexpr.

// Bounds calculator
template<typename> struct BOUNDS; // Declare BOUNDS as a templated struct
template<number L, number U> struct BOUNDS<Var<L, U>> {static const number l = L; static const number u = U;};
template<number N> struct BOUNDS<Lit<N>> {static const number l = N; static const number u = N;};
template<class A, class B> struct BOUNDS<Add<A, B>> {static const number l = BOUNDS<A>::l + BOUNDS<B>::l; static const number u = BOUNDS<A>::u + BOUNDS<B>::u;};
template<class A, class B> struct BOUNDS<Sub<A, B>> {static const number l = BOUNDS<A>::l - BOUNDS<B>::u; static const number u = BOUNDS<A>::u - BOUNDS<B>::l;};
template<class A, class B> struct BOUNDS<Mul<A, B>> {static const number l = BOUNDS<A>::l * BOUNDS<B>::l; static const number u = BOUNDS<A>::u * BOUNDS<B>::u;};
template<class A, class B> struct BOUNDS<Div<A, B>> {static const number l = BOUNDS<A>::l / BOUNDS<B>::u; static const number u = BOUNDS<A>::u / BOUNDS<B>::l;};

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
