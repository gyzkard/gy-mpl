/// \file gympl.hpp

#pragma once
#ifndef INCLUDED_GYMPL_PLATFORM
// \cond macro-verbose-255
#define INCLUDED_GYMPL_PLATFORM

#if defined(_MSC_VER)
#define GYMPL_COMPILER "MSVC"
#define GYMPL_COMPILER_MSVC
// todo: will ms ever consider
#define _Pragma(s)
#elif defined(__clang_major__)
#define GYMPL_COMPILER "CLANG"
#define GYMPL_COMPILER_CLANG
#elif defined(__GNUC__)
#define GYMPL_COMPILER "GCC"
#define GYMPL_COMPILER_GCC
#endif

#if __cplusplus >= 201703L
#define GYMPL_HAS_CPP17
#endif
// todo: msvc  defines __cplusplus as 201703L and /std:c++latest is not yet totally c++20 (and all this only with /Zc:__cplusplus
// enabled),
//       clang defines __cplusplus as 202002L and -std=c++20 also isn't totally c++20 yet,
//       gcc   defines __cplusplus as 201705L with -std=c++20,
//       so:
//#if __cplusplus >= 202002L
#if __cplusplus >= 201705L
#define GYMPL_HAS_CPP20

#if defined(GYMPL_COMPILER_CLANG) && (__clang_major__ > 13 || (__clang_major__ == 13 && __clang_minor__ >= 0)) || \
    defined(GYMPL_COMPILER_GCC) && (__GNUC__ > 10 || (__GNUC__ == 10 && __GNUC_MINOR__ >= 2)) ||                  \
    ! defined(GYMPL_COMPILER_CLANG) && ! defined(GYMPL_COMPILER_GCC)
// todo: Who knows when clang will have these available.
//       Adapt the check accordingly when it will be clear.
//       Atm (with Clang 11.0.1) , it seems like the trunk has them and it shows version 13.0.0, at least on godbolt.
#define GYMPL_HAS_CLASS_TYPE_NON_TYPE_TEMPLATE_PARAMS
#define GYMPL_HAS_RANGES
#endif

#if defined(GYMPL_COMPILER_CLANG) && (__clang_major__ > 11 || (__clang_major__ == 11 && __clang_patchlevel__ >= 1)) || \
    defined(GYMPL_COMPILER_GCC) && (__GNUC__ > 10 || (__GNUC__ == 10 && __GNUC_MINOR__ >= 2)) ||                       \
    ! defined(GYMPL_COMPILER_CLANG) && ! defined(GYMPL_COMPILER_GCC)
#define GYMPL_HAS_CONCEPTS
#define GYMPL_HAS_SPACESHIP
#define GYMPL_HAS_REMOVE_CV_REF
#endif

#endif
#if ! defined(GYMPL_COMPILER_GCC) || __GNUC__ > 10 || (__GNUC__ == 10 && __GNUC_MINOR__ >= 2)
#define GYMPL_HAS_NOEXCEPT_OP
#define GYMPL_NOEXCEPT_OP(...) noexcept(__VA_ARGS__)
#else
#define GYMPL_NOEXCEPT_OP(...) false
#endif
#if ! defined(GYMPL_COMPILER_MSVC) && (! defined(GYMPL_COMPILER_GCC) || __GNUC__ > 10 || (__GNUC__ == 10 && __GNUC_MINOR__ >= 2))
#define GYMPL_HAS_VALID_SFINAE_NOEXCEPT_OP(...) noexcept(__VA_ARGS__)
#else
#define GYMPL_HAS_VALID_SFINAE_NOEXCEPT_OP(...) false
#endif
#if __cplusplus >= 201402L
#define GYMPL_HAS_CPP14
#endif

#if defined(GYMPL_HAS_CPP20) &&                                                                                         \
    (defined(GYMPL_COMPILER_CLANG) && (__clang_major__ > 11 || (__clang_major__ == 11 && __clang_patchlevel__ >= 1)) || \
     defined(GYMPL_COMPILER_GCC) && (__GNUC__ > 10 || (__GNUC__ == 10 && __GNUC_MINOR__ >= 2)) ||                       \
     ! defined(GYMPL_COMPILER_CLANG) && ! defined(GYMPL_COMPILER_GCC))
#define GYMPL_HAS_is_nothrow_convertible
#endif

#ifdef GYMPL_HAS_CPP17
#define GYMPL_HAS_DEFINITIONLESS_STATIC_CONSTEXPR_DATA_MEMBER
#endif

#ifdef GYMPL_HAS_CONCEPTS
#define GYMPL_COT(mp_c) mp_c
#define GYMPL_COREQUIRES(...) requires(__VA_ARGS__)
#define GYMPL_PRE_CONCEPTS_CHECK(...)
#else
#define GYMPL_COT(mp_c) typename
#define GYMPL_COREQUIRES(...)
#define GYMPL_PRE_CONCEPTS_CHECK(...) static_assert(__VA_ARGS__)
#define GYMPL_CPP11
#endif

#ifdef GYMPL_HAS_CPP17
#define GYMPL_NTSA
#else
#define GYMPL_NTSA , "todo"
#endif

#ifdef GYMPL_HAS_CPP14
#define GYMPL_CONSTEXPR_11 constexpr
#else
#define GYMPL_CONSTEXPR_11
#endif
// \endcond

#endif
