/* 
 * Everyone has a tuple implementation. Me too!
 * 
 * Copyright (c) Rahman Salim Zengin, 2016
 * rsz@gufatek.com
 */

#ifndef METOOPLE_HPP
#define METOOPLE_HPP

#include <type_traits>

namespace rsz {

	template<int N> using element = std::integral_constant<int, N>;
	
	template<int Count, typename ElemType = void, typename... Types>
	struct MeToople : MeToople<Count, Types...> {
		using super = MeToople<Count, Types...>;
		const ElemType& elem;

		MeToople(const ElemType& elem, const Types&... args)
			: MeToople<Count, Types...>(args...), elem(elem) {}

		// To make all overloads visible;
		using super::get;

		const ElemType& get(element<(Count - sizeof...(Types) - 1)>) {
			return elem;
		}

		template<int Index> auto get() {
			return get(element<Index> {});
		};


	};
	template<int Count> struct MeToople<Count> { 
		void get() { static_assert(false, "Index required"); }; 
	};

	template<typename... Types>
	MeToople<sizeof...(Types), Types...> make_metoople(const Types&... args) {
		return MeToople<sizeof...(Types), Types...>(args...);
	}

	template<int Index, typename Tuple> 
	auto get(const Tuple& tuple) {
		return tuple.get(element<Index> {});
	};

} // namespace rsz

#endif // METOOPLE_HPP
