/// \file gympl.hpp

#pragma once
#ifndef INCLUDED_GYMPL_GYMPL
// \cond macro-verbose-255
#define INCLUDED_GYMPL_GYMPL

#include <algorithm>
#include <type_traits>

#include <gympl/platform.hpp>
#ifdef GYMPL_HAS_SPACESHIP
#include <compare>
#endif

// \endcond

#if _MSC_VER <= 1900
#pragma warning(push)
#pragma warning(disable : 4814) // MS
#endif

namespace gympl
{
    namespace compatibility
    {
#ifndef GYMPL_HAS_CPP17
        template<bool B>
        using bool_constant = std::integral_constant<bool, B>;
#else
        using std::bool_constant;
#endif

#ifdef GYMPL_HAS_REMOVE_CV_REF
        using std::remove_cvref;
#else
        template<class T>
        struct remove_cvref
        {
            typedef typename std::remove_cv<typename std::remove_reference<T>::type>::type type;
        };
#endif
    }
    namespace mpl
    {
        using namespace compatibility;

        template<typename T, typename... args>
        struct First
        {
            typedef T type;
        };

        struct NotMyType
        {};
        template<typename T, int I>
        struct bool_to_type
        {
            typedef NotMyType type;
        };
        template<typename T>
        struct bool_to_type<T, 1>
        {
            typedef T type;
        };

        template<typename T, int I>
        struct bool_to_types_type
        {
            typedef NotMyType type;
        };
        template<typename T>
        struct bool_to_types_type<T, 1>
        {
            typedef typename T::type type;
        };

        struct Match
        {};

        template<typename T, typename U, typename H = Match>
        struct is_same_to_type
        {};
        template<typename T, typename U>
        struct is_same_to_type<T, U, typename bool_to_type<Match, std::is_same<T, U>::value>::type>
        {
            typedef void type;
        };

        template<typename T>
        decltype(std::declval<typename std::add_lvalue_reference<T>::type>()) Instantiate()
        {
            return std::declval<typename std::add_lvalue_reference<T>::type>();
        }

        template<template<typename, typename> class OP, typename T, typename U = T>
        struct op2x : bool_constant<OP<T, U>::value && OP<U, T>::value>
        {};
        template<template<typename, typename> class OP, typename T, typename U = T>
        struct op2 : bool_constant<OP<T, T>::value && OP<U, U>::value && op2x<OP, T, U>::value>
        {};
    }

    namespace traits
    {
        using namespace compatibility;
        using namespace mpl;

        using std::false_type;
        using std::true_type;

        template<class, class = void>
        struct has_type_member : false_type
        {};
#ifdef GYMPL_HAS_CPP17
        template<class T>
        struct has_type_member<T, std::void_t<typename T::type>> : true_type
        {};
        template<class T>
        inline constexpr bool has_type_member_v = has_type_member<T>::value;
#else
        template<class T>
        struct has_type_member<T, typename mpl::First<void, typename T::type>::type> : true_type
        {};
#endif

        template<typename T, typename U>
        struct cv_ref_removed_is_same : bool_constant<std::is_same<typename remove_cvref<T>::type, typename remove_cvref<U>::type>::value>
        {};

#ifdef GYMPL_HAS_CPP17
        template<typename T, typename U>
        inline constexpr bool cv_ref_removed_is_same_v = cv_ref_removed_is_same<T, U>::value;
#endif

        // c/p from ms type_traits..
        // \cond ns-detail
        namespace detail
        {
            template<typename From>
            struct copy_cv
            {
                template<typename To>
                using Apply = To;
            };
            template<typename From>
            struct copy_cv<const From>
            {
                template<typename To>
                using Apply = const To;
            };
            template<typename From>
            struct copy_cv<volatile From>
            {
                template<typename To>
                using Apply = volatile To;
            };
            template<typename From>
            struct copy_cv<const volatile From>
            {
                template<typename To>
                using Apply = const volatile To;
            };
        }
        // \endcond
        template<typename From, typename To>
        using copy_cv = typename detail::copy_cv<From>::template Apply<To>;

