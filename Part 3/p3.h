// Multiple Variables (p3.h)
// Compile and run with `g++ p3.cpp -o p3 && ./p3`
// By Matthew Consterdine <mc21g14@soton.ac.uk>

#include <iostream> // Required for console input and output
#include <string> // Required for to_string
#include <stdexcept> // Standard exceptions
#include <limits> // Default values

#ifndef MetaProgrammingP3_h
#define MetaProgrammingP3_h

typedef int number; // The datatype used.

// Templated Maths
// @TODO: Why does L and U need to be stored in the variable and not in BOUNDS? Fix this!
template<number P=0, number L=std::numeric_limits<number>::min(), number U=std::numeric_limits<number>::max()> struct Var {static inline number eval(number* i) {if(i[P] < L || i[P] > U) throw std::out_of_range(std::to_string(i[P])); else return i[P];};}; // A single variable
template<number N=0> struct Lit {static inline number eval(number* i) {return N;};}; // An numbereger literal
// Addition, Subtraction, Multiplication, and Division binary operators
template<class A, class B> struct Add {static inline number eval(number* i) {return A::eval(i) + B::eval(i);};};
template<class A, class B> struct Sub {static inline number eval(number* i) {return A::eval(i) - B::eval(i);};};
template<class A, class B> struct Mul {static inline number eval(number* i) {return A::eval(i) * B::eval(i);};};
template<class A, class B> struct Div {static inline number eval(number* i) {return A::eval(i) / B::eval(i);};};
// Additional Maths Operators have been removed as they are not constexpr.

// Bounds calculator
template<class> struct BOUNDS; // Declare BOUNDS as a templated struct
template<number P, number L, number U> struct BOUNDS<Var<P, L, U>> {static const number l = L; static const number u = U;};
template<number N> struct BOUNDS<Lit<N>> {static const number l = N; static const number u = N;};
template<class A, class B> struct BOUNDS<Add<A, B>> {static const number l = BOUNDS<A>::l + BOUNDS<B>::l; static const number u = BOUNDS<A>::u + BOUNDS<B>::u;};
template<class A, class B> struct BOUNDS<Sub<A, B>> {static const number l = BOUNDS<A>::l - BOUNDS<B>::u; static const number u = BOUNDS<A>::u - BOUNDS<B>::l;};
template<class A, class B> struct BOUNDS<Mul<A, B>> {static const number l = BOUNDS<A>::l * BOUNDS<B>::l; static const number u = BOUNDS<A>::u * BOUNDS<B>::u;};
template<class A, class B> struct BOUNDS<Div<A, B>> {static const number l = BOUNDS<A>::l / BOUNDS<B>::u; static const number u = BOUNDS<A>::u / BOUNDS<B>::l;};

#endif
