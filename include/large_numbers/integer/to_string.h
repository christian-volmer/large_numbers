/*
	             Copyright Christian Volmer 2024.
	Distributed under the Boost Software License, Version 1.0.
	     (See accompanying file LICENSE_1_0.txt or copy at
	          https://www.boost.org/LICENSE_1_0.txt)
*/

/*
	<no description>
*/

#pragma once

namespace large_numbers {

template<typename limbT>
inline std::string integer<limbT>::to_string(int base /* = 10 */) const
{
	constexpr static char digits[37] = "0123456789abcdefghijklmnopqrstuvwxyz";

	if (base < 2 && base > 36)
		throw std::invalid_argument("integer::to_string(): parameter 'base' must be an integer between 2 and 36.");

	if (zero())
		return "0";

	if (negative())
		return "-" + (-(*this)).to_string(base);

	std::string s;

	this_type large_base = (signed char)(base);

	this_type value(*this);

	while (!value.zero()) {

		this_type quotient = value.quotient_remainder(large_base);

		s.push_back(digits[value.limb_at_extend(0)]);

		value = quotient;
	}

	std::reverse(s.begin(), s.end());
	return s;
}

} // namespace large_numbers
