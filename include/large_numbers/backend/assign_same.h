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
inline void assign(limb_type *dest, size_t dest_capacity,
	limb_type const *src, size_t src_size, bool src_signed) noexcept
{
	size_t i;

	for (i = 0; i < dest_capacity && i < src_size; ++i)
		dest[i] = src[i];

	limb_type src_extension = extension(src, src_size, src_signed);

	for (; i < dest_capacity; ++i)
		dest[i] = src_extension;
}

} // namespace backend
} // namespace large_numbers
