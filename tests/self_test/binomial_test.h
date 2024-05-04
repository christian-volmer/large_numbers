/*
	             Copyright Christian Volmer 2024.
	Distributed under the Boost Software License, Version 1.0.
	     (See accompanying file LICENSE_1_0.txt or copy at
	          https://www.boost.org/LICENSE_1_0.txt)
*/

/*
	Performs basic arithmetic operations on random integers and checks by means of several basic identities -- some of which are the binomial formulas -- if the computations are correct.
*/

#pragma once

#include "testing.h"

template<typename integerT>
inline bool binomial_test()
{
	integerT a = random_integer<integerT>(random_capacity());
	integerT b = random_integer<integerT>(random_capacity());

	bool equation1 = a - b == -(b - a);
	bool equation2 = a * b == b * a;
	bool equation3 = a * a - b * b == (a - b) * (a + b);
	bool equation4 = a * a + 2 * a * b + b * b == (a + b) * (a + b);
	bool equation5 = a * a - 2 * a * b + b * b == (a - b) * (a - b);

	if (!(equation1 && equation2 && equation3 && equation4 && equation5)) {

		std::cout << "\n";
		std::cout << "FAILED binomial formula test for\n";
		std::cout << "  a = " << a.to_string() << "\n";
		std::cout << "  b = " << b.to_string() << "\n";
		std::cout << "\n";

		return false;
	}

	return true;
}
