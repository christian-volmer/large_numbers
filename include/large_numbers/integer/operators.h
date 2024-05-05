/*
                 Copyright Christian Volmer 2024.
    Distributed under the Boost Software License, Version 1.0.
         (See accompanying file LICENSE_1_0.txt or copy at
              https://www.boost.org/LICENSE_1_0.txt)
*/

/*
    basic_integer<> operator implementations.
*/

#pragma once

namespace large_numbers {

template<typename limbT>
inline basic_integer<limbT> basic_integer<limbT>::operator-() const
{
	this_type result(*this);

	result.negate();

	return result;
}

template<typename limbT>
inline basic_integer<limbT> &basic_integer<limbT>::operator+=(this_type const &other)
{
	size_t other_limb_size = other.limb_size();

	limb_resize(std::max(limb_size(), other_limb_size) + 1);

	backend::add_to(limb_data(), limb_capacity(), other.limb_data(), other_limb_size, true, 0);

	return *this;
}

template<typename limbT>
inline basic_integer<limbT> &basic_integer<limbT>::operator-=(this_type const &other)
{
	size_t other_limb_size = other.limb_size();

	limb_resize(std::max(limb_size(), other_limb_size + 1) + 1);

	backend::subtract_from(limb_data(), limb_capacity(), other.limb_data(), other_limb_size, true, 0);

	return *this;
}

template<typename limbT>
inline basic_integer<limbT> &basic_integer<limbT>::operator*=(this_type const &other)
{
	this_type const lhs = *this;
	this_type const &rhs = other;

	size_t lhs_limb_size = lhs.limb_size();
	size_t rhs_limb_size = rhs.limb_size();

	backend::clear(limb_data(), limb_capacity());
	limb_resize(lhs_limb_size + rhs_limb_size);

	backend::multiply_add_to(limb_data(), limb_capacity(), lhs.limb_data(), lhs_limb_size, true, rhs.limb_data(), rhs_limb_size, true, 0);

	return *this;
}

template<typename limbT>
inline basic_integer<limbT> &basic_integer<limbT>::operator/=(this_type divisor)
{
	bool dividend_negative = this->negative();
	bool divisor_negative = divisor.negative();

	if (dividend_negative)
		negate();

	if (divisor_negative)
		divisor.negate();

	*this = quotient_remainder(divisor);

	if (dividend_negative != divisor_negative)
		negate();

	return *this;
}

template<typename limbT>
inline basic_integer<limbT> &basic_integer<limbT>::operator%=(this_type divisor)
{
	bool dividend_negative = this->negative();
	bool divisor_negative = divisor.negative();

	if (dividend_negative)
		negate();

	if (divisor_negative)
		divisor.negate();

	quotient_remainder(divisor);

	if (dividend_negative)
		negate();

	return *this;
}

} // namespace large_numbers
