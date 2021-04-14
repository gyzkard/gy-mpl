<!---
Copyright 2021-today gyzkard
(gyzkard@gyzkard.com)

Distributed under the MIT License.
(https://opensource.org/licenses/mit-license.php)
-->

gy-mpl
======

Macros, Traits and Concepts for C++.

## Copyright and License

* Copyright 2021-today gyzkard (gyzkard@gyzkard.com)

Distributed under the MIT License 
(https://opensource.org/licenses/mit-license.php).


## Basic Usage

```cpp
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

## todo

* Wait for Doxygen to support concepts or document them manually.
