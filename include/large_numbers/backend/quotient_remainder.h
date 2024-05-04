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
namespace backend {

inline constexpr static size_t const division_by_zero = static_cast<size_t>(-1);

template<typename limb_type>
inline size_t quotient_remainder(
	limb_type *quotient, size_t quotient_capacity,
	limb_type *dividend, size_t dividend_size,
	limb_type const *divisor, size_t divisor_size) noexcept
{
	using traits = limb_traits<limb_type>;
	using intermediate_type = typename traits::intermediate_type;

	// Determine the true size of the divisor
	while (divisor_size > 0 && divisor[divisor_size - 1] == 0)
		--divisor_size;

	if (divisor_size == 0)
		return division_by_zero;

	// Extract the most significant limb
	limb_type divisor_msl = divisor[divisor_size - 1];

	// Determine the size of the quotient
	ptrdiff_t quotient_size = dividend_size >= divisor_size
		? dividend_size + 1 - divisor_size
		: 0;

	// Initialise the quotient where necessary
	for (ptrdiff_t quotient_i = std::max<ptrdiff_t>(0, quotient_size - 1); quotient_i < static_cast<ptrdiff_t>(quotient_capacity); ++quotient_i)
		quotient[quotient_i] = 0;

	// If at this point the quotient is known to be zero, terminate.
	if (quotient_size == 0)
		return 0;

	// Determine the most significant limb of the quotient
	ptrdiff_t quotient_i = quotient_size - 1;

	// NOTE: the following can loop very often unless the divisor is normalised
	while (compare(dividend, dividend_size, false, 0, divisor, divisor_size, false, quotient_i) > 0) {

		subtract_from(dividend, dividend_size, divisor, divisor_size, false, quotient_i);
		if (quotient_i < static_cast<ptrdiff_t>(quotient_capacity))
			++quotient[quotient_i];
	}

	--quotient_i;

	// Determine the remaining limbs of the quotient

	assert(quotient_i + divisor_size + 1 == dividend_size);
	assert(divisor_size > 0);

	for (; quotient_i >= 0; --quotient_i) {

		intermediate_type temp =
			(static_cast<intermediate_type>(dividend[quotient_i + divisor_size]) << traits::bits_per_limb)
			+ static_cast<intermediate_type>(dividend[quotient_i + divisor_size - 1]);

		temp /= divisor_msl;

		if (temp > traits::unsigned_msl_max)
			temp = traits::unsigned_msl_max;

		if (quotient_i < static_cast<ptrdiff_t>(quotient_capacity))
			quotient[quotient_i] = static_cast<limb_type>(temp);

		multiply_subtract_from(dividend, dividend_size, divisor, divisor_size, false, static_cast<limb_type>(temp), quotient_i);

		// NOTE: the following can loop very often unless the divisor is normalised
		while (negative(dividend, dividend_size, true)) {

			if (quotient_i < static_cast<ptrdiff_t>(quotient_capacity))
				--quotient[quotient_i];

			add_to(dividend, dividend_size, divisor, divisor_size, false, quotient_i);
		}
	}

	return quotient_size;
}

} // namespace backend
} // namespace large_numbers
