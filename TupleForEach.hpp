#ifndef MVG_TUPLE_FOR_EACH_HPP_
#define MVG_TUPLE_FOR_EACH_HPP_

#include <tuple>

namespace TupleForEach
{
	namespace detail
	{
		template<std::size_t I, typename F, typename...TupleTs, typename... Args>
		static constexpr 
		std::enable_if_t<I == sizeof...(TupleTs), void>
		doForEach([[maybe_unused]] std::tuple<TupleTs...>& t, [[maybe_unused]] F&& f, [[maybe_unused]] Args&&... args)
		{
			
		}

		template<std::size_t I, typename F, typename... TupleTs, typename... Args>
		static constexpr
			std::enable_if_t < I < sizeof...(TupleTs), void>
			doForEach(std::tuple<TupleTs...>& t, F&& f, Args&&... args)
		{
			constexpr std::size_t size = std::tuple_size<std::tuple<TupleTs...>>::value;

			f(std::get<I>(t));
			if constexpr (I < size)
				doForEach<I + 1, F, TupleTs..., Args...>(t, std::forward<F>(f), std::forward<Args>(args)...);
		}

		//const version
		template<std::size_t I, typename F, typename...TupleTs, typename... Args>
		static constexpr
			std::enable_if_t<I == sizeof...(TupleTs), void>
			doForEach([[maybe_unused]] std::tuple<TupleTs...> const& t, [[maybe_unused]] F&& f, [[maybe_unused]] Args&&... args)
		{

		}

		template<std::size_t I, typename F, typename... TupleTs, typename... Args>
		static constexpr
			std::enable_if_t< I < sizeof...(TupleTs), void>
			doForEach(std::tuple<TupleTs...> const& t, F&& f, Args&&... args)
		{
			constexpr std::size_t size = std::tuple_size<std::tuple<TupleTs...>>::value;

			f(std::get<I>(t));
			if constexpr (I < size)
				doForEach<I + 1, F, TupleTs..., Args...>(t, std::forward<F>(f), std::forward<Args>(args)...);
		}
	}

	template<typename F, typename... TupleTs, typename... Args >
	static constexpr void foreach(std::tuple<TupleTs...>& t, F&& f, Args&&... args)
	{
		detail::doForEach<0, F, TupleTs..., Args...>(t, std::forward<F>(f), std::forward<Args>(args)...);
	}

	//const version
	template<typename F, typename... TupleTs, typename... Args>
	static constexpr void foreach(std::tuple<TupleTs...> const& t, F&& f, Args&&... args)
	{
		detail::doForEach<0, F, TupleTs..., Args...>(t, std::forward<F>(f), std::forward<Args>(args)...);
	}

	namespace detail
	{
		template<std::size_t I, typename F, typename... TupleTs, typename... Args>
		static constexpr
			std::enable_if_t< I == sizeof...(TupleTs), void>
			doParallelForEach(
				[[maybe_unused]] std::tuple<TupleTs...>& a,
				[[maybe_unused]] std::tuple<TupleTs...>& b,
				[[maybe_unused]] F&& f,
				[[maybe_unused]] Args&&... args)
		{

		}

		template<std::size_t I, typename F, typename... TupleTs, typename... Args>
		static constexpr
			std::enable_if_t < I < sizeof...(TupleTs), void >
			doParallelForEach(std::tuple<TupleTs...>& a, std::tuple<TupleTs...>& b, F&& f, Args&&... args)
		{
			constexpr std::size_t size = std::tuple_size<std::tuple<TupleTs...>>::value;

			f(std::get<I>(a), std::get<I>(b));
			if constexpr (I < size)
				doParallelForEach<I + 1, F, TupleTs..., Args...>(a, b, std::forward<F>(f), std::forward<Args>(args)...);
		}

		//const version
		template<std::size_t I, typename F, typename... TupleTs, typename... Args>
		static constexpr 
			std::enable_if_t< I == sizeof...(TupleTs), void>
			doParallelForEach(
				[[maybe_unused]] std::tuple<TupleTs...> const& a,
				[[maybe_unused]] std::tuple<TupleTs...> const& b,
				[[maybe_unused]] F&& f,
				[[maybe_unused]] Args&&... args)
		{

		}

		template<std::size_t I, typename F, typename... TupleTs, typename... Args>
		static constexpr
			std::enable_if_t< I < sizeof...(TupleTs), void >
			doParallelForEach(std::tuple<TupleTs...> const& a, std::tuple<TupleTs...> const& b, F&& f, Args&&... args)
		{
			constexpr std::size_t size = std::tuple_size<std::tuple<TupleTs...>>::value;

			f(std::get<I>(a), std::get<I>(b));
			if constexpr (I < size)
				doParallelForEach<I + 1, F, TupleTs..., Args...>(a, b, std::forward<F>(f), std::forward<Args>(args)...);
		}
	} //namespace detail

	//Parallel foreach

	template<typename F, typename... TupleTs, typename... Args>
	static constexpr void parallel_foreach(std::tuple<TupleTs...>& a, std::tuple<TupleTs...>& b, F&& f, Args&&... args)
	{
		detail::doParallelForEach<0, F, TupleTs..., Args...>(a, b, std::forward<F>(f), std::forward<Args>(args)...);
	}

	//const version
	template<typename F, typename... TupleTs, typename... Args>
	static constexpr void parallel_foreach(std::tuple<TupleTs...> const& a, std::tuple<TupleTs...> const& b, F&& f, Args&&... args)
	{
		detail::doParallelForEach<0, F, TupleTs..., Args...>(a, b, std::forward<F>(f), std::forward<Args>(args)...);
	}
}

#endif
