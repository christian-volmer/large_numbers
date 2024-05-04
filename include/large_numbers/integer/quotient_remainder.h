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
inline integer<limbT> integer<limbT>::quotient_remainder(this_type divisor, this_type const offset /* = this_type() */)
{
	if (!offset.zero()) {

		*this -= offset;
		this_type q = quotient_remainder(divisor);
		*this += offset;
		return q;
	}
	else if (divisor.negative()) {

		negate();
		this_type q = quotient_remainder(-divisor);
		negate();
		return q;
	}
	else if (negative()) {

		negate();
		this_type q = quotient_remainder(divisor);
		if (zero())
			return -q;
		else {

			*this = divisor - *this;
			return -(q + 1);
		}
	}
	else {

		assert(!negative());
		assert(!divisor.negative());
		assert(offset.zero());

		// Normalise the divisor

		size_t divisor_limb_size = divisor.limb_size();

		if (divisor_limb_size == 0)
			throw std::domain_error("Division by zero.");

		ptrdiff_t normalization_shift = backend::normalize(divisor.limb_data(), divisor_limb_size);

		// Prepare the dividend

		size_t dividend_limb_size = limb_size();

		if (normalization_shift > 0) {

			limb_resize(dividend_limb_size + 1);
			backend::shift_left(limb_data(), limb_capacity(), false, normalization_shift);

			dividend_limb_size = limb_size();
		}

		this_type quotient;

		if (divisor_limb_size <= dividend_limb_size) {

			size_t quotient_limb_capacity = dividend_limb_size + 1 - divisor_limb_size;
			quotient.limb_resize(quotient_limb_capacity);

			backend::quotient_remainder(quotient.limb_data(), quotient_limb_capacity, limb_data(), dividend_limb_size, divisor.limb_data(), divisor_limb_size);
		}

		backend::shift_right(limb_data(), limb_capacity(), false, normalization_shift);

		return quotient;
	}
}

} // namespace large_numbers
