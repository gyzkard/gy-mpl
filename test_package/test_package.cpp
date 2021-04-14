#include <gympl/gympl.hpp>

#include <cassert>

namespace
{
    using namespace gympl;

    void example()
    {
		using namespace gympl::traits;

		static_assert(! is_addable<NotMyType, int>::value GYMPL_NTSA);
		static_assert(is_addable<int, double>::value GYMPL_NTSA);

#ifdef GYMPL_HAS_CONCEPTS
		using namespace gympl::concepts;

		static_assert(! Addable<NotMyType, int>);
		static_assert(Addable<int, double>);
#endif
    }
}

int main()
{
    example();
    return EXIT_SUCCESS;
}
