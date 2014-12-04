///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013 - 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _TYPE_TRAITS_IMPL_2013_09_02_H_
  #define _TYPE_TRAITS_IMPL_2013_09_02_H_

  #include "cstddef_impl.h"
  #include "limits_impl.h"

  // Implement some of <type_traits> for compilers that do not yet support it.

  namespace std
  {
    template<typename template_value_type,
             template_value_type the_value>
    struct integral_constant
    {
      typedef template_value_type value_type;

      static constexpr value_type value = the_value;

      typedef integral_constant<value_type, value> type;

      operator value_type() const
      {
        return value;
      }
    };

    typedef integral_constant<bool, true>  true_type;
    typedef integral_constant<bool, false> false_type;
  }

  #if defined(_MSC_VER)
    typedef signed short char16_t;
    typedef signed int   char32_t;
  #endif

  namespace traits_helper
  {
    template<typename T> struct is_integral                     : std::false_type { };
    template<>           struct is_integral<bool>               : std::true_type  { };
    template<>           struct is_integral<char>               : std::true_type  { };
    template<>           struct is_integral<signed char>        : std::true_type  { };
    template<>           struct is_integral<unsigned char>      : std::true_type  { };
    template<>           struct is_integral<char16_t>           : std::true_type  { };
    template<>           struct is_integral<char32_t>           : std::true_type  { };
    template<>           struct is_integral<wchar_t>            : std::true_type  { };
    template<>           struct is_integral<short>              : std::true_type  { };
    template<>           struct is_integral<int>                : std::true_type  { };
    template<>           struct is_integral<long>               : std::true_type  { };
    template<>           struct is_integral<long long>          : std::true_type  { };
    template<>           struct is_integral<unsigned short>     : std::true_type  { };
    template<>           struct is_integral<unsigned int>       : std::true_type  { };
    template<>           struct is_integral<unsigned long>      : std::true_type  { };
    template<>           struct is_integral<unsigned long long> : std::true_type  { };

    template<typename T> struct is_floating_point               : std::false_type { };
    template<>           struct is_floating_point<float>        : std::true_type  { };
    template<>           struct is_floating_point<double>       : std::true_type  { };
    template<>           struct is_floating_point<long double>  : std::true_type  { };
  }

  namespace std
  {
    template<bool,
             typename template_value_type = void>
    struct enable_if { };

    template<typename template_value_type>
    struct enable_if<true, template_value_type>
    {
      typedef template_value_type type;
    };

    template<typename template_value_type1,
             typename template_value_type2>
    struct is_same : false_type { };

    template<typename template_value_type1>
    struct is_same<template_value_type1,
                   template_value_type1> : true_type { };

    template<typename T> struct add_const    { typedef const T type; };
    template<typename T> struct add_volatile { typedef volatile T type; };
    template<typename T> struct add_cv       { typedef typename std::add_volatile<typename std::add_const<T>::type>::type type; };

    template<typename T> struct remove_const                { typedef T type; };
    template<typename T> struct remove_const<const T>       { typedef T type; };
    template<typename T> struct remove_volatile             { typedef T type; };
    template<typename T> struct remove_volatile<volatile T> { typedef T type; }; 
    template<typename T> struct remove_cv                   { typedef typename std::remove_volatile<typename std::remove_const<T>::type>::type type; };

    template<typename T> struct is_void           : std::integral_constant          <bool, std::is_same<void, typename std::remove_cv<T>::type>::value> { };
    template<typename T> struct is_null_pointer   : std::integral_constant          <bool, std::is_same<void, typename std::remove_cv<std::nullptr_t>::type>::value> { };
    template<typename T> struct is_integral       : traits_helper::is_integral      <typename remove_cv<T>::type> { };
    template<typename T> struct is_floating_point : traits_helper::is_floating_point<typename remove_cv<T>::type> { };
    template<typename T> struct is_arithmetic     : std::integral_constant          <bool,    std::is_integral      <T>::value
                                                                                           || std::is_floating_point<T>::value> { };
    template<typename T> struct is_fundamental    : std::integral_constant          <bool,    std::is_arithmetic    <T>::value
                                                                                           || std::is_void          <T>::value
                                                                                           || std::is_null_pointer  <T>::value> { };
    template<typename T> struct is_array          : std::false_type {};
    template<typename T> struct is_array<T[]>     : std::true_type  {};
    template<typename T, std::size_t N>
                         struct is_array<T[N]>    : std::true_type  {};
  }

#endif // _TYPE_TRAITS_IMPL_2013_09_02_H_
