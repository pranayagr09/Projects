#include <iostream>
#include <vector>
//#include <simplecpp>        (HOW TO INCLUDE SIMPLECPP)
#include <cmath>
using namespace std;
class Polynomial{
            int n,tp,rootsL;
            void printss() const;
            void rootsARRAY();
            double* rootsv;
            int nTerms; // number of terms (NOT DEGREE) <- This is given by user
            double arrayF[101]; /* assumed an upper bound to degree of polynomial viz. 100
                                   could have done dynamic memory allocation, but had started 
                                   working before it was taught*/
       public:
            Polynomial ();   // constructor
            Polynomial (const Polynomial &p);// copy constructor
            void read(); // takes the input of polynomial (first the number of terms and then exponent(s) followed by coefficient(s))
            void print() const; // prints the polynomial in the format (coeff)x^index
            Polynomial operator + (const Polynomial p) const; // overloaded operator for adding 2 polynomials
            Polynomial operator - (const Polynomial p) const; // overloaded operator for subtracting 2 polynomials
            Polynomial operator * (const Polynomial p) const; // overloaded operator for multiplying 2 polynomials
            Polynomial operator / (const Polynomial p) const; // overloaded operator for dividing 2 polynomials(returns quotient)
            Polynomial operator % (const Polynomial p) const; // overloaded operator for dividing 2 polynomials(returns remainder)
            Polynomial derivative() const;// returns the first order derivative of the polynomial
            Polynomial integral() const;// returns the integral of the polynomial wrt x (neglects the constant of integration)
            double root() const; //(polynomial should have atleast one real root) gives only a single(lowest) root...made only for satisfying output on BodhiTree
            double valueAt (double x) const; // finds f(x) at a given point
            void plot (double xLeft, double xRight) const; // plots the graph of the function b/w the interval of the arguments [xLeft, xRight]
            void roots() const; //(polynomial should have atleast one real root) gives "ALL" the roots of the given polynomial (independent of nature of roots)
            Polynomial power(int p) const; // returns the pth power of the polynomial
            void divide (Polynomial q, Polynomial &s, Polynomial &r) const; // assigns p/q to s and p%q to r
            void factorise(); // displays the factorisation of the polynomial(provided that the polynomial has atleast 1 real root)
            bool comparison (const Polynomial p);
            Polynomial GCD (Polynomial p);
            Polynomial LCM (Polynomial p);
};
