#ifndef TYPE_LIST_HPP_
#define TYPE_LIST_HPP_

#include <tuple>
#include <cstddef>

template<typename... Types>
struct TypeList
{
	template<typename U>
	using push_back_t = typename TypeList<Types..., U>;

	template<typename U>
	using push_front_t = typename TypeList<U, Types...>;

	template<template<typename...> typename FuncT>
	using apply_t = FuncT<Types...>;

	template<template<typename> typename FuncT>
	using map_t = TypeList<FuncT<Types>...>;

	constexpr std::size_t size() const
	{
		return std::tuple_size<TupleT>::value;
	}

	using TupleT = std::tuple<Types...>;
};

#endif
