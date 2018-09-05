#ifndef MVG_TUPLE_FOR_EACH_HPP_
#define MVG_TUPLE_FOR_EACH_HPP_

#include <tuple>

namespace TupleForEach
{
	namespace detail
	{
		template<std::size_t I, typename F, typename...TupleTs>
		static constexpr 
		std::enable_if_t<I == sizeof...(TupleTs), void>
		doForEach(std::tuple<TupleTs...>& t, F f)
		{
			(void)t; //Get rid of warnings about 't' being unused
			(void)f; //Same as above
		}

		template<std::size_t I, typename F, typename... TupleTs>
		static constexpr 
		std::enable_if_t<I < sizeof...(TupleTs), void>
		doForEach(std::tuple<TupleTs...>& t, F& f)
		{
			static constexpr std::size_t size = std::tuple_size<std::tuple<TupleTs...>>::value;
			
			f(std::get<I>(t));
			if constexpr (I < size)
				doForEach<I + 1, F, TupleTs...>(t, f);
		}
	};

	template<typename F, typename... TupleTs>
	static constexpr void foreach(std::tuple<TupleTs...>& t, F& f)
	{
		detail::doForEach<0, F, TupleTs...>(t, f);
	}
};

#endif
