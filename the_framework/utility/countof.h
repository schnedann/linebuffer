#ifndef _COUNTOF_H
#define _COUNTOF_H

/* http://blog.natekohl.net/making-countof-suck-less/
 * Ivan Johnson solved this problem with a clever COUNTOF macro
 * that wins on all accounts: it's typesafe, compile-time,
 * and works with local types:
 */
#define COUNTOF(arr) ( \
   0 * sizeof(reinterpret_cast<const ::Bad_arg_to_COUNTOF*>(arr)) + \
   0 * sizeof(::Bad_arg_to_COUNTOF::check_type((arr), &(arr))) + \
   sizeof(arr) / sizeof((arr)[0]) )

struct Bad_arg_to_COUNTOF {
   class Is_pointer; // incomplete
   class Is_array {};
   template <typename T>
   static Is_pointer check_type(const T*, const T* const*);
   static Is_array check_type(const void*, const void*);
};

/* Alternate Solution for >=C++11
template<typename T, std::size_t N>
constexpr std::size_t countof(T const (&)[N]) noexcept
{
  return N;
}
*/

#endif
