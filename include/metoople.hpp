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

	
	template<int Count, typename ElemType = void, typename... Types>
	class MeToople : protected MeToople<Count, Types...> {
		using super = MeToople<Count, Types...>;
		const ElemType& elem;
		static constexpr std::size_t index{ (Count - sizeof...(Types) - 1) };
	public:
		MeToople(const ElemType& elem, const Types&... args)
			: MeToople<Count, Types...>(args...), elem(elem) {}
	protected:
		template<std::size_t N> 
		using element = std::integral_constant<std::size_t, N>;

		// Creating a function overload for every instance
		const ElemType& get(element<index>) { return elem; };

		using super::get; // Making all overloads visible
	public:
		template<std::size_t Index> 
		auto get() { return get(element<Index> {}); };

		std::size_t size() { return Count; };
	};
	template<int Count> class MeToople<Count> { 
	protected:
		void get() {}; // Required by the parent instance
	};

	template<typename... Types>
	MeToople<sizeof...(Types), Types...> make_metoople(const Types&... args) {
		return MeToople<sizeof...(Types), Types...>(args...);
	}

} // namespace rsz

#endif // METOOPLE_HPP
