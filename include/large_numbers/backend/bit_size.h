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

template<typename limb_type>
inline size_t bit_size(limb_type const *src, size_t src_size, bool src_signed) noexcept
{
	using traits = limb_traits<limb_type>;

	size_t const size = limb_size(src, src_size, src_signed);
	size_t bit_size = size * traits::bits_per_limb;

	if (size > 0) {

		typename traits::limb_type msl = src[size - 1];

		if (src_signed) {

			// Invert all bits of a negative number so we can use the same logic later on
			if (msl >= traits::signed_msl_min)
				msl = ~msl;

			// We shift out the sign bit and set the lowest significant bit as
			// a stopping condition for the while-loop later on.
			msl <<= 1;
			msl |= 1;
		}

		assert(msl != 0);

		// While the most significant bit is zero be can decrease the bit size by one.
		while (msl <= traits::signed_msl_max) {

			msl <<= 1;
			--bit_size;
		}
	}

	return bit_size;
}

} // namespace backend
} // namespace large_numbers
