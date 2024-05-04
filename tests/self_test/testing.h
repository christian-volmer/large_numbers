/*
	             Copyright Christian Volmer 2024.
	Distributed under the Boost Software License, Version 1.0.
	     (See accompanying file LICENSE_1_0.txt or copy at
	          https://www.boost.org/LICENSE_1_0.txt)
*/

/*
	Collection of functions to support the generation of random integers.
*/

#pragma once

static inline std::mt19937 g_RandomEngine;

// Returns a random size_t that can be used as the capacity of a
// randomly generated large integer.
inline size_t random_capacity() noexcept
{
	size_t size = std::uniform_int_distribution<size_t>(0, 4)(g_RandomEngine);

	if (size == 0)
		return std::uniform_int_distribution<size_t>(0, 100)(g_RandomEngine);
	else
		return size;
}

// Returns a randomly generated large integer of given type.
template<typename integerT>
inline integerT random_integer(size_t dest_capacity) noexcept
{
	integerT result;

	result.limb_resize(dest_capacity);

	for (size_t i = 0; i < dest_capacity; ++i)
		result.limb_data()[i] = static_cast<typename integerT::limb_type>(std::uniform_int_distribution<std::uintmax_t>()(g_RandomEngine));

	return result;
}
