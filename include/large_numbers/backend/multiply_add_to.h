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
inline void multiply_add_to(limb_type *dest, size_t dest_capacity,
	limb_type const *a, size_t a_size, bool a_signed, limb_type b, size_t limb_shift_left = 0) noexcept
{
	using traits = limb_traits<limb_type>;
	using intermediate_type = typename traits::intermediate_type;

	intermediate_type temp = 0;
	intermediate_type intermediate_typed_b = b;

	size_t i_dest = limb_shift_left;
	for (size_t i_a = 0; i_a < a_size && i_dest < dest_capacity; ++i_a, ++i_dest) {

		temp += static_cast<intermediate_type>(dest[i_dest])
			+ intermediate_typed_b * static_cast<intermediate_type>(a[i_a]);

		dest[i_dest] = static_cast<limb_type>(temp);

		temp >>= traits::bits_per_limb;
	}

	intermediate_type product_extension = intermediate_typed_b * static_cast<intermediate_type>(extension(a, a_size, a_signed));

	for (; i_dest < dest_capacity; ++i_dest) {

		temp += static_cast<intermediate_type>(dest[i_dest])
			+ product_extension;

		dest[i_dest] = static_cast<limb_type>(temp);

		temp >>= traits::bits_per_limb;
	}
}

} // namespace backend
} // namespace large_numbers
