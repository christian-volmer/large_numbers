/*
                 Copyright Christian Volmer 2024.
    Distributed under the Boost Software License, Version 1.0.
         (See accompanying file LICENSE_1_0.txt or copy at
              https://www.boost.org/LICENSE_1_0.txt)
*/

/*
    Large integer arithmetic negation.
*/

#pragma once

namespace large_numbers {
namespace backend {

template<typename limb_type>
inline void negate(limb_type *dest, size_t dest_capacity) noexcept
{
	size_t i = 0;

	while (i < dest_capacity && dest[i] == 0)
		++i;

	if (i < dest_capacity) {

		dest[i] = ~dest[i] + 1;
		++i;

		for (; i < dest_capacity; ++i)
			dest[i] = ~dest[i];
	}
}

} // namespace backend
} // namespace large_numbers
