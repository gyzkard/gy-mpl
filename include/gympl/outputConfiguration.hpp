#include <gympl/macroTools.hpp>
#include <gympl/testing.hpp>

#ifdef GYMPL_PRINT_CONFIG

#pragma message(GYMPL_PRINTDEFINE(GYMPL_COMPILER))
#ifdef GYMPL_HAS_CPP20
#pragma message(GYMPL_TOSTR2(GYMPL_HAS_CPP20))
#endif
#ifdef GYMPL_HAS_CPP17
#pragma message(GYMPL_TOSTR2(GYMPL_HAS_CPP17))
#endif
#ifdef GYMPL_HAS_CPP14
#pragma message(GYMPL_TOSTR2(GYMPL_HAS_CPP14))
#endif

#ifdef GYMPL_HAS_RANGES
#pragma message(GYMPL_TOSTR2(GYMPL_HAS_RANGES))
#endif
#ifdef GYMPL_HAS_CONCEPTS
#pragma message(GYMPL_TOSTR2(GYMPL_HAS_CONCEPTS))
#endif
#ifdef GYMPL_HAS_SPACESHIP
#pragma message(GYMPL_TOSTR2(GYMPL_HAS_SPACESHIP))
#endif
#ifdef GYMPL_HAS_REMOVE_CV_REF
#pragma message(GYMPL_TOSTR2(GYMPL_HAS_REMOVE_CV_REF))
#endif
#ifdef GYMPL_HAS_NOEXCEPT_OP
#pragma message(GYMPL_TOSTR2(GYMPL_HAS_NOEXCEPT_OP))
#endif

#endif
