// Integer Declarations (p4.cpp)
// Compile and run with `g++ p4.cpp -o p4 && ./p4`
// By Matthew Consterdine <mc21g14@soton.ac.uk>

#include <iostream> // Required for console input and output
#include <stdexcept> // Standard exceptions
#include <limits> // Default values

#ifndef MetaProgrammingP4_h
#define MetaProgrammingP4_h

typedef int number; // Define a custom number data type for easy changes
#define NUM_MIN (std::numeric_limits<number>::min()) // For brevity
#define NUM_MAX (std::numeric_limits<number>::max())

#define ARRAY_SIZE(array) (sizeof array / sizeof array[0]) // Macro to get size of a static array

// BOUNDS template, defaults to [NUM_MIN, NUM_MAX]
template<number L=NUM_MIN, number U=NUM_MAX> struct BOUNDS {
	static const number l = L; static const number u = U;
};

// Multiple variable place-holder
template<number P=0, class=void> struct Var; // Define template class
template<number P> struct Var<P, void> { // Void case
	static const number l = NUM_MIN; static const number u = NUM_MAX;
	static inline number eval(number* i) {return i[P];};
};
template<number P, number L, number U> struct Var<P, BOUNDS<L,U>> { // Bounded case
	static const number l = L; static const number u = U;
	static inline number eval(number* i) {
		if(i[P] < L || i[P] > U) throw std::out_of_range(std::to_string(i[P])); else return i[P];
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
	static inline number eval(number* i) {return A::eval(i) + B::eval(i);};
};
template<class A, class B> struct Sub {
	static const number l = A::l - B::u; static const number u = A::u - B::l;
	static inline number eval(number* i) {return A::eval(i) - B::eval(i);};
};
template<class A, class B> struct Mul {
	static const number l = A::l * B::l; static const number u = A::u * B::u;
	static inline number eval(number* i) {return A::eval(i) * B::eval(i);};
};
template<class A, class B> struct Div {
	static const number l = A::l / B::u; static const number u = A::u / B::l;
	static inline number eval(number* i) {return A::eval(i) / B::eval(i);};
};

// Conditional If template typedef, building blocks for later on
template <bool Cond, class Then, class Else> struct If {typedef Then RET;};
template <class Then, class Else> struct If<false, Then, Else> {typedef Else RET;}; // Specialise!

// Calculates the smallest primitive type to represent a value
// long long int is guaranteed to be bigger than anything that will be passed to this template
template<long long int N=std::numeric_limits<long long int>::max()> struct IntDecl {
	// typename and ::RET are very important, otherwise this will not work!
	typedef typename If<(N >=0 && N <= 255), unsigned char,
		typename If<(N >= 0 && N <= 65535), unsigned int,
			typename If<(N >= -32768 && N <= 32767), signed int, signed long int>::RET>::RET>::RET RET;
};

// Given a formula, get the type for the lower and upper bounds
template<class f> struct IntBounded {
	private:
	// Cache for performance, and save for readability
	typedef typename IntDecl<f::l>::RET _LOWERTYPE;
	typedef typename IntDecl<f::u>::RET _UPPERTYPE;
	static const int _lowersize = sizeof(_LOWERTYPE);
	static const int _uppersize = sizeof(_UPPERTYPE);

	// Choose between the two types, falling back to signed long int if equal
	public:
	typedef typename If<(_lowersize > _uppersize), _LOWERTYPE,
		typename If<(_uppersize > _lowersize), _UPPERTYPE, signed long int>::RET>::RET RET;
};

#endif
