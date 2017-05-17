#include <iostream>
#include <vector>
#include "wiel.h"

void DisplayPolynomial(const Polynomial & polynomial);
void GetPolynomial(Polynomial & polynomial, int polynomial_type);
int main ()
{
std::vector<double> real_vector;
std::vector<double> imag_vector;
int degree = polynomial.Degree();
real_vector.resize(degree);
imag_vector.resize(degree);
double * real_vector_ptr = &real_vector[0];
double * imag_vector_ptr = &imag_vector[0];
int root_count= 0;
if (polynomial.FindRoots(real_vector_ptr, imag_vector_ptr, &root_count) == PolynomialRootFinder::SUCCESS)
            {
                int i = 0;

                for (i = 0; i < root_count; ++i)
                {
                    std::cout << "Root " << i << " = " << real_vector_ptr[i] << " + i " << imag_vector_ptr[i] << std::endl;
                }
            }
            else
            {
                std::cout << "Failed to find all roots." << std::endl;
            }
        }
void GetPolynomial(Polynomial & polynomial, int polynomial_type)
{
    std::cout << "Enter the polynomial degree > ";
    int degree = 0;
    std::cin >> degree;
    std::cout << std::endl;
    std::vector<double> coefficient_vector;
    coefficient_vector.resize(degree + 1);
    double * coefficient_vector_ptr = &coefficient_vector[0];
    int i = 0;
    switch (polynomial_type)
    {
    case 1:
        for (i = 0; i <= degree; ++i)
        {
            std::cout << "coefficient[" << i << "] = ";
            double temp;;
            std::cin >> temp;
            coefficient_vector_ptr[i] = temp;
        }
        std::cout << std::endl;
        break;
    case 2:
        for (i = 1; i < degree; ++i)
        {
            coefficient_vector_ptr[i] = 0;
        }
        coefficient_vector_ptr[0] = 1.0;
        coefficient_vector_ptr[degree] = 1.0;
        break;
    case 3:
        for (i = 0; i <= degree; ++i)
        {
            coefficient_vector_ptr[i] = 1.0;
        }
        break;
    default:
        std::cout << "Invalid polynomial type" << std::endl;
        exit(-1);
    }
    polynomial.SetCoefficients(coefficient_vector_ptr, degree);
    return;
}
}
