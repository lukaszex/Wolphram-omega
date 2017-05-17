#include <math.h>
#include <float.h>
#include "wiel2.h"

namespace
{
 const float f_BASE = 2.0;
    const float f_ETA = FLT_EPSILON;
    const float f_ETA_N = (float)(10.0) * f_ETA;
    const float f_ETA_N_SQUARED = (float)(100.0) * f_ETA;
    const float f_MAXIMUM_FLOAT = FLT_MAX;
    const float f_MINIMUM_FLOAT = FLT_MIN;
    const float f_XX_INITIAL_VALUE = (float)(0.70710678);
    const float f_COSR_INITIAL_VALUE = (float)(-0.069756474);
    const float f_SINR_INITIAL_VALUE = (float)(0.99756405);
}
PolynomialRootFinder::PolynomialRootFinder()
{
}
PolynomialRootFinder::RootStatus_T PolynomialRootFinder::FindRoots(
                                       double * coefficient_vector_ptr,
                                       int degree,
                                       double * real_zero_vector_ptr,
                                       double * imaginary_zero_vector_ptr,
                                       int * number_of_roots_found_ptr)
{

    PolynomialRootFinder::RootStatus_T status;

    if (degree == 0)
    {
        status = PolynomialRootFinder::SCALAR_VALUE_HAS_NO_ROOTS;
    }
    else if (coefficient_vector_ptr[degree] == 0.0)
    {
        status = PolynomialRootFinder::LEADING_COEFFICIENT_IS_ZERO;
    }
    else
    {


        m_degree = degree;

        std::vector<double> temp_vector;
        std::vector<PRF_Float_T> pt_vector;

        m_p_vector.resize(m_degree + 1);
        m_qp_vector.resize(m_degree + 1);
        m_k_vector.resize(m_degree + 1);
        m_qk_vector.resize(m_degree + 1);
        m_svk_vector.resize(m_degree + 1);
        temp_vector.resize(m_degree + 1);
        pt_vector.resize(m_degree + 1);

        m_p_vector_ptr = &m_p_vector[0];
        m_qp_vector_ptr = &m_qp_vector[0];
        m_k_vector_ptr = &m_k_vector[0];
        m_qk_vector_ptr = &m_qk_vector[0];
        m_svk_vector_ptr = &m_svk_vector[0];
        double * temp_vector_ptr = &temp_vector[0];
        PRF_Float_T * pt_vector_ptr = &pt_vector[0];


        m_are = f_ETA;
        m_mre = f_ETA;
        PRF_Float_T lo = f_MINIMUM_FLOAT / f_ETA;



        PRF_Float_T xx = f_XX_INITIAL_VALUE;
        PRF_Float_T yy = - xx;
        PRF_Float_T cosr = f_COSR_INITIAL_VALUE;
        PRF_Float_T sinr = f_SINR_INITIAL_VALUE;
        m_n = m_degree;
        m_n_plus_one = m_n + 1;



        int ii = 0;

        for (ii = 0; ii < m_n_plus_one; ++ii)
        {
            m_p_vector_ptr[m_n - ii] = coefficient_vector_ptr[ii];
        }




        status = PolynomialRootFinder::FAILED_TO_CONVERGE;




        int jvar = 0;

        while (m_p_vector_ptr[m_n] == 0.0)
        {
            jvar = m_degree - m_n;
            real_zero_vector_ptr[jvar] = 0.0;
            imaginary_zero_vector_ptr[jvar] = 0.0;
            m_n_plus_one = m_n_plus_one - 1;
            m_n = m_n - 1;
        }



        int count = 0;

        for (count = 0; count < m_degree; ++count)
        {



            if (m_n <= 2)
            {
                if (m_n > 0)
                {


                    if (m_n == 1)
                    {
                        real_zero_vector_ptr[m_degree - 1] =
                            - m_p_vector_ptr[1] / m_p_vector_ptr[0];

                        imaginary_zero_vector_ptr[m_degree - 1] = 0.0;
                    }
                    else
                    {
                        SolveQuadraticEquation(
                            m_p_vector_ptr[0],
                            m_p_vector_ptr[1],
                            m_p_vector_ptr[2],
                            real_zero_vector_ptr[m_degree - 2],
                            imaginary_zero_vector_ptr[m_degree - 2],
                            real_zero_vector_ptr[m_degree - 1],
                            imaginary_zero_vector_ptr[m_degree - 1]);
                    }
                }

                m_n = 0;
                status = PolynomialRootFinder::SUCCESS;
                break;
            }
            else
            {



                PRF_Float_T max = 0.0;
                PRF_Float_T min = f_MAXIMUM_FLOAT;
                PRF_Float_T xvar;

                for (ii = 0; ii < m_n_plus_one; ++ii)
                {
                    xvar = (PRF_Float_T)(::fabs((PRF_Float_T)(m_p_vector_ptr[ii])));

                    if (xvar > max)
                    {
                        max = xvar;
                    }

                    if ((xvar != 0.0) && (xvar < min))
                    {
                        min = xvar;
                    }
                }



                bool do_scaling_flag = false;
                PRF_Float_T sc = lo / min;

                if (sc <= 1.0)
                {
                    do_scaling_flag = f_MAXIMUM_FLOAT / sc < max;
                }
                else
                {
                    do_scaling_flag = max < 10.0;

                    if (! do_scaling_flag)
                    {
                        if (sc == 0.0)
                        {
                            sc = f_MINIMUM_FLOAT;
                        }
                    }
                }




                if (do_scaling_flag)
                {
                    int lvar = (int)(::log(sc) / ::log(f_BASE) + 0.5);
                    double factor = ::pow((double)(f_BASE * 1.0), double(lvar));

                    if (factor != 1.0)
                    {
                        for (ii = 0; ii < m_n_plus_one; ++ii)
                        {
                            m_p_vector_ptr[ii] = factor * m_p_vector_ptr[ii];
                        }
                    }
                }



                for (ii = 0; ii < m_n_plus_one; ++ii)
                {
                     pt_vector_ptr[ii] = (PRF_Float_T)(::fabs((PRF_Float_T)(m_p_vector_ptr[ii])));
                }

                pt_vector_ptr[m_n] = - pt_vector_ptr[m_n];



                xvar = (PRF_Float_T)
                    (::exp((::log(- pt_vector_ptr[m_n]) - ::log(pt_vector_ptr[0]))
                        / (PRF_Float_T)(m_n)));




                PRF_Float_T xm;

                if (pt_vector_ptr[m_n - 1] != 0.0)
                {
                    xm = - pt_vector_ptr[m_n] / pt_vector_ptr[m_n - 1];

                    if (xm < xvar)
                    {
                        xvar = xm;
                    }
                }




                PRF_Float_T ff;

                while (true)
                {
                    xm = (PRF_Float_T)(xvar * 0.1);
                    ff = pt_vector_ptr[0];

                    for (ii = 1; ii < m_n_plus_one; ++ii)
                    {
                        ff = ff * xm + pt_vector_ptr[ii];
                    }

                    if (ff <= 0.0)
                    {
                        break;
                    }

                    xvar = xm;
                }

                PRF_Float_T dx = xvar;



                while (true)
                {
                    if ((PRF_Float_T)(::fabs(dx / xvar)) <= 0.005)
                    {
                        break;
                    }

                    ff = pt_vector_ptr[0];
                    PRF_Float_T df = ff;

                    for (ii = 1; ii < m_n; ++ii)
                    {
                        ff = ff * xvar + pt_vector_ptr[ii];
                        df = df * xvar + ff;
                    }

                    ff = ff * xvar + pt_vector_ptr[m_n];
                    dx = ff / df;
                    xvar = xvar - dx;
                }

                PRF_Float_T bnd = xvar;



                int n_minus_one = m_n - 1;

                for (ii = 1; ii < m_n; ++ii)
                {
                    m_k_vector_ptr[ii] =
                        (PRF_Float_T)(m_n - ii) * m_p_vector_ptr[ii] / (PRF_Float_T)(m_n);
                }

                m_k_vector_ptr[0] = m_p_vector_ptr[0];
                double aa = m_p_vector_ptr[m_n];
                double bb = m_p_vector_ptr[m_n - 1];
                bool zerok_flag = m_k_vector_ptr[m_n - 1] == 0.0;

                int jj = 0;

                for (jj = 1; jj <= 5; ++jj)
                {
                    double cc = m_k_vector_ptr[m_n - 1];

                    if (zerok_flag)
                    {


                        for (jvar = n_minus_one; jvar > 0; --jvar)
                        {
                            m_k_vector_ptr[jvar] = m_k_vector_ptr[jvar - 1];
                        }

                        m_k_vector_ptr[0] = 0.0;
                        zerok_flag = m_k_vector_ptr[m_n - 1] == 0.0;
                    }
                    else
                    {



                        double tvar = - aa / cc;

                        for (jvar = n_minus_one; jvar > 0; --jvar)
                        {
                            m_k_vector_ptr[jvar] =
                                tvar * m_k_vector_ptr[jvar - 1] + m_p_vector_ptr[jvar];
                        }

                        m_k_vector_ptr[0] = m_p_vector_ptr[0];
                        zerok_flag =
                            ::fabs(m_k_vector_ptr[m_n - 1]) <= ::fabs(bb) * f_ETA_N;
                    }
                }



                for (ii = 0; ii < m_n; ++ii)
                {
                    temp_vector_ptr[ii] = m_k_vector_ptr[ii];
                }


                int cnt = 0;

                for (cnt = 1; cnt <= 20; ++cnt)
                {


                    PRF_Float_T xxx = cosr * xx - sinr * yy;
                    yy = sinr * xx + cosr * yy;
                    xx = xxx;
                    m_real_s = bnd * xx;
                    m_imag_s = bnd * yy;
                    m_u = - 2.0 * m_real_s;
                    m_v = bnd;


                    int nz = Fxshfr(20 * cnt);

                    if (nz != 0)
                    {


                        jvar = m_degree - m_n;
                        real_zero_vector_ptr[jvar] = m_real_sz;
                        imaginary_zero_vector_ptr[jvar] = m_imag_sz;
                        m_n_plus_one = m_n_plus_one - nz;
                        m_n = m_n_plus_one - 1;

                        for (ii = 0; ii < m_n_plus_one; ++ii)
                        {
                            m_p_vector_ptr[ii] = m_qp_vector_ptr[ii];
                        }

                        if (nz != 1)
                        {
                            real_zero_vector_ptr[jvar + 1 ] = m_real_lz;
                            imaginary_zero_vector_ptr[jvar + 1] = m_imag_lz;
                        }

                        break;


                    }

                    for (ii = 0; ii < m_n; ++ii)
                    {
                        m_k_vector_ptr[ii] = temp_vector_ptr[ii];
                    }
                }
            }
        }


        if (number_of_roots_found_ptr != 0)
        {
            *number_of_roots_found_ptr = m_degree - m_n;
        }
    }

    return status;
}
int PolynomialRootFinder::Fxshfr(int l2var)
{
    //------------------------------------------------------------------

    //  Evaluate polynomial by synthetic division.

    //------------------------------------------------------------------


    QuadraticSyntheticDivision(m_n_plus_one,
                               m_u,
                               m_v,
                               m_p_vector_ptr,
                               m_qp_vector_ptr,
                               m_a,
                               m_b);

    int itype = CalcSc();

    int nz = 0;
    float betav = 0.25;
    float betas = 0.25;
    float oss = (float)(m_real_s);
    float ovv = (float)(m_v);
    float ots;
    float otv;
    double ui;
    double vi;
    double svar;

    int jvar = 0;

    for (jvar = 1; jvar <= l2var; ++jvar)
    {
        //--------------------------------------------------------------

        //  Calculate next m_k_vector_ptr polynomial and estimate m_v.

        //--------------------------------------------------------------


        NextK(itype);
        itype = CalcSc();
        Newest(itype, ui, vi);
        float vv = (float)(vi);

        //--------------------------------------------------------------

        //  Estimate svar

        //--------------------------------------------------------------


        float ss = 0.0;

        if (m_k_vector_ptr[m_n - 1] != 0.0)
        {
            ss = (float)(- m_p_vector_ptr[m_n] / m_k_vector_ptr[m_n - 1]);
        }

        float tv = 1.0;
        float ts = 1.0;

        if ((jvar != 1) && (itype != 3))
        {
            //----------------------------------------------------------

            //  Compute relative measures of convergence of

            //  svar and m_v sequences.

            //----------------------------------------------------------


            if (vv != 0.0)
            {
                tv = (float)(::fabs((vv - ovv) / vv));
            }

            if (ss != 0.0)
            {
                ts = (float)(::fabs((ss - oss) / ss));
            }

            //----------------------------------------------------------

            //  If decreasing, multiply two most recent convergence

            //  measures.

            //----------------------------------------------------------


            float tvv = 1.0;

            if (tv < otv)
            {
                tvv = tv * otv;
            }

            float tss = 1.0;

            if (ts < ots)
            {
                tss = ts * ots;
            }

            //----------------------------------------------------------

            //  Compare with convergence criteria.

            //----------------------------------------------------------


            bool vpass_flag = tvv < betav;
            bool spass_flag = tss < betas;

            if (spass_flag || vpass_flag)
            {
                //------------------------------------------------------

                //  At least one sequence has passed the convergence

                //  test. Store variables before iterating.

                //------------------------------------------------------


                double svu = m_u;
                double svv = m_v;
                int ii = 0;

                for (ii = 0; ii < m_n; ++ii)
                {
                    m_svk_vector_ptr[ii] = m_k_vector_ptr[ii];
                }

                svar = ss;

                //------------------------------------------------------

                //  Choose iteration according to the fastest

                //  converging sequence.

                //------------------------------------------------------


                bool vtry_flag = false;
                bool stry_flag = false;
                bool exit_outer_loop_flag = false;

                bool start_with_real_iteration_flag =
                    (spass_flag && ((! vpass_flag) || (tss < tvv)));

                do
                {
                    if (! start_with_real_iteration_flag)
                    {
                        nz = QuadraticIteration(ui, vi);

                        if (nz > 0)
                        {
                            exit_outer_loop_flag = true;
                            break;
                        }

                        //----------------------------------------------

                        //  Quadratic iteration has failed. flag

                        //  that it has been tried and decrease

                        //  the convergence criterion.

                        //----------------------------------------------


                        vtry_flag = true;
                        betav = (float)(betav * 0.25);
                    }

                    //--------------------------------------------------

                    //  Try linear iteration if it has not been

                    //  tried and the svar sequence is converging.

                    //--------------------------------------------------


                    if (((! stry_flag) && spass_flag)
                        || start_with_real_iteration_flag)
                    {
                        if (! start_with_real_iteration_flag)
                        {
                            for (ii = 0; ii < m_n; ++ii)
                            {
                                m_k_vector_ptr[ii] = m_svk_vector_ptr[ii];
                            }
                        }
                        else
                        {
                            start_with_real_iteration_flag = false;
                        }

                        int iflag = 0;

                        nz = RealIteration(svar, iflag);

                        if (nz > 0)
                        {
                            exit_outer_loop_flag = true;
                            break;
                        }

                        //----------------------------------------------

                        //  Linear iteration has failed. Flag that

                        //  it has been tried and decrease the

                        //  convergence criterion.

                        //----------------------------------------------


                        stry_flag = true;
                        betas = (float)(betas * 0.25);

                        if (iflag != 0)
                        {
                            //------------------------------------------

                            //  If linear iteration signals an almost

                            //  double real zero attempt quadratic

                            //  iteration.

                            //------------------------------------------


                            ui = - (svar + svar);
                            vi = svar * svar;

                            continue;
                        }
                    }

                    //--------------------------------------------------

                    //  Restore variables

                    //--------------------------------------------------


                    m_u = svu;
                    m_v = svv;

                    for (ii = 0; ii < m_n; ++ii)
                    {
                        m_k_vector_ptr[ii] = m_svk_vector_ptr[ii];
                    }

                    //----------------------------------------------

                    //  Try quadratic iteration if it has not been

                    //  tried and the m_v sequence is converging.

                    //----------------------------------------------

                }
                while (vpass_flag && (! vtry_flag));

                if (exit_outer_loop_flag)
                {
                    break;
                }

                //------------------------------------------------------

                //  Recompute m_qp_vector_ptr and scalar values to

                //  continue the second stage.

                //------------------------------------------------------


                QuadraticSyntheticDivision(m_n_plus_one,
                                           m_u,
                                           m_v,
                                           m_p_vector_ptr,
                                           m_qp_vector_ptr,
                                           m_a,
                                           m_b);

                itype = CalcSc();
            }
        }

        ovv = vv;
        oss = ss;
        otv = tv;
        ots = ts;
    }

    return nz;
}
int PolynomialRootFinder::QuadraticIteration(double uu, double vv)
{
    //------------------------------------------------------------------

    //  Main loop

    //------------------------------------------------------------------


    double ui = 0.0;
    double vi = 0.0;
    float omp = 0.0F;
    float relstp = 0.0F;
    int itype = 0;
    bool tried_flag = false;
    int jvar = 0;
    int nz = 0;
    m_u = uu;
    m_v = vv;

    while (true)
    {
        SolveQuadraticEquation(1.0,
                               m_u,
                               m_v,
                               m_real_sz,
                               m_imag_sz,
                               m_real_lz,
                               m_imag_lz);

        //--------------------------------------------------------------

        //  Return if roots of the quadratic are real and not close

        //  to multiple or nearly equal and  of opposite sign.

        //--------------------------------------------------------------


        if (::fabs(::fabs(m_real_sz) - ::fabs(m_real_lz)) > 0.01 * ::fabs(m_real_lz))
        {
            break;
        }

        //--------------------------------------------------------------

        //  Evaluate polynomial by quadratic synthetic division.

        //------------------------------------------------------------------


        QuadraticSyntheticDivision(m_n_plus_one,
                                   m_u,
                                   m_v,
                                   m_p_vector_ptr,
                                   m_qp_vector_ptr,
                                   m_a,
                                   m_b);

        float mp = (float)(::fabs(m_a - m_real_sz * m_b) + ::fabs(m_imag_sz * m_b));

        //--------------------------------------------------------------

        //  Compute a rigorous  bound on the rounding error in

        //  evaluting m_p_vector_ptr.

        //--------------------------------------------------------------


        float zm = (float)(::sqrt((float)(::fabs((float)(m_v)))));
        float ee = (float)(2.0 * (float)(::fabs((float)(m_qp_vector_ptr[0]))));
        float tvar = (float)(- m_real_sz * m_b);
        int ii = 0;

        for (ii = 1; ii < m_n; ++ii)
        {
            ee = ee * zm + (float)(::fabs((float)(m_qp_vector_ptr[ii])));
        }

        ee = ee * zm + (float)(::fabs((float)(m_a) + tvar));
        ee = (float)((5.0 * m_mre + 4.0 * m_are) * ee
            - (5.0 * m_mre + 2.0 * m_are) * ((float)(::fabs((float)(m_a) + tvar)) + (float)(::fabs((float)(m_b))) * zm)
                + 2.0 * m_are * (float)(::fabs(tvar)));

        //--------------------------------------------------------------

        //  Iteration has converged sufficiently if the polynomial

        //  value is less than 20 times this bound.

        //--------------------------------------------------------------


        if (mp <= 20.0 * ee)
        {
            nz = 2;
            break;
        }

        jvar = jvar + 1;

        //--------------------------------------------------------------

        //  Stop iteration after 20 steps.

        //--------------------------------------------------------------


        if (jvar > 20)
        {
            break;
        }

        if ((jvar >= 2) && ((relstp <= 0.01)
            && (mp >= omp) && (! tried_flag)))
        {
            //----------------------------------------------------------

            //  A cluster appears to be stalling the convergence.

            //  Five fixed shift steps are taken with a m_u, m_v

            //  close to the cluster.

            //----------------------------------------------------------


            if (relstp < f_ETA)
            {
                relstp = f_ETA;
            }

            relstp = (float)(::sqrt(relstp));
            m_u = m_u - m_u * relstp;
            m_v = m_v + m_v * relstp;

            QuadraticSyntheticDivision(m_n_plus_one,
                                       m_u,
                                       m_v,
                                       m_p_vector_ptr,
                                       m_qp_vector_ptr,
                                       m_a,
                                       m_b);

            for (ii = 0; ii < 5; ++ii)
            {
                itype = CalcSc();
                NextK(itype);
            }

            tried_flag = true;
            jvar = 0;
        }

        omp = mp;

        //--------------------------------------------------------------

        //  Calculate next m_k_vector_ptr polynomial and

        //  new m_u and m_v.

        //--------------------------------------------------------------


        itype = CalcSc();
        NextK(itype);
        itype = CalcSc();
        Newest(itype, ui, vi);

        //--------------------------------------------------------------

        //  If vi is zero the iteration is not converging.

        //--------------------------------------------------------------


        if (vi == 0.0)
        {
            break;
        }

        relstp = (float)(::fabs((vi - m_v) / vi));
        m_u = ui;
        m_v = vi;
    }

    return nz;
}

