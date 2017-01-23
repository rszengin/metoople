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
			static_assert(Index < Count, "get() : Index is out of range.");
			return (get(element<Index> {})); 
		};

		template<std::size_t... Indices>
		decltype(auto) collect() {
			return make_metoople(get<Indices>()...);
		}
	private:
		/* The range is including Final */
		template<std::size_t Current, std::size_t Step, std::size_t Final, typename Func>
		std::enable_if_t<(Current <= Final)> for_helper(Func func) {
			func(get<Current>());
			for_helper<Current + Step, Step, Final>(func);
		};
		template<std::size_t Current, std::size_t Step, std::size_t Final, typename Func>
		std::enable_if_t<(Current > Final)> for_helper(Func func) {};
	public:
		template<typename Func>
		void foreach(Func func) {
			for_helper<0, 1, Count - 1>(func);
		}

		template<std::size_t Initial, std::size_t Step = 1, std::size_t Final = (Count - 1), typename Func>
		void for_range(Func func) {
			static_assert((Final < Count), "for_range() : Range error.");
			for_helper<Initial, Step, Final>(func);
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