        template<typename From>
        struct copy_ref
        {
            template<class To>
            using Apply = copy_cv<From, To>;
        };
        template<typename From>
        struct copy_ref<From&>
        {
            template<class To>
            using Apply = typename std::add_lvalue_reference<copy_cv<From, To>>::type;
        };
        template<typename From>
        struct copy_ref<From&&>
        {
            template<class To>
            using Apply = typename std::add_rvalue_reference<copy_cv<From, To>>::type;
        };

        // \cond ns-detail
        namespace detail
        {
            template<typename T, typename Default, int IsIntegral>
            struct get_as_signed_type
            {
                typedef Default type;
            };
            template<typename T, typename Default>
            struct get_as_signed_type<T, Default, 1>
            {
                typedef typename copy_ref<T>::template Apply<typename std::make_signed<typename std::remove_reference<T>::type>::type>
                    type;
            };
        }
        // \endcond

        /// <summary>
        /// std::make_signed with fallback
        /// </summary>
        /// <param name="T">potentially unsigned value with a potentially signed representation</param>
        /// <param name="Default">Fallback type in case there's no signed representation of T</param>
        template<typename T, typename Default = T>
        struct get_as_signed_type
        {
            typedef typename detail::get_as_signed_type<T, Default, std::is_integral<typename remove_cvref<T>::type>::value>::type type;
        };

        // \cond impl
        namespace ops
        {
            using namespace mpl;

            template<typename T, typename U, typename H = Match>
            struct has_plus : false_type
            {};
            template<typename T, typename U>
            struct has_plus<T, U, typename First<Match, decltype(Instantiate<T>() + Instantiate<U>())>::type> : true_type
            {};

            template<typename T, typename U, typename H = Match>
            struct has_minus : false_type
            {};
            template<typename T, typename U>
            struct has_minus<T, U, typename First<Match, decltype(Instantiate<T>() - Instantiate<U>())>::type> : true_type
            {};

            template<typename T, typename U, typename H = Match>
            struct has_multiply : false_type
            {};
            template<typename T, typename U>
            struct has_multiply<T, U, typename First<Match, decltype(Instantiate<T>() * Instantiate<U>())>::type> : true_type
            {};

            template<typename T, typename U, typename H = Match>
            struct has_divide : false_type
            {};
            template<typename T, typename U>
            struct has_divide<T, U, typename First<Match, decltype(Instantiate<T>() / Instantiate<U>())>::type> : true_type
            {};

            template<typename T, typename H = Match>
            struct has_increment_prefix : false_type
            {};
            template<typename T>
            struct has_increment_prefix<T, typename First<Match, decltype(++Instantiate<T>())>::type> : true_type
            {};

            template<typename T, typename H = Match>
            struct has_increment_postfix : false_type
            {};
            template<typename T>
            struct has_increment_postfix<T, typename First<Match, decltype(Instantiate<T>()++)>::type> : true_type
            {};

            template<typename T, typename H = Match>
            struct is_weakly_incrementable : false_type
            {};
            template<typename T>
            struct is_weakly_incrementable<T, typename First<Match, decltype(++Instantiate<T>()++)>::type> : true_type
            {};

            template<typename T, typename H = Match>
            struct has_decrement_prefix : false_type
            {};
            template<typename T>
            struct has_decrement_prefix<T, typename First<Match, decltype(--Instantiate<T>())>::type> : true_type
            {};

            template<typename T, typename H = Match>
            struct has_decrement_postfix : false_type
            {};
            template<typename T>
            struct has_decrement_postfix<T, typename First<Match, decltype(Instantiate<T>()--)>::type> : true_type
            {};

