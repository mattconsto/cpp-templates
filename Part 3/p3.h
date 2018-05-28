// Multiple Variables (p3.h)
// Compile and run with `g++ p3.cpp -o p3 && ./p3`
// By Matthew Consterdine <mc21g14@soton.ac.uk>

#include <iostream> // Required for console input and output
#include <stdexcept> // Standard exceptions
#include <limits> // Default values

#ifndef MetaProgrammingP3_h
#define MetaProgrammingP3_h

typedef int number; // Define a custom number data type for easy changes
#define NUM_MIN (std::numeric_limits<number>::min()) // For brevity
#define NUM_MAX (std::numeric_limits<number>::max())

#define ARRAY_SIZE(array) (sizeof array / sizeof array[0]) // Macro to get size of a static array

// Depth counting to auto reset the global index for multiple variables.
struct Counter {
	static int depth;
	static int index;

	static void descend() {
		++depth;
		// Automatically reset the global index when depth = 1
		if(depth == 1) index = 0;
	}
	static void ascend() {--depth;}
	static void reset() {depth = 0;}
};
int Counter::depth = 0;
int Counter::index = 0;

// BOUNDS template, defaults to [NUM_MIN, NUM_MAX]
template<number L=NUM_MIN, number U=NUM_MAX> struct BOUNDS {
	static const number l = L; static const number u = U;
};

// Multiple variable place-holder
template<class=void> struct Var; // Define template class
template<> struct Var<void> { // Void case
	static const number l = NUM_MIN; static const number u = NUM_MAX;
	static inline number eval(number* i) {
		Counter::descend(); // Descend 
		number result = i[Counter::index++]; // Be careful to supply enough parameters!
		Counter::ascend(); // Ascend
		return result;
	};
};
template<number L, number U> struct Var<BOUNDS<L,U>> { // Bounded case
	static const number l = L; static const number u = U;
	static inline number eval(number* i) {
		Counter::descend();
		if(i[Counter::index] < L || i[Counter::index] > U) {
			Counter::reset(); // Exceptions skip other Counter::ascend();'s, need to reset
			throw std::out_of_range(std::to_string(i[Counter::index]));
		} else {
			number result = i[Counter::index++];
			Counter::ascend();
			return result;
		}
	};
};

// Literal expression (i.e. number), defaults to 0
template<number N=0> struct Lit {
	static const number l = N; static const number u = N;
	static inline number eval(number* i) {return N;};
};

// Addition, Subtraction, Multiplication, and Division binary operators
template<class A, class B> struct Add {
	static const number l = A::l + B::l; static const number u = A::u + B::u;
	static inline number eval(number* i) {
		Counter::descend();
		number result = A::eval(i) + B::eval(i);
		Counter::ascend();
		return result;
	};
};
template<class A, class B> struct Sub {
	static const number l = A::l - B::u; static const number u = A::u - B::l;
	static inline number eval(number* i) {
		Counter::descend();
		number result = A::eval(i) - B::eval(i);
		Counter::ascend();
		return result;
	};
};
template<class A, class B> struct Mul {
	static const number l = A::l * B::l; static const number u = A::u * B::u;
	static inline number eval(number* i) {
		Counter::descend();
		number result = A::eval(i) * B::eval(i);
		Counter::ascend();
		return result;
	};
};
template<class A, class B> struct Div {
	static const number l = A::l / B::u; static const number u = A::u / B::l;
	static inline number eval(number* i) {
		Counter::descend();
		number result = A::eval(i) / B::eval(i);
		Counter::ascend();
		return result;
	};
};

#endif
