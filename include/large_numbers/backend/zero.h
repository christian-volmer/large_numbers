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
inline bool zero(limb_type const *src, size_t src_size) noexcept
{
	for (size_t src_i = 0; src_i < src_size; ++src_i)
		if (src[src_i] != 0)
			return false;

	return true;
}

} // namespace backend
} // namespace large_numbers
