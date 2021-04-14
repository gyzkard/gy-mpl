#pragma once
#ifndef INCLUDED_GYMPL_TESTING
#define INCLUDED_GYMPL_TESTING

#include <cassert>

#include <gympl/macroTools.hpp>

#define GYMPL_REQUIRE(expr) (void)((! ! (expr)) || (assert(expr), std::exit(EXIT_FAILURE), 0))

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
