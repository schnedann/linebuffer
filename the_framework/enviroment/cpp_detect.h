#ifndef CPP_DETECT_H
#define CPP_DETECT_H

#ifndef __STDC_VERSION__
  #define __STDC_VERSION__ 199000L
#endif


#define dUSE_C94 	(__STDC_VERSION__==199409L)
#define dUSE_C99 	(__STDC_VERSION__==199901L)
#define dUSE_C11 	(__STDC_VERSION__==201112L)
#define dUSE_C18 	(__STDC_VERSION__==201710L)

#define dUSE_Cpp98 ((__cplusplus==199711L)||dUSE_Cpp11)
#define dUSE_Cpp11 ((__cplusplus==201103L)||dUSE_Cpp14)
#define dUSE_Cpp14 ((__cplusplus==201402L)||dUSE_Cpp17)
#define dUSE_Cpp17 ((__cplusplus==201703L)||dUSE_Cpp20)
#define dUSE_Cpp20 (__cplusplus==202002L)

namespace Enviroment {

constexpr bool const USE_C94 = dUSE_C94;
constexpr bool const USE_C99 = dUSE_C99;
constexpr bool const USE_C11 = dUSE_C11;
constexpr bool const USE_C18 = dUSE_C18;

constexpr bool const USE_Cpp98 = dUSE_Cpp98;
constexpr bool const USE_Cpp11 = dUSE_Cpp11;
constexpr bool const USE_Cpp14 = dUSE_Cpp14;
constexpr bool const USE_Cpp17 = dUSE_Cpp17;
constexpr bool const USE_Cpp20 = dUSE_Cpp20;

} //namespace


#endif // CPP_DETECT_H
