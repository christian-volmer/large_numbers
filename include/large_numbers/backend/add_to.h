/*
                 Copyright Christian Volmer 2024.
    Distributed under the Boost Software License, Version 1.0.
         (See accompanying file LICENSE_1_0.txt or copy at
              https://www.boost.org/LICENSE_1_0.txt)
*/

/*
    Large integer addition.
*/

#pragma once

namespace large_numbers {
namespace backend {

template<typename limb_type>
inline void add_to(limb_type *dest, size_t dest_capacity,
	limb_type const *src, size_t src_size, bool src_signed, size_t limb_shift_left = 0) noexcept
{
	using traits = limb_traits<limb_type>;
	using intermediate_type = typename traits::intermediate_type;

	intermediate_type temp = 0;

	size_t i_dest = limb_shift_left;
	for (size_t i_src = 0; i_src < src_size && i_dest < dest_capacity; ++i_src, ++i_dest) {

		temp += static_cast<intermediate_type>(dest[i_dest])
			+ static_cast<intermediate_type>(src[i_src]);

		dest[i_dest] = static_cast<limb_type>(temp);

		temp >>= traits::bits_per_limb;
	}

	intermediate_type src_extension = extension(src, src_size, src_signed);

	for (; i_dest < dest_capacity; ++i_dest) {

		temp += static_cast<intermediate_type>(dest[i_dest])
			+ src_extension;

		dest[i_dest] = static_cast<limb_type>(temp);

		temp >>= traits::bits_per_limb;
	}
}

} // namespace backend
} // namespace large_numbers
