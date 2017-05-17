#ifndef WIEL2_H
#define WIEL2_H

#include <vector>
#include "wiel2.h"
class PolynomialRootFinder
{
protected:

    typedef double PRF_Float_T;

    std::vector<double> m_p_vector;
    std::vector<double> m_qp_vector;
    std::vector<double> m_k_vector;
    std::vector<double> m_qk_vector;
    std::vector<double> m_svk_vector;

    double * m_p_vector_ptr;
    double * m_qp_vector_ptr;
    double * m_k_vector_ptr;
    double * m_qk_vector_ptr;
    double * m_svk_vector_ptr;

    int m_degree;
    int m_n;
    int m_n_plus_one;
    double m_real_s;
    double m_imag_s;
    double m_u;
    double m_v;
    double m_a;
    double m_b;
    double m_c;
    double m_d;
    double m_a1;
    double m_a2;
    double m_a3;
    double m_a6;
    double m_a7;
    double m_e;
    double m_f;
    double m_g;
    double m_h;
    double m_real_sz;
    double m_imag_sz;
    double m_real_lz;
    double m_imag_lz;
    PRF_Float_T m_are;
    PRF_Float_T m_mre;

public:

    PolynomialRootFinder();

    virtual ~PolynomialRootFinder();

    PolynomialRootFinder::RootStatus_T FindRoots(double * coefficient_ptr,
                                                 int degree,
                                                 double * real_zero_vector_ptr,
                                                 double * imaginary_zero_vector_ptr,
                                                 int * number_of_roots_found_ptr = 0);

private:

    int Fxshfr(int l2var);

    int QuadraticIteration(double uu, double vv);

    int RealIteration(double & sss, int & flag);

    int CalcSc();

    void NextK(int itype);

    void Newest(int itype, double & uu, double & vv);

    void QuadraticSyntheticDivision(int n_plus_one,
                                    double u,
                                    double v,
                                    double * p_ptr,
                                    double * q_ptr,
                                    double & a,
                                    double & b);

    void SolveQuadraticEquation(double a,
                                double b,
                                double c,
                                double & sr,
                                double & si,
                                double & lr,
                                double & li);

    PolynomialRootFinder(const PolynomialRootFinder & that);

    PolynomialRootFinder operator =(const PolynomialRootFinder & that);
};

#endif
