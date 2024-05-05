/*
                 Copyright Christian Volmer 2024.
    Distributed under the Boost Software License, Version 1.0.
         (See accompanying file LICENSE_1_0.txt or copy at
              https://www.boost.org/LICENSE_1_0.txt)
*/

/*
    Compares the result of division using native C++ types against our own implementation.
*/

#pragma once

#include <limits>

#include "testing.h"

template<typename integerT>
inline bool native_division_test()
{
	std::intmax_t smallest = std::numeric_limits<std::intmax_t>::min() + 1;
	std::intmax_t largest = std::numeric_limits<std::intmax_t>::max();

	auto distribution = std::uniform_int_distribution<intmax_t>(smallest, largest);

	std::intmax_t native_dividend = distribution(g_RandomEngine);
	std::intmax_t native_divisor = 0;

	while (native_divisor == 0) {

		native_divisor = distribution(g_RandomEngine);
		native_divisor >>= std::uniform_int_distribution<int>(0, sizeof(std::intmax_t) * 8 - 1)(g_RandomEngine);
	}

	std::intmax_t native_quotient = native_dividend / native_divisor;
	std::intmax_t native_remainder = native_dividend % native_divisor;

	integerT large_dividend = native_dividend;
	integerT large_divisor = native_divisor;

	integerT large_quotient = large_dividend / large_divisor;
	integerT large_remainder = large_dividend % large_divisor;

	if ((large_quotient != native_quotient) || (large_remainder != native_remainder)) {

		std::cout << "\n";
		std::cout << "FAILED native division test for\n";
		std::cout << "  dividend = " << native_dividend << "\n";
		std::cout << "  divisor = " << native_divisor << "\n";
		std::cout << "\n";

		return false;
	}

	return true;
}
