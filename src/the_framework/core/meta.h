/*
 * Copyright 2017-2021,Danny Schneider
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef META_H
#define META_H

#include <iostream>
#include <limits>
#include <utility>
#include <initializer_list>
#include <type_traits>

#include "dtypes.h"
#include "compile_guards.h"


namespace Meta{

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

namespace Constants{

template<typename T> struct UINTMAX{
  constexpr void typecheck(){
    Compile::Guards::IsUnsigned<T>();
  }
  constexpr static T const value = ((((1ull<<((sizeof(T)<<3)-1))-1)<<1)|1);
};

template<typename T> struct TYPEBITS{
  constexpr static T const value = sizeof(T)<<3;
};

} //namespace Constants

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

namespace Varadic {

template<typename ...Args> constexpr auto sum(Args ...args){
  return (args + ...);
}//            ^~~~~ fold expression

//---

template<typename ...Args> constexpr void printf(Args&&... args){
  (std::cout << ... << std::forward<Args>(args)) << '\n';
  return;
}

//---

// compile-time endianness swap based on http://stackoverflow.com/a/36937049
template<typename T, std::size_t... N> constexpr T bswap_impl(T _i, std::index_sequence<N...>) {
  return ((((_i >> (N * Meta::Constants::TYPEBITS<u8>::value)) & T(Meta::Constants::UINTMAX<u8>::value)) <<
           ((sizeof(T)-1-N) * Meta::Constants::TYPEBITS<u8>::value)) | ...);
}; //                                                                ^~~~~ fold expression
template<typename T, typename U = std::make_unsigned_t<T>> constexpr U bswap(T _i){
  return bswap_impl<U>(static_cast<U>(_i), std::make_index_sequence<sizeof(T)>{});
}

//---

  /**
   * sum sizes of types in varadic template
   */
//template<std::size_t N, typename Ti, typename ...T> struct varadic_size;
  template<std::size_t N, typename Ti, typename ...T> struct varadic_size{
    constexpr static std::size_t const value = sizeof(Ti)+varadic_size<N-1,T...>::value;
  };

  //Terminate recursion
  template<typename Ti, typename ...T> struct varadic_size<0,Ti,T...>{
    constexpr static std::size_t const value = sizeof(Ti);
  };

//-----

  /**
   * Not really Metaprogramming but maybe usefull...
   * Print for all std:: containers...
   * https://eli.thegreenplace.net/2014/variadic-templates-in-c/
   */
  template <template <typename, typename...> class ContainerType,
            typename ValueType, typename... Args>
  constexpr void print_container(ContainerType<ValueType, Args...> const& c) {
    for (const auto& v : c) {
      std::cout << v << ' ';
    }
    std::cout << '\n';
    return;
  }

} //namespace Varadic

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

