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
inline basic_integer<limbT> basic_integer<limbT>::from_string(std::string const &str, int base /* = 10 */)
{
	if (base < 2 && base > 36)
		throw std::invalid_argument("basic_integer::from_string(): parameter 'base' must be an integer between 2 and 36.");

	this_type result;

	auto i = str.cbegin();
	auto end = str.cend();

	while (i != end && std::isspace(*i))
		++i;

	bool negate_result = false;

	if (i != end && *i == '+')
		++i;
	else if (i != end && *i == '-') {

		negate_result = true;
		++i;
	}

	this_type large_base = static_cast<signed char>(base);

	for (; i != end; ++i) {

		signed char digit = static_cast<signed char>(base);

		if (*i >= '0' && *i <= '9')
			digit = *i - '0';
		else if (*i >= 'a' && *i <= 'z')
			digit = 10 + (*i - 'a');
		else if (*i >= 'A' && *i <= 'Z')
			digit = 10 + (*i - 'A');

		if (digit >= base)
			break;

		result *= large_base;
		result += digit;
	}

	if (negate_result)
		return -result;
	else
		return result;
}

} // namespace large_numbers
