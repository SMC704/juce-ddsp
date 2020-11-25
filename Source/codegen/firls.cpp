//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  firls.cpp
//
//  Code generation for function 'firls'
//


// Include files
#include "firls.h"
#include "additive.h"
#include "mldivide.h"
#include "rt_nonfinite.h"
#include "subtractive.h"
#include <cmath>
#include <cstring>

// Function Definitions
void firls(const double varargin_3[64], double h_data[], int h_size[2])
{
  int i;
  static double G_data[4225];
  signed char k_data[65];
  signed char b_k_data[65];
  int s;
  double b0;
  int I1_data_tmp;
  double b_data[66];
  unsigned char I1_data[4225];
  signed char I2_data[4225];
  double y_data[4096];
  double b0_data[66];
  double b_y_data[65];
  double c_y_data[65];
  static double tmp_data[4225];
  double b_tmp_data[4225];
  double c_tmp_data[4225];
  double d_tmp_data[4225];
  for (i = 0; i < 65; i++) {
    k_data[i] = static_cast<signed char>(i);
  }

  std::memset(&G_data[0], 0, 4225U * sizeof(double));
  for (i = 0; i < 65; i++) {
    for (s = 0; s < 65; s++) {
      I1_data_tmp = s + 65 * i;
      I1_data[I1_data_tmp] = static_cast<unsigned char>(static_cast<unsigned int>
        (k_data[s]) + i);
      I2_data[I1_data_tmp] = static_cast<signed char>(k_data[s] - i);
    }
  }

  std::memcpy(&b_k_data[0], &k_data[1], 64U * sizeof(signed char));
  std::memcpy(&k_data[0], &b_k_data[0], 64U * sizeof(signed char));
  b0 = 0.0;
  std::memset(&b_data[0], 0, 64U * sizeof(double));
  for (i = 0; i < 64; i++) {
    y_data[i] = 6.2831853071795862 * static_cast<double>(k_data[i]);
  }

  for (I1_data_tmp = 0; I1_data_tmp < 32; I1_data_tmp++) {
    double m_s_tmp;
    double m_s_tmp_tmp;
    double b_m_s_tmp;
    double m_s;
    double b1_tmp;
    double b1;
    double a;
    s = I1_data_tmp << 1;
    m_s_tmp = 0.0079365079365079361 * static_cast<double>(s);
    m_s_tmp_tmp = 0.0079365079365079361 * (static_cast<double>(s) + 1.0);
    b_m_s_tmp = m_s_tmp_tmp - m_s_tmp;
    m_s = (varargin_3[s + 1] - varargin_3[s]) / b_m_s_tmp;
    b1_tmp = m_s * m_s_tmp;
    b1 = varargin_3[s] - b1_tmp;
    b0 += b1 * b_m_s_tmp + m_s / 2.0 * (m_s_tmp_tmp * m_s_tmp_tmp - m_s_tmp *
      m_s_tmp);
    for (i = 0; i < 64; i++) {
      b_y_data[i] = y_data[i] * m_s_tmp_tmp;
    }

    for (s = 0; s < 64; s++) {
      b_y_data[s] = std::cos(b_y_data[s]);
    }

    for (i = 0; i < 64; i++) {
      c_y_data[i] = y_data[i] * m_s_tmp;
    }

    for (s = 0; s < 64; s++) {
      c_y_data[s] = std::cos(c_y_data[s]);
    }

    a = m_s / 39.478417604357432;
    for (i = 0; i < 64; i++) {
      b_data[i] += a * (b_y_data[i] - c_y_data[i]) / static_cast<double>
        (k_data[i] * k_data[i]);
    }

    for (i = 0; i < 64; i++) {
      b_y_data[i] = 2.0 * static_cast<double>(k_data[i]) * m_s_tmp_tmp;
    }

    a = m_s_tmp_tmp * (m_s * m_s_tmp_tmp + b1);
    for (s = 0; s < 64; s++) {
      if (std::abs(b_y_data[s]) < 1.0020841800044864E-292) {
        b_y_data[s] = 1.0;
      } else {
        m_s = 3.1415926535897931 * b_y_data[s];
        m_s = std::sin(m_s) / m_s;
        b_y_data[s] = m_s;
      }
    }

    for (i = 0; i < 64; i++) {
      c_y_data[i] = 2.0 * static_cast<double>(k_data[i]) * m_s_tmp;
    }

    b_m_s_tmp = m_s_tmp * (b1_tmp + b1);
    for (s = 0; s < 64; s++) {
      if (std::abs(c_y_data[s]) < 1.0020841800044864E-292) {
        c_y_data[s] = 1.0;
      } else {
        m_s = 3.1415926535897931 * c_y_data[s];
        m_s = std::sin(m_s) / m_s;
        c_y_data[s] = m_s;
      }
    }

    for (i = 0; i < 64; i++) {
      b_data[i] += a * b_y_data[i] - b_m_s_tmp * c_y_data[i];
    }

    for (i = 0; i < 4225; i++) {
      tmp_data[i] = 2.0 * static_cast<double>(I1_data[i]) * m_s_tmp_tmp;
    }

    for (s = 0; s < 4225; s++) {
      if (std::abs(tmp_data[s]) < 1.0020841800044864E-292) {
        tmp_data[s] = 1.0;
      } else {
        m_s = 3.1415926535897931 * tmp_data[s];
        m_s = std::sin(m_s) / m_s;
        tmp_data[s] = m_s;
      }
    }

    for (i = 0; i < 4225; i++) {
      b_tmp_data[i] = 2.0 * static_cast<double>(I2_data[i]) * m_s_tmp_tmp;
    }

    for (s = 0; s < 4225; s++) {
      if (std::abs(b_tmp_data[s]) < 1.0020841800044864E-292) {
        b_tmp_data[s] = 1.0;
      } else {
        m_s = 3.1415926535897931 * b_tmp_data[s];
        m_s = std::sin(m_s) / m_s;
        b_tmp_data[s] = m_s;
      }
    }

    for (i = 0; i < 4225; i++) {
      c_tmp_data[i] = 2.0 * static_cast<double>(I1_data[i]) * m_s_tmp;
    }

    for (s = 0; s < 4225; s++) {
      if (std::abs(c_tmp_data[s]) < 1.0020841800044864E-292) {
        c_tmp_data[s] = 1.0;
      } else {
        m_s = 3.1415926535897931 * c_tmp_data[s];
        m_s = std::sin(m_s) / m_s;
        c_tmp_data[s] = m_s;
      }
    }

    for (i = 0; i < 4225; i++) {
      d_tmp_data[i] = 2.0 * static_cast<double>(I2_data[i]) * m_s_tmp;
    }

    a = 0.5 * m_s_tmp_tmp;
    b_m_s_tmp = 0.5 * m_s_tmp;
    for (s = 0; s < 4225; s++) {
      if (std::abs(d_tmp_data[s]) < 1.0020841800044864E-292) {
        m_s = 1.0;
        d_tmp_data[s] = 1.0;
      } else {
        m_s = 3.1415926535897931 * d_tmp_data[s];
        m_s = std::sin(m_s) / m_s;
        d_tmp_data[s] = m_s;
      }

      G_data[s] += a * (tmp_data[s] + b_tmp_data[s]) - b_m_s_tmp * (c_tmp_data[s]
        + m_s);
    }
  }

  b0_data[0] = b0;
  std::memcpy(&b0_data[1], &b_data[0], 64U * sizeof(double));
  std::memcpy(&b_data[0], &b0_data[0], 65U * sizeof(double));
  std::memcpy(&b_y_data[0], &b_data[0], 65U * sizeof(double));
  mldiv(G_data, b_y_data);
  h_size[0] = 1;
  h_size[1] = 129;
  h_data[64] = b_y_data[0];
  for (i = 0; i < 64; i++) {
    h_data[i] = b_y_data[64 - i] / 2.0;
    h_data[i + 65] = b_y_data[i + 1] / 2.0;
  }
}

// End of code generation (firls.cpp)
