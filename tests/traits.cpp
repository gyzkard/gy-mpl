#include <gympl/testing.hpp>

#include <type_traits>

#include <gympl/gympl.hpp>

#define GYMPL_PRINT_CONFIG
#include <gympl/outputCompilerInfo.hpp>
#include <gympl/outputConfiguration.hpp>

namespace
{
    namespace testtypes
    {
        struct StronglyIncrementable
        {
            StronglyIncrementable& operator++() &;
            StronglyIncrementable operator++(int) &;
        };
        struct WeaklyIncrementable
        {
            WeaklyIncrementable& operator++();
            WeaklyIncrementable operator++(int);
        };

        struct HasValue
        {
            int value();
        };
        struct HasValueBase
        {
            double index_base();
        };
        struct HasValueAndValueBase
        {
            int value();
            double index_base();
        };

        struct HasTypeMember
        {
            typedef int type;
        };

        struct HasValueN
        {
            gympl::mpl::NotMyType value();
        };
        struct HasValueBaseN
        {
            gympl::mpl::NotMyType index_base();
        };
        struct HasValueAndValueBaseNvNb
        {
            gympl::mpl::NotMyType value();
            gympl::mpl::NotMyType index_base();
        };
        struct HasValueAndValueBaseNv
        {
            gympl::mpl::NotMyType value();
            double index_base();
        };
        struct HasValueAndValueBaseNb
        {
            int value();
            gympl::mpl::NotMyType index_base();
        };
    }