namespace Math {

namespace Convert {

template<typename FloatType, typename RT> constexpr RT sattFloatToInt(FloatType const num) {
  Compile::Guards::IsFloatType<FloatType>();
  Compile::Guards::IsInteger<RT>();
  RT res = static_cast<RT>(num); //Assume it is safe to cast
  //check if float fits into integer
  if ( std::numeric_limits<RT>::digits < std::numeric_limits<FloatType>::digits) {
    auto const max = std::numeric_limits<RT>::max();
    if(num > static_cast<FloatType>(max)) res = max;
    auto const min = std::numeric_limits<RT>::min();
    if(num < static_cast<FloatType>(min)) res = min;
  }
  return res;
}

} //namespace Convert

//----- Simple Math

template <typename T, T i, T j> struct Multiply {
  constexpr static T const value = i * j;
};

template <typename T, T x, T y> struct CeilDiv {
  constexpr static T const value = (x % y) ? x / y + 1 : x / y;
};

//----- quadratic square root

/**************************************************
 * https://www.c-plusplus.net/forum/topic/217911/template-meta-programmierung-quadratwurzel-use-of-undefined-type-error/3
 * https://de.wikipedia.org/wiki/Heron-Verfahren
 **************************************************/

namespace sqrt_detail {

template<typename T, uint8_t I, T A, T X0, T AX > struct HeronStep {
  static_assert(std::is_unsigned<T>(),"Type is not unsigned");
  constexpr static T const x1 = ((X0+AX)/2);
  constexpr static T const value = HeronStep<T, I-1, A, x1, (A/x1) >::value;
};

template<typename T, T A, T X0, T AX > struct HeronStep<T, 0, A, X0, AX > {
  static_assert(std::is_unsigned<T>(),"Type is not unsigned");
  constexpr static T const value = X0;
};

} //namespace sqrt_detail

template<typename T, T A > struct SquareRoot_Heron {
  static_assert(std::is_unsigned<T>(),"Type is not unsigned");
  constexpr static T const value = sqrt_detail::HeronStep<T, 5, A, 2, (A/2) >::value;
};

//----- fibonacci

/*template <typename T, typename U> struct X_;

template <typename T, T N> struct X_<T, std::integral_constant<T, N>> {};

template <typename T> struct X_<T, std::integral_constant<T, 0>> {};

template <typename T, T N> struct X : X_<T, std::integral_constant<T, N>> {};*/

namespace fibonacci_detail {

/**************************************************
 * https://en.wikipedia.org/w/index.php?title=Fibonacci_number&oldid=924288678
 **************************************************/

template<typename T, typename T2> struct Fibonacci_Step;

//recursive calculation of Fibonacci number
template<typename T, T X> struct Fibonacci_Step<T,std::integral_constant<T,X>> {
  constexpr static int const result = Fibonacci_Step<T,std::integral_constant<T,X-1>>::result + Fibonacci_Step<T,std::integral_constant<T,X-2>>::result;
};

//Specialisation "1" --> Terminating recursion
template<typename T> struct Fibonacci_Step<T,std::integral_constant<T,1>> {
  static const int result = T(1);
};

//Specialisation "2" --> Terminating recursion
template<typename T> struct Fibonacci_Step<T,std::integral_constant<T,2>> {
  static const int result = T(1);
};

} //namespace fibonacci_detail

//Caller for Calculation of an Fibonacci number
template<typename T, T X> struct Fibonacci {
  static_assert(std::is_unsigned<T>(),"Type is not unsigned");
  static_assert(X>2,"Parameter X too small");
  constexpr static int const result = fibonacci_detail::Fibonacci_Step<T,std::integral_constant<T,X-1>>::result + fibonacci_detail::Fibonacci_Step<T,std::integral_constant<T,X-2>>::result;
};

//-----

template <typename T> struct Discrete{
  constexpr void typecheck(){
    Compile::Guards::IsUnsigned<T>();
  }
  constexpr static T const allbitsset = ((((T(1)<<((sizeof(T)<<3)-1))-1)<<1)|1);

//----- isPrime

  constexpr static bool isPrime_R(T const _v, T _d){
    bool res = true;
    while(res && (_d > 1)){
      res = (0 != (_v/_d));
      --_d;
    }
    return true;
  }

  constexpr static bool isPrime(T const _v){
    return (4>_v)?(true):(
           (0==(_v%2))?(false):(
            isPrime_R(_v,(_v-1))));
  }
};

//----- Power x^y

//Recursive Calculation of M^N
template<u64 M, u64 N> struct POWER{
  constexpr static u64 const value = M * POWER<M,(N-1)>::value;
};

//Terminate recursion
template<u64 M> struct POWER<M,0>{
  constexpr static u64 const value = 1;
};

//----- Devision with Rounding upwards (towards Infinite)... normaly compilers round towards zero, at least if result is positive

template<typename T, T A, T B> struct CEILDIV{
  static_assert (B>0,"Divide by Zero is forbidden");
  constexpr static T const value = ((A+B-1)/B);
  //constexpr static T const value = ((A%B)>0)?((A/B)+1):(A/B);
};

//----- Logarithm to Base 2

template<u64 VAL> struct FLOOR_LOG2_Impl{
  constexpr static u8 value = 1 + FLOOR_LOG2_Impl<VAL/2>::value;
};
template<> struct FLOOR_LOG2_Impl<0>{
  constexpr static u8 value = 0;
};

template<u64 VAL> struct FLOOR_LOG2{
  constexpr static u8 value = (VAL>1)?(FLOOR_LOG2_Impl<VAL>::value-1):(0);
};

template<u64 VAL> struct CEIL_LOG2_Impl{
  constexpr static u8 value = 1 + CEIL_LOG2_Impl<((VAL+1)/2)>::value;
};
template<> struct CEIL_LOG2_Impl<1>{
  constexpr static u8 value = 0;
};
template<> struct CEIL_LOG2_Impl<0>{
  constexpr static u8 value = 0;
};

template<u64 VAL> struct CEIL_LOG2{
  constexpr static u8 value = (VAL>1)?(CEIL_LOG2_Impl<VAL>::value):(0);
};

} //namespace Math

//--------------------------------------------------

namespace DStruct {

/**
 * A compile Time "inteligent Array" which at least knows its number of Elements
 */
template <typename T, size_t N> struct Array {
  T storage[N];
  constexpr static const size_t size = N;
  constexpr T* data(){
    return &storage[0];
  }
};

} //namespace DStruct

//--------------------------------------------------

