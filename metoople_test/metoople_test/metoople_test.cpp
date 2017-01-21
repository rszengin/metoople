/* 
 * Copyright (c) Rahman Salim Zengin, 2017
 * rsz@gufatek.com
 */

#include "..\..\include\metoople.hpp"
#include <iostream>
#include <typeinfo>

int main()
{
	using namespace rsz;

	auto d_u_t = make_metoople(1, 2.2f, 3.3, '4', "ABCDEF");

	auto view = [](const auto& elem) { 
		std::cout << typeid(elem).name() << "(" << elem << ") "; };

	//view(d_u_t.elem);
	//view(d_u_t.super::elem);
	//view(d_u_t.super::super::elem);
	//view(d_u_t.super::super::super::elem);
	//view(d_u_t.super::super::super::super::elem);
	//std::cout << std::endl;

	//view(d_u_t.get(element<0>{}));
	//view(d_u_t.get(element<1>{}));
	//view(d_u_t.get(element<2>{}));
	//view(d_u_t.get(element<3>{}));
	//view(d_u_t.get(element<4>{}));
	//std::cout << std::endl;

	view(d_u_t.get<0>());
	view(d_u_t.get<1>());
	view(d_u_t.get<2>());
	view(d_u_t.get<3>());
	view(d_u_t.get<4>());
	std::cout << std::endl;

	std::cout << "Size : " << d_u_t.size() << std::endl;

    return 0;
}

