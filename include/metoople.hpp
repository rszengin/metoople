/* 
 * Everyone has a tuple implementation. Me too!
 * 
 * Copyright (c) Rahman Salim Zengin, 2016
 * rsz@gufatek.com
 */

#ifndef METOOPLE_HPP
#define METOOPLE_HPP

#include <type_traits>
#include <utility>

namespace rsz {

	template<int Count, typename ElemType = void, typename... Types>
	class MeToople : protected MeToople<Count, Types...> {
		using super = MeToople<Count, Types...>;
		static constexpr std::size_t INDEX{ (Count - sizeof...(Types) - 1) };

		template<std::size_t N, std::size_t M> struct selector {};

		ElemType&& elem;
	public:
		MeToople(ElemType&& elem, const Types&&... args)
			: MeToople<Count, Types...>(args...), elem(elem) {}
	protected:
		template<std::size_t N> 
		using element = std::integral_constant<std::size_t, N>;

		// Creating a function overload for every instance
		ElemType& get(element<INDEX>) { return elem; };

		using super::get; // Making all overloads visible
	public:
		constexpr std::size_t size() const { return Count; };

		template<std::size_t Index> 
		decltype(auto) get() { 
			static_assert(Index < Count, "get<Index>() : Index is out of range.");
			return (get(element<Index> {})); 
		};

		template<std::size_t... Indices>
		decltype(auto) collect() {
			return make_metoople(get<Indices>()...);
		}
	private:

		template<std::size_t Current, std::size_t Final, typename Func>
		void foreach_helper(selector<Current, Final>, Func func) {
			func(get<Current>());
			foreach_helper(selector<Current + 1, Final> {}, func);
		};
		template<std::size_t Final, typename Func>
		void foreach_helper(selector<Final, Final>, Func func) {
			func(get<Final>());
		};
	public:
		template<typename Func>
		void foreach(Func func) {
			foreach_helper(selector<0, Count - 1> {}, func);
		}
	};
	template<int Count> class MeToople<Count> {
	protected:
		void get() {}; // Required by the parent instance
	};

	template<typename... Types>
	MeToople<sizeof...(Types), Types...> make_metoople(Types&&... args) {
		return MeToople<sizeof...(Types), Types...>(args...);
	}

} // namespace rsz

#endif // METOOPLE_HPP