    void concept_traits_checks()
    {
        using namespace gympl::mpl;
        using namespace gympl::traits;

        static_assert(std::is_same<First<int, double>::type, int>::value GYMPL_NTSA);

        static_assert(! has_type_member<int>::value GYMPL_NTSA);
        static_assert(has_type_member<testtypes::HasTypeMember>::value GYMPL_NTSA);
        static_assert(has_type_member<std::remove_const<int>>::value GYMPL_NTSA);

        static_assert(std::is_same<bool_to_type<int, 0>::type, NotMyType>::value GYMPL_NTSA);
        static_assert(std::is_same<bool_to_type<int, 1>::type, int>::value GYMPL_NTSA);

        static_assert(! has_type_member<is_same_to_type<int, double>>::value GYMPL_NTSA);
        static_assert(has_type_member<is_same_to_type<int, int>>::value GYMPL_NTSA);

        static_assert(cv_ref_removed_is_same<int, int>::value GYMPL_NTSA);
        static_assert(cv_ref_removed_is_same<int, int&>::value GYMPL_NTSA);
        static_assert(cv_ref_removed_is_same<int, int&&>::value GYMPL_NTSA);
        static_assert(cv_ref_removed_is_same<int, int const>::value GYMPL_NTSA);
        static_assert(cv_ref_removed_is_same<int, int const&>::value GYMPL_NTSA);
        static_assert(cv_ref_removed_is_same<int, int const&&>::value GYMPL_NTSA);

        static_assert(std::is_same<get_as_signed_type<unsigned int, NotMyType>::type, int>::value GYMPL_NTSA);
        static_assert(std::is_same<get_as_signed_type<int, NotMyType>::type, int>::value GYMPL_NTSA);
        static_assert(std::is_same<get_as_signed_type<int&, NotMyType>::type, int&>::value GYMPL_NTSA);
        static_assert(std::is_same<get_as_signed_type<void, NotMyType>::type, NotMyType>::value GYMPL_NTSA);

        static_assert(! has_plus<NotMyType>::value GYMPL_NTSA);
        static_assert(has_plus<int>::value GYMPL_NTSA);
        static_assert(! has_minus<NotMyType>::value GYMPL_NTSA);
        static_assert(has_minus<int>::value GYMPL_NTSA);
        static_assert(! has_multiply<NotMyType>::value GYMPL_NTSA);
        static_assert(has_multiply<int>::value GYMPL_NTSA);
        static_assert(! has_divide<NotMyType>::value GYMPL_NTSA);
        static_assert(has_divide<int>::value GYMPL_NTSA);

        static_assert(! has_plus<NotMyType, int>::value GYMPL_NTSA);
        static_assert(has_plus<int, double>::value GYMPL_NTSA);
        static_assert(! has_minus<NotMyType, int>::value GYMPL_NTSA);
        static_assert(has_minus<int, double>::value GYMPL_NTSA);
        static_assert(! has_multiply<NotMyType, int>::value GYMPL_NTSA);
        static_assert(has_multiply<int, double>::value GYMPL_NTSA);
        static_assert(! has_divide<NotMyType, int>::value GYMPL_NTSA);
        static_assert(has_divide<int, double>::value GYMPL_NTSA);

        static_assert(! has_increment_prefix<NotMyType>::value GYMPL_NTSA);
        static_assert(has_increment_prefix<int>::value GYMPL_NTSA);
        static_assert(! has_increment_postfix<NotMyType>::value GYMPL_NTSA);
        static_assert(has_increment_postfix<int>::value GYMPL_NTSA);
        static_assert(! has_decrement_prefix<NotMyType>::value GYMPL_NTSA);
        static_assert(has_decrement_prefix<int>::value GYMPL_NTSA);
        static_assert(! has_decrement_postfix<NotMyType>::value GYMPL_NTSA);
        static_assert(has_decrement_postfix<int>::value GYMPL_NTSA);

        static_assert(! is_addable<NotMyType>::value GYMPL_NTSA);
        static_assert(is_addable<int>::value GYMPL_NTSA);
        static_assert(! is_subtractable<NotMyType>::value GYMPL_NTSA);
        static_assert(is_subtractable<int>::value GYMPL_NTSA);
        static_assert(! is_multiplyable<NotMyType>::value GYMPL_NTSA);
        static_assert(is_multiplyable<int>::value GYMPL_NTSA);
        static_assert(! is_dividable<NotMyType>::value GYMPL_NTSA);
        static_assert(is_dividable<int>::value GYMPL_NTSA);

        static_assert(! is_addable<NotMyType, int>::value GYMPL_NTSA);
        static_assert(is_addable<int, double>::value GYMPL_NTSA);
        static_assert(! is_subtractable<NotMyType, int>::value GYMPL_NTSA);
        static_assert(is_subtractable<int, double>::value GYMPL_NTSA);
        static_assert(! is_multiplyable<NotMyType, int>::value GYMPL_NTSA);
        static_assert(is_multiplyable<int, double>::value GYMPL_NTSA);
        static_assert(! is_dividable<NotMyType, int>::value GYMPL_NTSA);
        static_assert(is_dividable<int, double>::value GYMPL_NTSA);

        static_assert(is_weakly_incrementable<testtypes::WeaklyIncrementable>::value GYMPL_NTSA);
        static_assert(! is_weakly_incrementable<testtypes::StronglyIncrementable>::value GYMPL_NTSA);
        static_assert(is_strongly_incrementable<int>::value GYMPL_NTSA);
        static_assert(! is_strongly_incrementable<int const>::value GYMPL_NTSA);
        static_assert(is_strongly_decrementable<int>::value GYMPL_NTSA);
        static_assert(! is_strongly_decrementable<int const>::value GYMPL_NTSA);

        static_assert(is_strongly_in_and_decrementable<int>::value GYMPL_NTSA);
        static_assert(! is_strongly_in_and_decrementable<int const>::value GYMPL_NTSA);
        static_assert(is_strongly_in_and_decrementable<float>::value GYMPL_NTSA);
        static_assert(! is_strongly_in_and_decrementable<void*>::value GYMPL_NTSA);

        static_assert(! is_add_and_subtractable<NotMyType>::value GYMPL_NTSA);
        static_assert(is_add_and_subtractable<int const>::value GYMPL_NTSA);
        static_assert(is_add_and_subtractable<float const&&>::value GYMPL_NTSA);

        static_assert(! is_add_and_subtractable<NotMyType, int>::value GYMPL_NTSA);
        static_assert(is_add_and_subtractable<int const, float const>::value GYMPL_NTSA);
        static_assert(is_add_and_subtractable<int const&, float const&>::value GYMPL_NTSA);
        static_assert(is_add_and_subtractable<int const&&, float const&&>::value GYMPL_NTSA);

        static_assert(! can_do_arithmetics<NotMyType, int>::value GYMPL_NTSA);
        static_assert(can_do_arithmetics<int const, float const>::value GYMPL_NTSA);
        static_assert(can_do_arithmetics<int const&, float const&>::value GYMPL_NTSA);
        static_assert(can_do_arithmetics<int const&&, float const&&>::value GYMPL_NTSA);

        static_assert(std::is_same<diff_type<int const&&, float const&&>::type, float>::value GYMPL_NTSA);
        static_assert(std::is_same<diff_type<void, int>::type, NotMyType>::value GYMPL_NTSA);

        static_assert(is_array_index<int>::value GYMPL_NTSA);
        static_assert(is_array_index<int const&>::value GYMPL_NTSA);
        static_assert(is_array_index<int const&&>::value GYMPL_NTSA);
        static_assert(! is_array_index<float>::value GYMPL_NTSA);
        static_assert(! is_array_index<void*>::value GYMPL_NTSA);
    }
#ifdef GYMPL_HAS_CONCEPTS
    void concept_concept_checks()
    {
        using namespace gympl::concepts;

        static_assert(CvRefRemovedIsSame<int, int>);
        static_assert(CvRefRemovedIsSame<int, int&>);
        static_assert(CvRefRemovedIsSame<int, int&&>);
        static_assert(CvRefRemovedIsSame<int, int const>);
        static_assert(CvRefRemovedIsSame<int, int const&>);
        static_assert(CvRefRemovedIsSame<int, int const&&>);

        static_assert(! Addable<NotMyType>);
        static_assert(Addable<int>);
        static_assert(! Subtractable<NotMyType>);
        static_assert(Subtractable<int>);
        static_assert(! Multiplyable<NotMyType>);
        static_assert(Multiplyable<int>);
        static_assert(! Dividable<NotMyType>);
        static_assert(Dividable<int>);

        static_assert(! Addable<NotMyType, int>);
        static_assert(Addable<int, double>);
        static_assert(! Subtractable<NotMyType, int>);
        static_assert(Subtractable<int, double>);
        static_assert(! Multiplyable<NotMyType, int>);
        static_assert(Multiplyable<int, double>);
        static_assert(! Dividable<NotMyType, int>);
        static_assert(Dividable<int, double>);

        static_assert(WeaklyIncrementable<testtypes::WeaklyIncrementable>);
        static_assert(! WeaklyIncrementable<testtypes::StronglyIncrementable>);
        static_assert(! StronglyIncrementable<testtypes::WeaklyIncrementable>);
        static_assert(StronglyIncrementable<testtypes::StronglyIncrementable>);
        static_assert(StronglyIncrementable<int>);
        static_assert(! StronglyIncrementable<int const>);
        static_assert(StronglyDecrementable<int>);
        static_assert(! StronglyDecrementable<int const>);

        static_assert(StronglyInDecrementable<int>);
        static_assert(! StronglyInDecrementable<int const>);
        static_assert(StronglyInDecrementable<float>);
        static_assert(! StronglyInDecrementable<void*>);

        static_assert(! AddAndSubtractable<NotMyType>);
        static_assert(AddAndSubtractable<int const>);
        static_assert(AddAndSubtractable<float const&&>);

        static_assert(! AddAndSubtractable<NotMyType, int>);
        static_assert(AddAndSubtractable<int const, float const>);
        static_assert(AddAndSubtractable<int const&, float const&>);
        static_assert(AddAndSubtractable<int const&&, float const&&>);

        static_assert(! CanDoArithmetics<NotMyType, int>);
        static_assert(CanDoArithmetics<int const, float const>);
        static_assert(CanDoArithmetics<int const&, float const&>);
        static_assert(CanDoArithmetics<int const&&, float const&&>);
    }
#endif
}

GYMPL_TEST_MAIN_START
{
    return EXIT_SUCCESS;
}
GYMPL_TEST_MAIN_END
