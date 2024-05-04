/*
	             Copyright Christian Volmer 2024.
	Distributed under the Boost Software License, Version 1.0.
	     (See accompanying file LICENSE_1_0.txt or copy at
	          https://www.boost.org/LICENSE_1_0.txt)
*/

/*
	Test that parses random string representations to random number bases into integers, converts the result back to a string, and confirms that both strings match.
*/

#pragma once

template<typename integerT>
inline bool string_test()
{
	constexpr static char digits[2 * 36 + 1] = "00112233445566778899aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ";

	int base = std::uniform_int_distribution<int>(2, 36)(g_RandomEngine);
	size_t length = std::uniform_int_distribution<size_t>(1, 100)(g_RandomEngine);

	std::string str1;
	str1.resize(length);

	std::uniform_int_distribution<int> digit_distribution(0, 2 * base - 1);

	for (size_t i = 0; i < length; ++i)
		str1[i] = digits[digit_distribution(g_RandomEngine)];

	// Remove leading zeros
	while ((str1.length() > 1) && str1[0] == '0')
		str1 = str1.substr(1);

	// Negate at random
	if ((str1.length() > 1) || ((str1.length() == 1) && (str1[0] != '0')))
		if (std::uniform_int_distribution<int>(0, 1)(g_RandomEngine) == 1)
			str1 = "-" + str1;

	integerT number = integerT::from_string(str1, base);
	std::string str2 = number.to_string(base);

	for (auto &c : str1)
		c = static_cast<std::string::value_type>(std::tolower(c));

	if (str1 != str2) {

		std::cout << "\n";
		std::cout << "FAILED string round-trip test for\n";
		std::cout << "  str1 = " << str1 << "\n";
		std::cout << "  str2 = " << str2 << "\n";
		std::cout << "\n";

		return false;
	}

	return true;
}
