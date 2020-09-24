#pragma once
#ifndef HAS_OPERATOR_HPP
#define HAS_OPERATOR_HPP



#include <type_traits>
#include <utility>


template <typename T, typename = void >
struct has_equal : std::false_type {};

template<typename T>
struct has_equal<T,
    std::enable_if_t<
    std::is_convertible_v<
    decltype(std::declval<T>() == std::declval<T>()),
    bool
    >
    >
> : std::true_type {};


template <typename T, typename = void>
struct has_less : std::false_type {};

template <typename T>
struct has_less<T,
    std::enable_if_t <
    std::is_convertible_v <decltype(std::declval<T>() < std::declval<T>()), bool
    >
    >
    > : std::true_type{};

template <typename T>
constexpr bool has_equal_v = has_equal<T>::value;


template <typename T>
constexpr bool has_less_v = has_less<T>::value;

#endif // !HAS_OPERATOR_HPP