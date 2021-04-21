#pragma once
#ifndef INCLUDED_GYMPL_TESTING
#define INCLUDED_GYMPL_TESTING

#include <cassert>
#include <type_traits>
#include <cmath>

#include <gympl/macroTools.hpp>

#define GYMPL_REQUIRE(expr) (void)((! ! (expr)) || (assert(expr), std::exit(EXIT_FAILURE), 0))

namespace gympl
{
    namespace testing
    {
        template <typename T>
        inline bool isEqual(T v1, T v2, T epsilon)
        {
            return std::abs(v1 - v2) <= epsilon;
        }
    }
}

#define GYMPL_PRINTDEFINE(x) #x ": " GYMPL_TOSTR2(x)

#ifndef GYMPL_NON_SELF_CONTAINED_TESTS
#define GYMPL_TEST_MAIN_START int main()
#else
#define GYMPL_TEST_MAIN_START \
    namespace                 \
    {                         \
        int r = []()
#endif

#ifdef GYMPL_NON_SELF_CONTAINED_TESTS
#define GYMPL_TEST_MAIN_END \
    ();                     \
    }
#else
#define GYMPL_TEST_MAIN_END
#endif

#endif
