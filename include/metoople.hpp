/* 
 * Everyone has a tuple implementation. Me too!
 * 
 * Copyright (c) Rahman Salim Zengin, 2016
 * rsz@gufatek.com
 */

#ifndef METOOPLE_HPP_
#define METOOPLE_HPP_

#include <type_traits>
#include <utility>

namespace rsz {

	template<std::size_t N> struct Element {};

	template<typename T, typename... Types>
	class Metoople_base : protected Metoople_base<Types...> {
		using parent = Metoople_base<Types...>;
		T& elem;
	protected:
		Metoople_base(T& elem, Types&... others)
			: elem(elem), parent(others...) {}

		using parent::get; // Making all overloads visible

		// Creating a function overload for every instance
		T& get(Element<sizeof...(Types)>) { return elem; }
	};

	template<typename T>
	class Metoople_base<T> {
		T& elem;
	protected:
		Metoople_base(T& elem) : elem(elem) {}

		// Creating a function overload for every instance
		T& get(Element<0>) { return elem; }
	};

	template<typename... Types>
	class Metoople : private Metoople_base<Types...> {
		using parent = Metoople_base<Types...>;
		static constexpr std::size_t COUNT{ sizeof...(Types) };
	public:
		Metoople(Types&&... args) : parent(args...) {}

		constexpr std::size_t size() const { return COUNT; }

		template<std::size_t Index>
		decltype(auto) get() { 
			static_assert(Index < COUNT, "get() : Index is out of range.");
			return (parent::get(Element<(COUNT - Index - 1)>{})); 
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
			for_helper<0, 1, COUNT - 1>(func);
		}

		/* (Final == -1) -> Final = COUNT - 1 */
		template<std::size_t Initial, std::size_t Final = -1, std::size_t Step = 1, typename Func>
		void for_range(Func func) {
			for_helper<Initial, Step, ((Final < COUNT) ? Final : (COUNT - 1))>(func);
		}

		template<std::size_t... Indices>
		decltype(auto) collect() {
			return make_metoople(get<Indices>()...);
		}
	};

	template<typename... Types>
	Metoople<Types...> make_metoople(Types&&... args) {
		return Metoople<Types...>(std::forward<Types>(args)...);
	}

} // namespace rsz

#endif // METOOPLE_HPP_
