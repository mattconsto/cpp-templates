// Bounds (p2.h)
// Compile and run with `g++ p2.cpp -o p2 && ./p2`
// By Matthew Consterdine <mc21g14@soton.ac.uk>

#include <iostream> // Required for console input and output
#include <stdexcept> // Standard exceptions
#include <limits> // Default values

#ifndef MetaProgrammingP2_h
#define MetaProgrammingP2_h

typedef int number; // Define a custom number data type for easy changes
#define NUM_MIN (std::numeric_limits<number>::min()) // For brevity
#define NUM_MAX (std::numeric_limits<number>::max())

// BOUNDS template, defaults to [NUM_MIN, NUM_MAX]
template<number L=NUM_MIN, number U=NUM_MAX> struct BOUNDS {
	static const number l = L; static const number u = U;
};

// Variable place-holder
template<class=void> struct Var; // Define template class
template<> struct Var<void> {static inline number eval(number i) {return i;};}; // Void case
template<number L, number U> struct Var<BOUNDS<L,U>> { // Bounded case
	static inline number eval(number i) {
		if(i < L || i > U) throw std::out_of_range(std::to_string(i)); else return i;
	};
};

// Literal expression (i.e. number), defaults to 0
template<number N=0> struct Lit {static inline number eval(number i) {return N;};};

// Addition, Subtraction, Multiplication, and Division binary operators
template<class A, class B> struct Add {
	static inline number eval(number i) {return A::eval(i) + B::eval(i);};
};
template<class A, class B> struct Sub {
	static inline number eval(number i) {return A::eval(i) - B::eval(i);};
};
template<class A, class B> struct Mul {
	static inline number eval(number i) {return A::eval(i) * B::eval(i);};
};
template<class A, class B> struct Div {
	static inline number eval(number i) {return A::eval(i) / B::eval(i);};
};

// Bounds finder template
template<class> struct FIND_BOUNDS; // Declare FIND_BOUNDS template class
template<> struct FIND_BOUNDS<Var<void>> { // An unbound variable can represent any value
	static const number l = NUM_MIN; static const number u = NUM_MAX;
};
template<number L, number U> struct FIND_BOUNDS<Var<BOUNDS<L, U>>> { // Bound variable
	static const number l = L; static const number u = U;
};
template<number N> struct FIND_BOUNDS<Lit<N>> { // Literals are constant
	static const number l = N; static const number u = N;
};

// Bounds finder Addition, Subtraction, Multiplication, and Division operations
template<class A, class B> struct FIND_BOUNDS<Add<A, B>> {
	static const number l = FIND_BOUNDS<A>::l + FIND_BOUNDS<B>::l;
	static const number u = FIND_BOUNDS<A>::u + FIND_BOUNDS<B>::u;
};
template<class A, class B> struct FIND_BOUNDS<Sub<A, B>> {
	static const number l = FIND_BOUNDS<A>::l - FIND_BOUNDS<B>::u;
	static const number u = FIND_BOUNDS<A>::u - FIND_BOUNDS<B>::l;
};
template<class A, class B> struct FIND_BOUNDS<Mul<A, B>> {
	static const number l = FIND_BOUNDS<A>::l * FIND_BOUNDS<B>::l;
	static const number u = FIND_BOUNDS<A>::u * FIND_BOUNDS<B>::u;
};
template<class A, class B> struct FIND_BOUNDS<Div<A, B>> {
	static const number l = FIND_BOUNDS<A>::l / FIND_BOUNDS<B>::u;
	static const number u = FIND_BOUNDS<A>::u / FIND_BOUNDS<B>::l;
};

#endif
