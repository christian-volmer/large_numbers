/*
                 Copyright Christian Volmer 2024.
    Distributed under the Boost Software License, Version 1.0.
         (See accompanying file LICENSE_1_0.txt or copy at
              https://www.boost.org/LICENSE_1_0.txt)
*/

/*
    Determine if a large integer is negative.
*/

#pragma once

namespace large_numbers {
namespace backend {

template<typename limb_type>
inline bool negative(limb_type const *src, size_t src_size, bool src_signed) noexcept
{
	using traits = limb_traits<limb_type>;

	if (!src_signed || (src_size == 0))
		return false;

	if (src[src_size - 1] <= traits::signed_msl_max)
		return false;
	else
		return true;
}

} // namespace backend
} // namespace large_numbers
