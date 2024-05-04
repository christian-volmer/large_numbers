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
inline void multiply_subtract_from(limb_type *dest, size_t dest_capacity,
	limb_type const *a, size_t a_size, bool a_signed, limb_type b, size_t limb_shift_left = 0) noexcept
{
	negate(dest, dest_capacity);
	multiply_add_to(dest, dest_capacity, a, a_size, a_signed, b, limb_shift_left);
	negate(dest, dest_capacity);
}

} // namespace backend
} // namespace large_numbers
