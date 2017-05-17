#include <memory>
#include <float.h>
#include <math.h>
#include <assert.h>
#include <exception>
#include "wiel.h"
#include "wiel2.h"
Polynomial::Polynomial()
  : m_degree(-1)
  , m_coefficient_vector_ptr(NULL)
{
    SetToScalar(0.0);
}
Polynomial::Polynomial(double scalar)
  : m_degree(-1)
  , m_coefficient_vector_ptr(NULL)
{
    SetToScalar(scalar);
}
Polynomial::Polynomial(double x_coefficient, double scalar)
  : m_degree(-1)
  , m_coefficient_vector_ptr(NULL)
{
    SetToFirstOrderPolynomial(x_coefficient, scalar);
}
Polynomial::Polynomial(double x_squared_coefficient, double x_coefficient, double scalar)
  : m_degree(-1)
  , m_coefficient_vector_ptr(NULL)
{
    SetToQuadraticPolynomial(x_squared_coefficient, x_coefficient, scalar);
}
Polynomial::Polynomial(double * coefficient_vector_ptr, int degree)
  : m_degree(-1)
  , m_coefficient_vector_ptr(NULL)
{
    SetCoefficients(coefficient_vector_ptr, degree);
}
Polynomial::Polynomial(const Polynomial & polynomial)
  : m_degree(-1)
  , m_coefficient_vector_ptr(NULL)
{
    Copy(polynomial);
}
void Polynomial::SetCoefficients(double * coefficient_vector_ptr,
                                 int degree)
{
    assert(degree >= 0);

    m_degree = degree;

    SetLength(m_degree + 1, false);

    int ii = 0;

    for (ii = 0; ii <= m_degree; ++ii)
    {
        m_coefficient_vector_ptr[ii] = coefficient_vector_ptr[ii];
    }

    AdjustPolynomialDegree();
}
void Polynomial::SetToScalar(double scalar)
{
    SetCoefficients(&scalar, 0);
}
void Polynomial::SetToFirstOrderPolynomial(double x_coefficient, double scalar)
{
    double coefficient_array[2];
    coefficient_array[0] = scalar;
    coefficient_array[1] = x_coefficient;
    SetCoefficients(&coefficient_array[0], 1);
}
void Polynomial::SetToQuadraticPolynomial(double x_squared_coefficient,
                                          double x_coefficient,
                                          double scalar)
{
    double coefficient_array[3];
    coefficient_array[0] = scalar;
    coefficient_array[1] = x_coefficient;
    coefficient_array[2] = x_squared_coefficient;
    SetCoefficients(&coefficient_array[0], 2);
}
double Polynomial::EvaluateReal(double xr) const
{
    assert(m_degree >= 0);

    double pr = m_coefficient_vector_ptr[m_degree];
    int i = 0;

    for (i = m_degree - 1; i >= 0; --i)
    {
        pr = pr * xr + m_coefficient_vector_ptr[i];
    }

    return pr;
}
double Polynomial::EvaluateReal(double xr, double & dr) const
{
    assert(m_degree >= 0);

    double pr = m_coefficient_vector_ptr[m_degree];
    dr = pr;

    int i = 0;

    for (i = m_degree - 1; i > 0; --i)
    {
        pr = pr * xr + m_coefficient_vector_ptr[i];
        dr = dr * xr + pr;
    }

    pr = pr * xr + m_coefficient_vector_ptr[0];

    return pr;
}
void Polynomial::EvaluateImaginary(double xi,
                                   double & pr,
                                   double & pi) const
{
    assert(m_degree >= 0);

    pr = m_coefficient_vector_ptr[m_degree];
    pi = 0;

    int i = 0;

    for (i = m_degree - 1; i >= 0; --i)
    {
        double temp = -pi * xi + m_coefficient_vector_ptr[i];
        pi = pr * xi;
        pr = temp;
    }

    return;
}
void Polynomial::EvaluateComplex(double xr,
                                 double xi,
                                 double & pr,
                                 double & pi) const
{
    assert(m_degree >= 0);

    pr = m_coefficient_vector_ptr[m_degree];
    pi = 0;

    int i = 0;

    for (i = m_degree - 1; i >= 0; --i)
    {
        double temp = pr * xr - pi * xi + m_coefficient_vector_ptr[i];
        pi = pr * xi + pi * xr;
        pr = temp;
    }

    return;
}
void Polynomial::EvaluateComplex(double xr,
                                 double xi,
                                 double & pr,
                                 double & pi,
                                 double & dr,
                                 double & di) const
{
    assert(m_degree >= 0);

    pr = m_coefficient_vector_ptr[m_degree];
    pi = 0;
    dr = pr;
    di = 0;

    double temp = 0.0;
    int i = 0;

    for (i = m_degree - 1; i > 0; --i)
    {
        temp = pr * xr - pi * xi + m_coefficient_vector_ptr[i];
        pi = pr * xi + pi * xr;
        pr = temp;

        temp = dr * xr - di * xi + pr;
        di = dr * xi + di * xr + pi;
        dr = temp;
    }

    temp = pr * xr - pi * xi + m_coefficient_vector_ptr[0];
    pi = pr * xi + pi * xr;
    pr = temp;

    return;
}
Polynomial Polynomial::Derivative() const
{
    Polynomial derivative_polynomial;

    assert(m_degree >= 0);

    if (m_degree > 0)
    {


        derivative_polynomial.SetLength(m_degree);

        derivative_polynomial.m_degree = m_degree - 1;


        double * temp_ptr = derivative_polynomial.m_coefficient_vector_ptr;

        for (int i = m_degree; i > 0; --i)
        {
            temp_ptr[i - 1] = (double)(i) * m_coefficient_vector_ptr[i];
        }
    }
    else
    {
        derivative_polynomial = 0.0;
    }

    return derivative_polynomial;
}
Polynomial Polynomial::Integral() const
{
    Polynomial integral_polynomial;

    assert(m_degree >= 0);

    integral_polynomial.SetLength(m_degree + 2);

    integral_polynomial.m_degree = m_degree + 1;


    double * temp_ptr = integral_polynomial.m_coefficient_vector_ptr;
    int i = 0;

    for (i = m_degree; i > 0; --i)
    {
        temp_ptr[i + 1] = m_coefficient_vector_ptr[i] / (double)(i + 1);
    }

    return integral_polynomial;
}
int Polynomial::Degree() const
{
    return m_degree;
}
PolynomialRootFinder::RootStatus_T Polynomial::FindRoots(double * real_zero_vector_ptr,
                                                         double * imaginary_zero_vector_ptr,
                                               int * roots_found_ptr) const
{
    assert(m_degree >= 0);

    PolynomialRootFinder * polynomial_root_finder_ptr = new PolynomialRootFinder;

    if (polynomial_root_finder_ptr == NULL)
    {
        throw std::bad_alloc();
    }

    std::auto_ptr<PolynomialRootFinder> root_finder_ptr(polynomial_root_finder_ptr);

    PolynomialRootFinder::RootStatus_T status = root_finder_ptr->FindRoots(m_coefficient_vector_ptr,
                                                                           m_degree,
                                                                           real_zero_vector_ptr,
                                                                           imaginary_zero_vector_ptr,
                                                                           roots_found_ptr);
    return status;
}
void Polynomial::IncludeRealRoot(double real_value)
{
    if ((m_degree == 0) && (m_coefficient_vector_ptr[0] == 0.0))
    {
        SetToScalar(1.0);
    }

    double coefficient_array[2];
    coefficient_array[0] = -real_value;
    coefficient_array[1] = 1.0;
    Polynomial temp_polynomial(coefficient_array, 1);
    operator *=(temp_polynomial);
    return;
}
void Polynomial::IncludeComplexConjugateRootPair(double real_value, double imag_value)
{
    if ((m_degree == 0) && (m_coefficient_vector_ptr[0] == 0.0))
    {
        SetToScalar(1.0);
    }

    double coefficient_array[3];
    coefficient_array[0] = real_value * real_value + imag_value * imag_value;
    coefficient_array[1] = -(real_value + real_value);
    coefficient_array[2] = 1.0;
    Polynomial temp_polynomial(coefficient_array, 2);
    operator *=(temp_polynomial);
}
void Polynomial::AdjustPolynomialDegree()
{

    while ((m_degree > 0)
        && (fabs(m_coefficient_vector_ptr[m_degree]) < DBL_EPSILON))
    {
        m_coefficient_vector_ptr[m_degree] = 0.0;
        m_degree--;
    }

    return;
}
void Polynomial::Copy(const Polynomial & polynomial)
{
    SetLength(polynomial.m_degree + 1);

    m_degree = polynomial.m_degree;

    for (int i = 0; i <= m_degree; ++i)
    {
        m_coefficient_vector_ptr[i] = polynomial.m_coefficient_vector_ptr[i];
    }

    return;
}
void Polynomial::SetLength(unsigned int number_of_coefficients,
                           bool copy_data_flag)
{

    // If m_degree is equal to -1, then this is a new polynomial and the

    // caller will set m_degree.

    if ((!copy_data_flag) || (m_degree == -1))
    {
        // Clear and resize the coefficient vector.

        m_coefficient_vector.clear();
        m_coefficient_vector.resize(number_of_coefficients);
        m_coefficient_vector_ptr = &m_coefficient_vector[0];
    }
    else
    {

        std::vector<double> temp_vector;
        temp_vector.resize(m_degree + 1);

        int i = 0;

        for (i = 0; i <= m_degree; ++i)
        {
            temp_vector[i] = m_coefficient_vector_ptr[i];
        }


        m_coefficient_vector.clear();
        m_coefficient_vector.resize(number_of_coefficients);
        m_coefficient_vector_ptr = &m_coefficient_vector[0];

        if (number_of_coefficients > (unsigned int)(m_degree + 1))
        {

            for (i = 0; i <= m_degree; ++i)
            {
                m_coefficient_vector_ptr[i] = temp_vector[i];
            }

            for (i = m_degree + 1; i < (int)(number_of_coefficients); ++i)
            {
                m_coefficient_vector_ptr[i] = 0.0;
            }
        }
        else
        {
            for (int i = 0; i < (int)(number_of_coefficients); ++i)
            {
                m_coefficient_vector_ptr[i] = temp_vector[i];
            }
        }
    }

    return;
}
Polynomial operator +(const Polynomial & polynomial_0,
                      const Polynomial & polynomial_1)
{
    return Polynomial(polynomial_0) += polynomial_1;
}
Polynomial operator +(const Polynomial & polynomial,
                      double scalar)
{
    return Polynomial(polynomial) += scalar;
}

Polynomial operator +(double scalar,
                      const Polynomial & polynomial)
{
    return Polynomial(polynomial) += scalar;
}
Polynomial operator -(const Polynomial & minuend_polynomial,
                      const Polynomial & subtrahend_polynomial)
{
    return Polynomial(minuend_polynomial) -= subtrahend_polynomial;
}

