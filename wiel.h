#ifndef WIEL_H
#define WIEL_H

#include <vector>
#include "wiel2.h"
class Polynomial
{
protected:

    std::vector<double> m_coefficient_vector;
    int m_degree;
    double * m_coefficient_vector_ptr;

public:

    Polynomial();

    Polynomial(double scalar);

    Polynomial(double x_coefficient, double scalar);

    Polynomial(double x_squared_coefficient,
               double x_coefficient,
               double scalar);

    Polynomial(double * coefficient_vector, int degree);

    Polynomial(const Polynomial & polynomial);

    virtual ~Polynomial();

    void SetCoefficients(double * coefficient_vector_ptr,
                         int degree);

    void SetToScalar(double scalar);

    void SetToFirstOrderPolynomial(double x_coefficient, double scalar);

    void SetToQuadraticPolynomial(double x_squared_coefficient,
                                  double x_coefficient,
                                  double scalar);

    double EvaluateReal(double xr) const;

    double EvaluateReal(double xr, double & dr) const;

    void EvaluateImaginary(double xi,
                           double & pr,
                           double & pi) const;

    void EvaluateComplex(double xr,
                         double xi,
                         double & pr,
                         double & pi) const;

    void EvaluateComplex(double xr,
                         double xi,
                         double & pr,
                         double & pi,
                         double & dr,
                         double & di) const;

    Polynomial Derivative() const;

    Polynomial Integral() const;

    int Degree() const;

    PolynomialRootFinder::RootStatus_T FindRoots(double * real_zero_vector_ptr,
                                                 double * imaginary_zero_vector_ptr,
                                                 int * roots_found_ptr = 0) const;

    void IncludeRealRoot(double real_value);

    void IncludeComplexConjugateRootPair(double real_value, double imag_value);

    bool Divide(const Polynomial & divisor_polynomial,
                Polynomial & quotient_polynomial,
                Polynomial & remainder_polynomial) const;

    double operator [](int power_index) const;

    double & operator [](int power_index);

    Polynomial operator +=(const Polynomial & polynomial);

    Polynomial operator +=(double scalar);

    Polynomial operator -=(const Polynomial & polynomial);

    Polynomial operator -=(double scalar);

    Polynomial operator *=(const Polynomial & polynomial);

    Polynomial operator *=(double scalar);

    Polynomial operator /=(double scalar);

    Polynomial operator +();

    Polynomial operator -();

    Polynomial operator =(double scalar);

    Polynomial operator =(const Polynomial & polynomial);

private:

    void AdjustPolynomialDegree();

    void Copy(const Polynomial & polynomial);

    void SetLength(unsigned int number_of_coefficients,
                   bool copy_data_flag = true);
};
#endif