namespace Initialize {

// A class template that just a list of types:
template <class... T> struct typelist {
  //static size_t value = sizeof...(T...);
};

//-----

/*template <int I> struct squared {
  squared<I - 1> rest;
  static const int x = I * I ;
  constexpr int operator[](int const &i) const { return (i == I ?  x : rest[i]); }
  constexpr int size() const { return I; }
};

template <> struct squared<0> {
  static const int x = 0;
  constexpr int operator[](int const &i) const { return x; }
  constexpr int size() const { return 1; }
};*/

//-----

/*
template<typename T, T N> struct SqArr {
  static inline void fill(T arr[]) {
    arr[N-1] = (N-1)*(N-1);
    SqArr<T, N-1>::fill(arr);
  }
};

template<typename T> struct SqArr<0<T> > {
  static inline void fill(T arr[]) { }
};*/

//-----

namespace linspace_detail {

template<typename T, size_t RC, T S, T E, size_t C> struct linspace {
  static const T value;
  /*if(RC==C){
    value = S;
  }else{
    value = linspace<T,RC-1,S,E,C>::value;
  }*/

};

template<typename T, T S, T E, size_t C> struct linspace<T, 1, S, E, C> {
  static const T value = E;
};

} //namespace linspace_detail

//--------------------------------------------------

} //namespace Initialize


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

//--- remove const from any Type

namespace Types {

/**************************************************
 * Remove Pointer Property from Type if exists
 **************************************************/

//default Implementation
template <typename U> struct remove_pointer { // in general case
  using type = U;
};

//Spezialisation
template <typename T> struct remove_pointer<T*> { // for U = T*
  using type = T;
};

//convenience Wrapper
template <typename W> using RemovePointer = typename remove_pointer<W>::type;

//--------------------------------------------------

//----- remove const from any Type
template <typename T> struct DeConst {
  using R = T;
};
template <typename T> struct DeConst<T const> {
  using R = T;
};

//--------------------------------------------------
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

//--- Select Type by condition

template<bool cond, typename TRUE, typename FALSE> struct if_else{
  using type = FALSE;
};

template<typename TRUE, typename FALSE> struct if_else<true,TRUE,FALSE>{
  using type = TRUE;
};

template<bool cond, typename TRUE, typename FALSE> using if_else_t = typename if_else<cond,TRUE,FALSE>::type;

//--- construct nested Initializer List

template<typename T, size_t LEVELS> struct nested_init_lists_st{
  using type = std::initializer_list<typename nested_init_lists_st<T,(LEVELS-1)>::type>;
  //using type = if_else_t<(LEVELS>1),std::initializer_list<typename nested_init_lists_st<T,(LEVELS-1)>::type>,std::initializer_list<T>>;
};

template<typename T> struct nested_init_lists_st<T,1>{
  using type = std::initializer_list<T>;
};

template<typename T> struct nested_init_lists_st<T,0>{
  using type = std::initializer_list<T>;
};

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

template<typename T> struct replace8bitint{

  using type = if_else_t<std::is_same<u8,T>::value,u16,
               if_else_t<std::is_same<s8,T>::value,s16,
               if_else_t<std::is_same<u8&,T>::value,u16&,
               if_else_t<std::is_same<s8&,T>::value,s16&,
               if_else_t<std::is_same<u8 const,T>::value,u16 const,
               if_else_t<std::is_same<s8 const,T>::value,s16 const,
               if_else_t<std::is_same<u8 const&,T>::value,u16 const&,
               if_else_t<std::is_same<s8 const&,T>::value,s16 const&,
               T>>>>>>>>;

  /*using type = if_else_t<(sizeof(T)==1 && std::is_integral<T>() && std::is_unsigned<T>()),u16,
               if_else_t<(sizeof(T)==1 && std::is_integral<T>() && std::is_signed<T>())  ,s16,
               T>>;*/
};

template<typename T> using replace8bitint_t = typename Meta::Types::replace8bitint<T>::type;
//template<typename T> using replace8bitint_t = typename Meta::Types::replace8bitint<typename std::remove_cv<T>::type>::type;

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

} //namespace Types

//--------------------------------------------------

namespace Select{

/**************************************************
 * Select a Type by Condition at Compile Time
 **************************************************/

//default Implementation
template< bool CONDITION, class THEN, class ELSE > struct IF{};

//Spezialisation "False"
template<class THEN, class ELSE> struct IF< false, THEN, ELSE > {
  using result = ELSE ;
};

//Spezialisation "True"
template<class THEN, class ELSE> struct IF< true, THEN, ELSE > {
  using result = THEN;
};

//convenience Wrapper
template< bool CONDITION, class THEN, class ELSE > using IF_ELSE = typename IF<CONDITION,THEN,ELSE>::result;

//--------------------------------------------------

} //namespace Select


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

/*namespace datastruct{

template<typename T1, typename T2> struct pair{
  T1 first;
  T2 second;
};*/

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

} //namespace Meta

#endif // META_H