int PolynomialRootFinder::RealIteration(double & sss, int & flag)
{
    //------------------------------------------------------------------

    //  Main loop

    //------------------------------------------------------------------


    double tvar = 0.0;
    float omp = 0.0F;
    int nz = 0;
    flag = 0;
    int jvar = 0;
    double svar = sss;

    while (true)
    {
        double pv = m_p_vector_ptr[0];

        //--------------------------------------------------------------

        //  Evaluate m_p_vector_ptr at svar

        //--------------------------------------------------------------


        m_qp_vector_ptr[0] = pv;
        int ii = 0;

        for (ii = 1; ii < m_n_plus_one; ++ii)
        {
            pv = pv * svar + m_p_vector_ptr[ii];
            m_qp_vector_ptr[ii] = pv;
        }

        float mp = (float)(::fabs(pv));

        //--------------------------------------------------------------

        //  Compute a rigorous bound on the error in evaluating p

        //--------------------------------------------------------------


        PRF_Float_T ms = (PRF_Float_T)(::fabs(svar));
        PRF_Float_T ee = (m_mre / (m_are + m_mre)) * (PRF_Float_T)(::fabs((PRF_Float_T)(m_qp_vector_ptr[0])));

        for (ii = 1; ii < m_n_plus_one; ++ii)
        {
            ee = ee * ms + (float)(::fabs((PRF_Float_T)(m_qp_vector_ptr[ii])));
        }

        //--------------------------------------------------------------

        //  Iteration has converged sufficiently if the

        //  polynomial value is less than 20 times this bound.

        //--------------------------------------------------------------


        if (mp <= 20.0 * ((m_are + m_mre) * ee - m_mre * mp))
        {
            nz = 1;
            m_real_sz = svar;
            m_imag_sz = 0.0;
            break;
        }

        jvar = jvar + 1;

        //--------------------------------------------------------------

        //  Stop iteration after 10 steps.

        //--------------------------------------------------------------


        if (jvar > 10)
        {
            break;
        }

        if ((jvar >= 2)
            && ((::fabs(tvar) <= 0.001 * ::fabs(svar - tvar))
            && (mp > omp)))
        {
            //----------------------------------------------------------

            //  A cluster of zeros near the real axis has been

            //  encountered. Return with flag set to initiate

            //  a quadratic iteration.

            //----------------------------------------------------------


            flag = 1;
            sss = svar;
            break;
        }

        //--------------------------------------------------------------

        //  Return if the polynomial value has increased significantly.

        //--------------------------------------------------------------


        omp = mp;

        //--------------------------------------------------------------

        //  Compute t, the next polynomial, and the new iterate.

        //--------------------------------------------------------------


        double kv = m_k_vector_ptr[0];
        m_qk_vector_ptr[0] = kv;

        for (ii = 1; ii < m_n; ++ii)
        {
            kv = kv * svar + m_k_vector_ptr[ii];
            m_qk_vector_ptr[ii] = kv;
        }

        if (::fabs(kv) <= ::fabs(m_k_vector_ptr[m_n - 1]) * f_ETA_N)
        {
            m_k_vector_ptr[0] = 0.0;

            for (ii = 1; ii < m_n; ++ii)
            {
                m_k_vector_ptr[ii] = m_qk_vector_ptr[ii - 1];
            }
        }
        else
        {
            //----------------------------------------------------------

            //  Use the scaled form of the recurrence if the

            //  value of m_k_vector_ptr at svar is non-zero.

            //----------------------------------------------------------


            tvar = - pv / kv;
            m_k_vector_ptr[0] = m_qp_vector_ptr[0];

            for (ii = 1; ii < m_n; ++ii)
            {
                m_k_vector_ptr[ii] = tvar * m_qk_vector_ptr[ii - 1] + m_qp_vector_ptr[ii];
            }
        }

        //--------------------------------------------------------------

        //  Use unscaled form.

        //--------------------------------------------------------------


        kv = m_k_vector_ptr[0];

        for (ii = 1; ii < m_n; ++ii)
        {
            kv = kv * svar + m_k_vector_ptr[ii];
        }

        tvar = 0.0;

        if (::fabs(kv) > ::fabs(m_k_vector_ptr[m_n - 1]) * f_ETA_N)
        {
            tvar = - pv / kv;
        }

        svar = svar + tvar;
    }

    return nz;
}

