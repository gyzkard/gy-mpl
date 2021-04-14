# gy-mpl

Macros, Traits and Concepts for C++.

## Quickstart

```c++
#include <gympl/gympl.hpp>

using namespace gympl::traits;

static_assert(! is_addable<NotMyType, int>::value GYMPL_NTSA);
static_assert(is_addable<int, double>::value GYMPL_NTSA);

#ifdef GYMPL_HAS_CONCEPTS
using namespace gympl::concepts;

static_assert(! Addable<NotMyType, int>);
static_assert(Addable<int, double>);
#endif
```

## Supported compilers

At the moment, this library requires C++11 support.
It has been successfully tested with
* MSVC V16.9.2 (VS 2019) V15.9.34 (VS 2017), mostly V14.0.25431.01 Update 3 (VS 2015) [some traits don't work yet]; VS 2010 and below won't work
* clang 7.0.1-8 and 11.0.1-2
* gcc 8.3.0-6 and 10.2.1-6
