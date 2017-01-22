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
		constexpr std::size_t size() const { return Count; };

		template<std::size_t Index> 
		auto get() { 
			static_assert(Index < Count, "get<Index>() : Index is out of range.");
			return (get(element<Index> {})); 
		};

		template<std::size_t... Indices>
		decltype(auto) collect() {
			auto locol = make_metoople(get<Indices>()...);
			std::cout << "locol : ";
			locol.foreach([](auto x) {std::cout << x << " "; });
			std::cout << std::endl;
			return locol;
		}
	private:
		template<std::size_t N, std::size_t M> struct selector {};

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
	MeToople<sizeof...(Types), Types...> make_metoople(const Types&... args) {
		return MeToople<sizeof...(Types), Types...>(args...);
	}

} // namespace rsz

#endif // METOOPLE_HPP
