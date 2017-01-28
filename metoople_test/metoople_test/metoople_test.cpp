/* 
 * Copyright (c) Rahman Salim Zengin, 2017
 * rsz@gufatek.com
 */

#include "..\..\include\metoople.hpp"
#include <iostream>
#include <typeinfo>
#include <algorithm>

using namespace rsz;

int main()
{
	const auto a{ 1 };
	const auto b{ 2.2f };
	auto c{ 3.3 };
	auto d{ '4' };
	const auto e{ "ABCDEF" };

	auto view = [](const auto& elem) { 
		std::cout << typeid(elem).name() << "(" << elem << ") "; };

	//auto d_u_t = make_metoople(1, 2.2f, 3.3, '4', "ABCDEF");
	auto d_u_t = make_metoople(a, b, c, d, e, 1, 2.2f, 3.3, '4', "ABCDEF");

	view(d_u_t.get<0>());
	view(d_u_t.get<1>());
	view(d_u_t.get<2>());
	view(d_u_t.get<3>());
	view(d_u_t.get<4>());
	std::cout << " Size : " << d_u_t.size() << std::endl;
	d_u_t.foreach(view);
	std::cout << std::endl;

	auto manual_collection = make_metoople(d_u_t.get<0>(), d_u_t.get<2>(), d_u_t.get<4>());
	manual_collection.foreach(view);
	std::cout << std::endl;

	auto&& collection = d_u_t.collect<0, 2, 5>();
	std::cout << "Type info of \"collection\" : " << typeid(collection).name() << std::endl;
	view(collection.get<0>());
	view(collection.get<1>());
	view(collection.get<2>());
	std::cout << std::endl;
	collection.foreach(view);
	std::cout << std::endl;

	d_u_t.collect<0, 2, 5>().foreach(view);
	std::cout << std::endl;

	d_u_t.for_range<0>(view);
	std::cout << std::endl;

	d_u_t.for_range<1, 8, 1>(view);
	std::cout << std::endl;

	d_u_t.for_range<0, -1, 2>(view);
	std::cout << std::endl;

	d_u_t.for_range<1, 9, 2>(view);
	std::cout << std::endl;

	Metoople<char, int, double> test_metoople('c', 135, 1234.5678);
	view(test_metoople.get<0>());
	view(test_metoople.get<1>());
	view(test_metoople.get<2>());
	std::cout << std::endl;

	test_metoople.get<0>() = 'd';
	test_metoople.get<1>() = 225;
	test_metoople.get<2>() = 1.234;
	test_metoople.foreach(view);
	std::cout << std::endl;

    return 0;
}

