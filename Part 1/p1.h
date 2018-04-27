// Expression Template (p1.h)
// Compile and run with `g++ p1.cpp -o p1 && ./p1`
// By Matthew Consterdine <mc21g14@soton.ac.uk>

#include <iostream> // Required for console input and output

#ifndef MetaProgrammingP1_h
#define MetaProgrammingP1_h

typedef int number; // Define a custom number data type for easy changes

// Variable place-holder
struct Var {static inline number eval(number i) {return i;};};

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

#endif
