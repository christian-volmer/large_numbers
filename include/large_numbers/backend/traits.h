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

//
// struct intermediate_type
//

template<typename limbT>
struct intermediate_type;

template<>
struct intermediate_type<std::uint8_t> {
	using type = std::uint16_t;
};

template<>
struct intermediate_type<std::uint16_t> {
	using type = std::uint32_t;
};

template<>
struct intermediate_type<std::uint32_t> {
	using type = std::uint64_t;
};

//
// struct limb_traits
//

template<typename limbT>
struct limb_traits {

	using limb_type = limbT;
	using intermediate_type = typename intermediate_type<limb_type>::type;

	static constexpr size_t bits_per_limb = sizeof(limb_type) * 8;

	static constexpr limb_type zero_limb = limb_type(0);
	static constexpr limb_type negative_extension_limb = limb_type(-1);

	static constexpr limb_type signed_msl_min = limb_type(1) << (bits_per_limb - 1);
	static constexpr limb_type signed_msl_max = signed_msl_min - 1;

	static constexpr limb_type unsigned_msl_max = limb_type(-1);
	static constexpr limb_type unsigned_msl_normalized = signed_msl_min;
};

} // namespace backend
} // namespace large_numbers