            template<typename T, typename H = Match>
            struct is_weakly_decrementable : false_type
            {};
            template<typename T>
            struct is_weakly_decrementable<T, typename First<Match, decltype(--Instantiate<T>()--)>::type> : true_type
            {};
        }
        // \endcond
        template<typename T, typename U = T>
        struct has_plus : bool_constant<ops::has_plus<T, U>::value>
        {};
        template<typename T, typename U = T>
        struct has_minus : bool_constant<ops::has_minus<T, U>::value>
        {};
        template<typename T, typename U = T>
        struct has_multiply : bool_constant<ops::has_multiply<T, U>::value>
        {};
        template<typename T, typename U = T>
        struct has_divide : bool_constant<ops::has_divide<T, U>::value>
        {};
        template<typename T>
        struct has_increment_prefix : ops::has_increment_prefix<T>
        {};
        template<typename T>
        struct has_increment_postfix : ops::has_increment_postfix<T>
        {};
        template<typename T>
        struct has_decrement_prefix : ops::has_decrement_prefix<T>
        {};
        template<typename T>
        struct has_decrement_postfix : ops::has_decrement_postfix<T>
        {};
        template<typename T>
        struct is_weakly_incrementable : ops::is_weakly_incrementable<T>
        {};
        template<typename T>
        struct is_weakly_decrementable : ops::is_weakly_decrementable<T>
        {};

        template<typename T, typename U = T>
        struct is_addable : public mpl::op2<has_plus, T, U>
        {};
        template<typename T, typename U = T>
        struct is_subtractable : public mpl::op2<has_minus, T, U>
        {};
        template<typename T, typename U = T>
        struct is_multiplyable : public mpl::op2<has_multiply, T, U>
        {};
        template<typename T, typename U = T>
        struct is_dividable : public mpl::op2<has_divide, T, U>
        {};
        template<typename T, typename U = T>
        struct is_add_and_subtractable : bool_constant<is_addable<T, U>::value && is_subtractable<T, U>::value>
        {};
        template<typename T, typename U = T>
        struct is_multiply_and_dividable : bool_constant<is_multiplyable<T, U>::value && is_dividable<T, U>::value>
        {};

        template<typename T, typename U = T>
        struct is_addable_x : public mpl::op2x<has_plus, T, U>
        {};
        template<typename T, typename U = T>
        struct is_subtractable_x : public mpl::op2x<has_minus, T, U>
        {};
        template<typename T, typename U = T>
        struct is_multiplyable_x : public mpl::op2x<has_multiply, T, U>
        {};
        template<typename T, typename U = T>
        struct is_dividable_x : public mpl::op2x<has_divide, T, U>
        {};
        template<typename T, typename U = T>
        struct is_add_and_subtractable_x : bool_constant<is_addable_x<T, U>::value && is_subtractable_x<T, U>::value>
        {};
        template<typename T, typename U = T>
        struct is_multiply_and_dividable_x : bool_constant<is_multiplyable_x<T, U>::value && is_dividable_x<T, U>::value>
        {};

        template<typename T, typename U = T>
        struct can_do_arithmetics_x : bool_constant<is_add_and_subtractable_x<T, U>::value && is_multiply_and_dividable_x<T, U>::value>
        {};
        template<typename T, typename U = T>
        struct can_do_arithmetics : bool_constant<is_add_and_subtractable<T, U>::value && is_multiply_and_dividable<T, U>::value>
        {};
        template<typename T>
        struct is_strongly_incrementable
          : bool_constant<has_increment_prefix<T>::value && has_increment_postfix<T>::value && ! is_weakly_incrementable<T>::value>
        {};
        template<typename T>
        struct is_strongly_decrementable
          : bool_constant<has_decrement_prefix<T>::value && has_decrement_postfix<T>::value && ! is_weakly_decrementable<T>::value>
        {};
        template<typename T>
        struct is_strongly_in_and_decrementable
          : bool_constant<is_strongly_incrementable<T>::value && is_strongly_decrementable<T>::value>
        {};

        template<typename T, typename U>
        struct diff_type_unchecked
        {
            typedef decltype(Instantiate<T>() - Instantiate<U>()) type;
        };
        template<typename T, typename U>
        struct diff_type
        {
            typedef typename bool_to_types_type<diff_type_unchecked<T, U>, has_minus<T, U>::value>::type type;
        };

