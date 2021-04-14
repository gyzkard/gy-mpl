#include <gympl/macroTools.hpp>
#include <gympl/testing.hpp>

#ifdef _MSC_VER
#pragma message(GYMPL_PRINTDEFINE(__cplusplus))
#pragma message(GYMPL_PRINTDEFINE(_MSC_FULL_VER))
#else
#pragma message(GYMPL_PRINTDEFINE(__cplusplus))
#if defined(__clang_major__)
#pragma message("clang version: " GYMPL_TOSTR(__clang_major__) "." GYMPL_TOSTR(__clang_minor__) "." GYMPL_TOSTR(__clang_patchlevel__))
#endif
#if defined(__GNUC__)
#pragma message("gcc version: " GYMPL_TOSTR(__GNUC__) "." GYMPL_TOSTR(__GNUC_MINOR__))
#endif
#endif
