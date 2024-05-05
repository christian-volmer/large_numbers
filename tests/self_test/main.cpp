/*
                 Copyright Christian Volmer 2024.
    Distributed under the Boost Software License, Version 1.0.
         (See accompanying file LICENSE_1_0.txt or copy at
              https://www.boost.org/LICENSE_1_0.txt)
*/

/*
    Entry point of the large number library self-test. Runs different types of arithmentic tests on random numbers with large integer types based on 8, 16, and 32 bit limb sizes.
*/

#include <chrono>
#include <functional>
#include <iostream>
#include <random>

#include <large_numbers.h>

#include "binomial_test.h"
#include "quotient_test.h"
#include "string_test.h"
#include "native_division.h"

// Runs tests on the given integer type for the duration given in seconds
// as the paramter `testTime_s`.
template<typename integerT>
bool test_suite(double testTime_s)
{
	struct test_definition {

		std::string name;
		bool (*function)();
	};

	std::vector<test_definition> tests = {

		{ "Binomial formula test", binomial_test<integerT> },
		{ "Quotient-remainder test", quotient_test<integerT> },
		{ "String round-trip test", string_test<integerT> },
		{ "Comparison against native division", native_division_test<integerT> }
	};

	std::cout << "Testing limb-size = " << integerT::traits::bits_per_limb << " bits.\n";
	std::cout << "\n";

	bool success = true;

	for (auto const &test : tests) {

		std::cout << "  " << test.name << "...";

		auto startTime = std::chrono::steady_clock::now();
		auto endTime = startTime;
		size_t count = 0;

		do {

			success &= test.function();
			++count;

		} while (std::chrono::duration<double>((endTime = std::chrono::steady_clock::now()) - startTime).count() < testTime_s);

		std::cout << " completed " << count << " tests in " << std::chrono::duration<double>(endTime - startTime).count() << " seconds.\n";
	}

	std::cout << "\n";

	return success;
}

int main()
{
	auto seed = (std::random_device())();
	std::cout << "seed = " << seed << "\n";
	g_RandomEngine.seed(seed);

	bool success = true;

	double const testTime_s = 1.0;

	success &= test_suite<large_numbers::integer_8>(testTime_s);
	success &= test_suite<large_numbers::integer_16>(testTime_s);
	success &= test_suite<large_numbers::integer_32>(testTime_s);

	return !success;
}