        template<typename T>
        struct is_array_index
          : bool_constant<(std::is_convertible<T, char>::value || std::is_convertible<T, unsigned char>::value ||
                           std::is_convertible<T, short>::value || std::is_convertible<T, unsigned short>::value ||
                           std::is_convertible<T, int>::value || std::is_convertible<T, unsigned int>::value ||
                           std::is_convertible<T, long>::value || std::is_convertible<T, unsigned long>::value ||
                           std::is_convertible<T, long long>::value || std::is_convertible<T, unsigned long long>::value ||
                           std::is_convertible<T, char>::value || std::is_convertible<T, unsigned char>::value) &&
                          ! (std::is_same<float, typename remove_cvref<T>::type>::value ||
                             std::is_same<double, typename remove_cvref<T>::type>::value)>
        {};
    }

#ifdef GYMPL_HAS_CONCEPTS
    namespace concepts
    {
        using namespace traits;

        template<typename T, typename U>
        concept CvRefRemovedIsSame = cv_ref_removed_is_same<T, U>::value;

        template<typename T>
        concept WeaklyIncrementable = requires(T x)
        {
            ++x++;
        };
        template<typename T>
        concept Incrementable = requires(T x)
        {
            (++x)++;
        };
        template<typename T>
        concept StronglyIncrementable = Incrementable<T> && ! WeaklyIncrementable<T>;

        template<typename T>
        concept WeaklyDecrementable = requires(T x)
        {
            --x--;
        };
        template<typename T>
        concept Decrementable = requires(T x)
        {
            (--x)--;
        };
        template<typename T>
        concept StronglyDecrementable = Decrementable<T> && ! WeaklyDecrementable<T>;

        template<typename T>
        // todo: debatable excluding floating point; maybe add opt-in
        concept StronglyInDecrementable = StronglyIncrementable<T>&& StronglyDecrementable<T>; // && !std::is_floating_point_v<T>;

        template<typename T, typename U = T>
        concept AddableX = requires(T x, U y)
        {
            x + y;
            y + x;
        };
        template<typename T, typename U = T>
        concept SubtractableX = requires(T x, U y)
        {
            x - y;
            y - x;
        };
        template<typename T, typename U = T>
        concept MultiplyableX = requires(T x, U y)
        {
            x* y;
            y* x;
        };
        template<typename T, typename U = T>
        concept DividableX = requires(T x, U y)
        {
            x / y;
            y / x;
        };

        template<typename T, typename U = T>
        concept Addable = requires(T x, U y)
        {
            x + x;
            y + y;
            x + y;
            y + x;
        };
        template<typename T, typename U = T>
        concept Subtractable = requires(T x, U y)
        {
            x - x;
            y - y;
            x - y;
            y - x;
        };
        template<typename T, typename U = T>
        concept Multiplyable = requires(T x, U y)
        {
            x* x;
            y* y;
            x* y;
            y* x;
        };
        template<typename T, typename U = T>
        concept Dividable = requires(T x, U y)
        {
            x / x;
            y / y;
            x / y;
            y / x;
        };

        template<typename T, typename U = T>
        concept AddAndSubtractableX = AddableX<T, U>&& SubtractableX<T, U>;
        template<typename T, typename U = T>
        concept MultiplyAndDividableX = MultiplyableX<T, U>&& DividableX<T, U>;

        template<typename T, typename U = T>
        concept AddAndSubtractable = Addable<T, U>&& Subtractable<T, U>;
        template<typename T, typename U = T>
        concept MultiplyAndDividable = Multiplyable<T, U>&& Dividable<T, U>;

        template<typename T, typename U = T>
        concept CanDoArithmeticsX = AddableX<T, U>&& SubtractableX<T, U>&& MultiplyableX<T, U>&& DividableX<T, U>;

        template<typename T, typename U = T>
        concept CanDoArithmetics = Addable<T, U>&& Subtractable<T, U>&& Multiplyable<T, U>&& Dividable<T, U>;

        template<typename T>
        concept IsArrayIndex = (bool)is_array_index<T>::value;

        // ranges (todo)

        // see std::ranges::equal_to - https://en.cppreference.com/w/cpp/utility/functional/ranges/equal_to
        template<typename T, typename U>
        concept CompDeclv = requires(T t, U u)
        {
            std::declval<T>() == std::declval<U>();
        };
        template<typename T, typename U>
        concept CompDeclvOrEqualityComparableWith = CompDeclv<T, U> || std::equality_comparable_with<T, U>;
    }
#endif
}

#if _MSC_VER <= 1900
#pragma warning(pop)
#endif

#endif
