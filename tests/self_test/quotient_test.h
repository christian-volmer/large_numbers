/*
                 Copyright Christian Volmer 2024.
    Distributed under the Boost Software License, Version 1.0.
         (See accompanying file LICENSE_1_0.txt or copy at
              https://www.boost.org/LICENSE_1_0.txt)
*/

/*
    Test that calculates quotient and remainder of the division of random integers and checks if the results can be combined back to give the original dividend.
*/

#pragma once

#include "testing.h"

template<typename integerT>
inline bool quotient_test()
{
	integerT a = random_integer<integerT>(random_capacity());
	integerT b = random_integer<integerT>(random_capacity());
	integerT c = random_integer<integerT>(random_capacity());

	integerT r = a;

	try {

		integerT q = r.quotient_remainder(b, c);

		if (!(q * b + r == a)) {

			std::cout << "\n";
			std::cout << "FAILED quotient test for\n";
			std::cout << "  a = " << a.to_string() << "\n";
			std::cout << "  b = " << b.to_string() << "\n";
			std::cout << "  c = " << c.to_string() << "\n";
			std::cout << "with\n";
			std::cout << "  q = " << q.to_string() << "\n";
			std::cout << "  r = " << r.to_string() << "\n";
			std::cout << "\n";

			return false;
		}
	}
	catch (std::domain_error const &) {

		if (b) {
			std::cout << "\n";
			std::cout << "FAILED quotient test for\n";
			std::cout << "  a = " << a.to_string() << "\n";
			std::cout << "  b = " << b.to_string() << "\n";
			std::cout << "  c = " << c.to_string() << "\n";
			std::cout << "with wrongly generated division by zero exception.\n";

			return false;
		}
	}

	return true;
}