int PolynomialRootFinder::CalcSc()
{
    //------------------------------------------------------------------

    //  Synthetic division of m_k_vector_ptr by the quadratic 1, m_u, m_v.

    //------------------------------------------------------------------


    QuadraticSyntheticDivision(m_n,
                               m_u,
                               m_v,
                               m_k_vector_ptr,
                               m_qk_vector_ptr,
                               m_c,
                               m_d);

    int itype = 0;

    if ((::fabs(m_c) <= ::fabs(m_k_vector_ptr[m_n - 1]) * f_ETA_N_SQUARED)
        && (::fabs(m_d) <= ::fabs(m_k_vector_ptr[m_n - 2]) * f_ETA_N_SQUARED))
    {
        //--------------------------------------------------------------

        //  itype == 3 Indicates the quadratic is almost a

        //  factor of m_k_vector_ptr.

        //--------------------------------------------------------------


        itype = 3;
    }
    else if (::fabs(m_d) >= ::fabs(m_c))
    {
        //--------------------------------------------------------------

        //  itype == 2 Indicates that all formulas are divided by m_d.

        //--------------------------------------------------------------


        itype = 2;
        m_e = m_a / m_d;
        m_f = m_c / m_d;
        m_g = m_u * m_b;
        m_h = m_v * m_b;
        m_a3 = (m_a + m_g) * m_e + m_h * (m_b / m_d);
        m_a1 = m_b * m_f - m_a;
        m_a7 = (m_f + m_u) * m_a + m_h;
    }
    else
    {
        //--------------------------------------------------------------

        //  itype == 1 Indicates that all formulas are divided by m_c.

        //--------------------------------------------------------------


        itype = 1;
        m_e = m_a / m_c;
        m_f = m_d / m_c;
        m_g = m_u * m_e;
        m_h = m_v * m_b;
        m_a3 = m_a * m_e + (m_h / m_c + m_g) * m_b;
        m_a1 = m_b - m_a * (m_d / m_c);
        m_a7 = m_a + m_g * m_d + m_h * m_f;
    }

    return itype;
}
void PolynomialRootFinder::NextK(int itype)
{
    int ii = 0;

    if (itype == 3)
    {
        //--------------------------------------------------------------

        //  Use unscaled form of the recurrence if type is 3.

        //--------------------------------------------------------------


        m_k_vector_ptr[0] = 0.0;
        m_k_vector_ptr[1] = 0.0;

        for (ii = 2; ii < m_n; ++ii)
        {
            m_k_vector_ptr[ii] = m_qk_vector_ptr[ii - 2];
        }
    }
    else
    {
        double temp = m_a;

        if (itype == 1)
        {
            temp = m_b;
        }

        if (::fabs(m_a1) <= ::fabs(temp) * f_ETA_N)
        {
            //----------------------------------------------------------

            //  If m_a1 is nearly zero then use a special form of

            //  the recurrence.

            //----------------------------------------------------------


            m_k_vector_ptr[0] = 0.0;
            m_k_vector_ptr[1] = - m_a7 * m_qp_vector_ptr[0];

            for (ii = 2; ii < m_n; ++ii)
            {
                m_k_vector_ptr[ii] = m_a3 * m_qk_vector_ptr[ii - 2] - m_a7 * m_qp_vector_ptr[ii - 1];
            }
        }
        else
        {
            //----------------------------------------------------------

            //  Use scaled form of the recurrence.

            //----------------------------------------------------------


            m_a7 = m_a7 / m_a1;
            m_a3 = m_a3 / m_a1;
            m_k_vector_ptr[0] = m_qp_vector_ptr[0];
            m_k_vector_ptr[1] = m_qp_vector_ptr[1] - m_a7 * m_qp_vector_ptr[0];

            for (ii = 2; ii < m_n; ++ii)
            {
                m_k_vector_ptr[ii] =
                    m_a3 * m_qk_vector_ptr[ii - 2] - m_a7 * m_qp_vector_ptr[ii - 1] + m_qp_vector_ptr[ii];
            }
        }
    }

    return;
}
void PolynomialRootFinder::Newest(int itype, double & uu, double & vv)
{
    //------------------------------------------------------------------

    //  Use formulas appropriate to setting of itype.

    //------------------------------------------------------------------


    if (itype == 3)
    {
        //--------------------------------------------------------------

        //  If itype == 3 the quadratic is zeroed.

        //--------------------------------------------------------------


        uu = 0.0;
        vv = 0.0;
    }
    else
    {
        double a4;
        double a5;

        if (itype == 2)
        {
            a4 = (m_a + m_g) * m_f + m_h;
            a5 = (m_f + m_u) * m_c + m_v * m_d;
        }
        else
        {
            a4 = m_a + m_u * m_b + m_h * m_f;
            a5 = m_c + (m_u + m_v * m_f) * m_d;
        }

        //--------------------------------------------------------------

        //  Evaluate new quadratic coefficients.

        //--------------------------------------------------------------


        double b1 = - m_k_vector_ptr[m_n - 1] / m_p_vector_ptr[m_n];
        double b2 = - (m_k_vector_ptr[m_n - 2] + b1 * m_p_vector_ptr[m_n - 1]) / m_p_vector_ptr[m_n];
        double c1 = m_v * b2 * m_a1;
        double c2 = b1 * m_a7;
        double c3 = b1 * b1 * m_a3;
        double c4 = c1 - c2 - c3;
        double temp = a5 + b1 * a4 - c4;

        if (temp != 0.0)
        {
            uu = m_u - (m_u * (c3 + c2) + m_v * (b1 * m_a1 + b2 * m_a7)) / temp;
            vv = m_v * (1.0 + c4 / temp);
        }
    }

    return;
}
void PolynomialRootFinder::QuadraticSyntheticDivision(int n_plus_one,
                                                      double u,
                                                      double v,
                                                      double * p_ptr,
                                                      double * q_ptr,
                                                      double & a,
                                                      double & b)
{
    b = p_ptr[0];
    q_ptr[0] = b;
    a = p_ptr[1] - u * b;
    q_ptr[1] = a;

    int ii = 0;

    for (ii = 2; ii < n_plus_one; ++ii)
    {
        double c = p_ptr[ii] - u * a - v * b;
        q_ptr[ii] = c;
        b = a;
        a = c;
    }

    return;
}
void PolynomialRootFinder::SolveQuadraticEquation(double a,
                                                  double b,
                                                  double c,
                                                  double & sr,
                                                  double & si,
                                                  double & lr,
                                                  double & li)
{
    if (a == 0.0)
    {
        if (b != 0.0)
        {
            sr = - c / b;
        }
        else
        {
            sr = 0.0;
        }

        lr = 0.0;
        si = 0.0;
        li = 0.0;
    }
    else if (c == 0.0)
    {
        sr = 0.0;
        lr = - b / a;
        si = 0.0;
        li = 0.0;
    }
    else
    {
        //--------------------------------------------------------------

        //  Compute discriminant avoiding overflow.

        //--------------------------------------------------------------


        double d;
        double e;
        double bvar = b / 2.0;

        if (::fabs(bvar) < ::fabs(c))
        {
            if (c < 0.0)
            {
                e = - a;
            }
            else
            {
                e = a;
            }

            e = bvar * (bvar / ::fabs(c)) - e;

            d = ::sqrt(::fabs(e)) * ::sqrt(::fabs(c));
        }
        else
        {
            e = 1.0 - (a / bvar) * (c / bvar);
            d = ::sqrt(::fabs(e)) * ::fabs(bvar);
        }

        if (e >= 0.0)
        {
            //----------------------------------------------------------

            //  Real zeros

            //----------------------------------------------------------


            if (bvar >= 0.0)
            {
                d = - d;
            }

            lr = (- bvar + d) / a;
            sr = 0.0;

            if (lr != 0.0)
            {
                sr = (c / lr) / a;
            }

            si = 0.0;
            li = 0.0;
        }
        else
        {
            //----------------------------------------------------------

            //  Complex conjugate zeros

            //----------------------------------------------------------


            sr = - bvar / a;
            lr = sr;
            si = ::fabs(d / a);
            li = - si;
        }
    }

    return;
}
