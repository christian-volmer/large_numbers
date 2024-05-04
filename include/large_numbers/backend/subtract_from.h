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
inline void subtract_from(limb_type *dest, size_t dest_capacity,
	limb_type const *src, size_t src_size, bool src_signed, size_t limb_shift_left = 0) noexcept
{
	negate(dest, dest_capacity);
	add_to(dest, dest_capacity, src, src_size, src_signed, limb_shift_left);
	negate(dest, dest_capacity);
}

} // namespace backend
} // namespace large_numbers
