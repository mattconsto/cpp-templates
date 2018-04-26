// Expression Template (p1.h)
// Compile and run with `g++ p1.cpp -o p1 && ./p1`
// By Matthew Consterdine <mc21g14@soton.ac.uk>

#include <iostream> // Required for console input and output
#include <cmath> // Required for additional maths operators

#ifndef MetaProgrammingP1_h
#define MetaProgrammingP1_h

typedef int number; // The datatype used.

// Templated Maths
struct Var {static inline number eval(number i) {return i;};}; // A single variable
template<number N=0> struct Lit {static inline number eval(number i) {return N;};}; // An numbereger literal
// Addition, Subtraction, Multiplication, and Division binary operators
template<class A, class B> struct Add {static inline number eval(number i) {return A::eval(i) + B::eval(i);};};
template<class A, class B> struct Sub {static inline number eval(number i) {return A::eval(i) - B::eval(i);};};
template<class A, class B> struct Mul {static inline number eval(number i) {return A::eval(i) * B::eval(i);};};
template<class A, class B> struct Div {static inline number eval(number i) {return A::eval(i) / B::eval(i);};};

// Additional Maths Operators (Commented out as they are not part of the spec).
// template<class A> struct Ln           {static inline number eval(number i) {return log(A::eval(i));};};
// template<class A> struct Log          {static inline number eval(number i) {return log10(A::eval(i));};};
// template<class A> struct Exp          {static inline number eval(number i) {return exp(A::eval(i));};};
// template<class A> struct Sqrt         {static inline number eval(number i) {return sqrt(A::eval(i));};};
// template<class A, class B> struct Mod {static inline number eval(number i) {return A::eval(i) % B::eval(i);};};
// template<class A, class B> struct Pow {static inline number eval(number i) {return pow(A::eval(i), B::eval(i));};};

#endif
