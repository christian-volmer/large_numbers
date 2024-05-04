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
inline void shift_right(limb_type *dest, size_t dest_capacity, bool dest_signed, ptrdiff_t bit_shift) noexcept;

template<typename limb_type>
inline void shift_left(limb_type *dest, size_t dest_capacity, bool dest_signed, ptrdiff_t bit_shift) noexcept
{
	using traits = limb_traits<limb_type>;
	using intermediate_type = typename traits::intermediate_type;

	if (bit_shift == 0 || dest_capacity == 0)
		return;

	if (bit_shift < 0) {

		shift_right(dest, dest_capacity, dest_signed, -bit_shift);
		return;
	}

	assert(bit_shift > 0);

	ptrdiff_t coarse = bit_shift / traits::bits_per_limb;
	ptrdiff_t fine = bit_shift % traits::bits_per_limb;

	ptrdiff_t i = static_cast<ptrdiff_t>(dest_capacity) - 1;

	for (; i > coarse; --i) {

		intermediate_type temp =
			(static_cast<intermediate_type>(dest[i - coarse]) << traits::bits_per_limb)
			+ static_cast<intermediate_type>(dest[i - coarse - 1]);

		temp >>= traits::bits_per_limb - fine;

		dest[i] = static_cast<limb_type>(temp);
	}

	if (i >= coarse) {

		dest[i] = dest[i - coarse] << fine;
		--i;
	}

	for (; i >= 0; --i)
		dest[i] = traits::zero_limb;
}

template<typename limb_type>
inline void shift_right(limb_type *dest, size_t dest_capacity, bool dest_signed, ptrdiff_t bit_shift) noexcept
{
	using traits = limb_traits<limb_type>;
	using intermediate_type = typename traits::intermediate_type;

	if (bit_shift == 0 || dest_capacity == 0)
		return;

	if (bit_shift < 0) {

		shift_left(dest, dest_capacity, dest_signed, -bit_shift);
		return;
	}

	assert(bit_shift > 0);

	size_t coarse = bit_shift / traits::bits_per_limb;
	size_t fine = bit_shift % traits::bits_per_limb;

	size_t i = 0;

	for (; i + coarse + 1 < dest_capacity; ++i) {

		intermediate_type temp =
			(static_cast<intermediate_type>(dest[i + coarse + 1]) << traits::bits_per_limb)
			+ static_cast<intermediate_type>(dest[i + coarse]);

		temp >>= fine;

		dest[i] = static_cast<limb_type>(temp);
	}

	limb_type dest_extension = extension(dest, dest_capacity, dest_signed);

	if (i + coarse < dest_capacity) {

		intermediate_type temp =
			(static_cast<intermediate_type>(dest_extension) << traits::bits_per_limb)
			+ static_cast<intermediate_type>(dest[i + coarse]);

		temp >>= fine;

		dest[i] = static_cast<limb_type>(temp);
		++i;
	}

	for (; i < dest_capacity; ++i)
		dest[i] = dest_extension;
}

} // namespace backend
} // namespace large_numbers
