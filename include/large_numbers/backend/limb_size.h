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
inline size_t limb_size(limb_type const *src, size_t src_size, bool src_signed) noexcept
{
	using traits = limb_traits<limb_type>;

	size_t size = src_size;

	if (!src_signed) {

		while (size > 0 && src[size - 1] == 0)
			--size;
	}
	else if (negative(src, src_size, src_signed)) {

		while (size > 1 && src[size - 1] == traits::negative_extension_limb && src[size - 2] >= traits::signed_msl_min)
			--size;
	}
	else {

		while (size > 1 && src[size - 1] == 0 && src[size - 2] <= traits::signed_msl_max)
			--size;

		if (size == 1 && src[0] == 0)
			--size;
	}

	return size;
}

} // namespace backend
} // namespace large_numbers
