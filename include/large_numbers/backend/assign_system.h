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

template<typename limb_type, typename other_type>
inline std::enable_if_t<std::is_integral_v<other_type> && !std::is_same_v<other_type, bool>, size_t> assign(limb_type *dest, size_t dest_capacity, other_type const &other)
{
	using traits = limb_traits<limb_type>;

	if (other == 0) {

		if (dest)
			clear(dest, dest_capacity);

		return 0;
	}

	if (dest && dest_capacity) {

		bool other_negative;

		if constexpr (std::is_signed_v<other_type>)
			other_negative = other < 0;
		else
			other_negative = false;

		other_type temp = other;
		ptrdiff_t shift = 0;

		while (temp % 2 == 0) {

			temp /= 2;
			++shift;
		}

		if constexpr (std::is_signed_v<other_type>)
		{
			if (other_negative)
				temp = -temp;
		}

		assert(temp > 0);

		// The following distinction avoids the situation where 'traits::bits_per_limb' is
		// larger than the width of temp in the shift-right operation in the 'else' branch
		if constexpr (sizeof(temp) <= sizeof(limb_type)) {

			dest[0] = static_cast<limb_type>(temp);
			for (size_t i = 1; i < dest_capacity; ++i)
				dest[i] = 0;
		}
		else {

			for (size_t i = 0; i < dest_capacity; ++i) {

				dest[i] = static_cast<limb_type>(temp);
				temp >>= traits::bits_per_limb;
			}
		}

		if constexpr (std::is_signed_v<other_type>)
		{
			if (other_negative)
				negate(dest, dest_capacity);
		}

		shift_left(dest, dest_capacity, std::is_signed_v<other_type>, shift);
	}

	size_t required_bit_size = sizeof(other_type) * 8;
	size_t required_capacity = (required_bit_size + traits::bits_per_limb - 1) / traits::bits_per_limb;

	return required_capacity;
}

} // namespace backend
} // namespace large_numbers
