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
inline limb_type extension(limb_type const *src, size_t src_size, bool src_signed) noexcept
{
	using traits = limb_traits<limb_type>;

	if (negative(src, src_size, src_signed))
		return traits::negative_extension_limb;
	else
		return traits::zero_limb;
}

} // namespace backend
} // namespace large_numbers
