/******************************************************************************/
/** Algorithms to calculate linear Equation                                  **/
/** developed , collected and / or implemented by                            **/
/** Danny Schneider, 2017-2021                                               **/
/******************************************************************************/

#ifndef LINEAR_EQUATION_H
#define LINEAR_EQUATION_H

/**
 * https://wordsandbuttons.online/vastly_outperforming_lapack_with_cpp_metaprogramming.html
 */

#include <array>

namespace Math{

namespace linear_equations{

  template <int I, int J, int K, int N> constexpr static double aij(const std::array<std::array<double, N>, N>& a){
    if(K == N) return a[I][J];
    return aij<I, J, K+(K<N), N>(a) * aij<K, K, K+(K<N), N>(a)
      - aij<I, K, K+(K<N), N>(a) * aij<K, J, K+(K<N), N>(a);
  }

  template <int I, int K, int N> constexpr static double bi(
    const std::array<std::array<double, N>, N>& a,
    const std::array<double, N>& b){
    if(K == N) return b[I];
    return aij<K, K, K+(K<N), N>(a) * bi<I, K+(K<N), N>(a, b)
      - aij<I, K, K+(K<N), N>(a) * bi<K, K+(K<N), N>(a, b);
  }

  template <int J, int I, int N> constexpr static void d_for(
    double& d,
    const std::array<std::array<double, N>, N>& a,
    std::array<double, N>& x){
    if(J < I){
      d -= aij<I, J, I+(J<I), N>(a) * x[J];
      d_for<J+(J<I), I, N>(d, a, x);
    }
  }

  template <int I, int N> constexpr static double di(
    const std::array<std::array<double, N>, N>& a,
    const std::array<double, N>& b,
    std::array<double, N>& x){
    double d = bi<I, I+1, N>(a, b);
    d_for<0, I, N>(d, a, x);
    return d;
  }

  template <int I, int N> constexpr static void x_for(
    const std::array<std::array<double, N>, N>& a,
    const std::array<double, N>& b,
    std::array<double, N>& x){
    if(I < N){
      double d = di<I, N>(a, b, x);
      double aiji = aij<I, I, I+1, N>(a);
      x[I] = d / aiji;
      x_for<I+(I<N), N>(a, b, x);
    }
  }

  template <int N> constexpr static void solve(
    const std::array<std::array<double, N>, N>& a,
    const std::array<double, N>& b,
    std::array<double, N>& x){
    x_for<0, N>(a, b, x);
  }

} //namespace

} //namespace

#endif // LINEAR_EQUATION_H


