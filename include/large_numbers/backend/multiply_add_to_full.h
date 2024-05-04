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
	limb_type const *a, size_t a_size, bool a_signed,
	limb_type const *b, size_t b_size, bool b_signed,
	size_t limb_shift_left = 0) noexcept
{
	for (size_t a_i = 0; a_i < a_size; ++a_i)
		multiply_add_to(dest, dest_capacity, b, b_size, b_signed, a[a_i], a_i + limb_shift_left);

	if (negative(a, a_size, a_signed))
		subtract_from(dest, dest_capacity, b, b_size, b_signed, a_size + limb_shift_left);
}

} // namespace backend
} // namespace large_numbers
