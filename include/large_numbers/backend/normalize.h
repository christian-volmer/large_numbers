/*
                 Copyright Christian Volmer 2024.
    Distributed under the Boost Software License, Version 1.0.
         (See accompanying file LICENSE_1_0.txt or copy at
              https://www.boost.org/LICENSE_1_0.txt)
*/

/*
    Large integer normalisation. Ensures that the most significant bit is 1.
*/

#pragma once

namespace large_numbers {
namespace backend {

template<typename limb_type>
inline ptrdiff_t normalize(limb_type *dest, size_t &dest_size) noexcept
{
	using traits = limb_traits<limb_type>;

	// normalization requires (and therefore assumes) 'dest' to be unsigned
	dest_size = limb_size(dest, dest_size, false);

	if (dest_size == 0)
		return 0;

	ptrdiff_t normalization_shift = 0;
	limb_type msl = dest[dest_size - 1];
	while (msl < traits::unsigned_msl_normalized) {

		msl <<= 1;
		++normalization_shift;
	}

	assert(normalization_shift >= 0 && static_cast<size_t>(normalization_shift) < traits::bits_per_limb);

	shift_left(dest, dest_size, false, normalization_shift);

	return normalization_shift;
}

} // namespace backend
} // namespace large_numbers
