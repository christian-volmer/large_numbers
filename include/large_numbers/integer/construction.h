/*
                 Copyright Christian Volmer 2024.
    Distributed under the Boost Software License, Version 1.0.
         (See accompanying file LICENSE_1_0.txt or copy at
              https://www.boost.org/LICENSE_1_0.txt)
*/

/*
    basic_integer<> constructor implementations.
*/

#pragma once

namespace large_numbers {

template<typename limbT>
inline basic_integer<limbT>::basic_integer() :
	m_limbs()
{
}

template<typename limbT>
template<typename other_type, std::enable_if_t<std::is_integral_v<other_type> && !std::is_same_v<other_type, bool>, bool>>
inline basic_integer<limbT>::basic_integer(other_type other) :
	m_limbs()
{
	size_t required_size = backend::assign<limb_type>(nullptr, 0, other) + std::is_unsigned_v<other_type>;

	limb_resize(required_size);
	backend::assign(limb_data(), limb_capacity(), other);
}

} // namespace large_numbers
