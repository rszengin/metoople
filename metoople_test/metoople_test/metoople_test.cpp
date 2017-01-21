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

	std::cout << d_u_t.elem << ", " 
		<< d_u_t.super::elem << ", "
		<< d_u_t.super::super::elem << ", " 
		<< d_u_t.super::super::super::elem << ", "
		<< d_u_t.super::super::super::super::elem << std::endl;

	//view(d_u_t.get()); // Error!
	view(d_u_t.get(element<0>{}));
	view(d_u_t.get(element<1>{}));
	view(d_u_t.get(element<2>{}));
	view(d_u_t.get(element<3>{}));
	view(d_u_t.get(element<4>{}));
	std::cout << std::endl;
	
    return 0;
}

