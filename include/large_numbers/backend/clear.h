/*
                 Copyright Christian Volmer 2024.
    Distributed under the Boost Software License, Version 1.0.
         (See accompanying file LICENSE_1_0.txt or copy at
              https://www.boost.org/LICENSE_1_0.txt)
*/

/*
    Function to set a large integer to the value zero.
*/

#pragma once

namespace large_numbers {
namespace backend {

template<typename limb_type>
inline void clear(limb_type *dest, size_t dest_capacity) noexcept
{
	for (size_t dest_i = 0; dest_i < dest_capacity; ++dest_i)
		dest[dest_i] = 0;
}

} // namespace backend
} // namespace large_numbers
