/*
				 Copyright Christian Volmer 2024.
	Distributed under the Boost Software License, Version 1.0.
		 (See accompanying file LICENSE_1_0.txt or copy at
			  https://www.boost.org/LICENSE_1_0.txt)
*/

/*
	Main include of the integer data type of the large integer library.
*/

#pragma once

#include "backend.h"

#include <cctype>
#include <vector>

namespace large_numbers {


/*
	The `integer` template class stores an integer whose size is only limited by available memory. 
	For the internal representation of its value it uses an array of so called 'limbs' of type
	given by template parameter `limbT`. `limbT` can be `std::uint8_t`, `std::uint16_t` or `std::uint32_t`.
*/
template<typename limbT>
class integer {

public:

	using limb_type = limbT;
	using this_type = integer<limb_type>;
	using traits = backend::limb_traits<limb_type>;

private:

	std::vector<limb_type> m_limbs;

public:

	// Default constructor, initialises the integers to the value zero.
	integer();

	// Copy constructor
	integer(this_type const &) = default;

	// Move constructor
	integer(this_type &&) noexcept = default;

	// Constructs from a C++ system integer type.
	template<typename other_type, std::enable_if_t<std::is_integral_v<other_type> && !std::is_same_v<other_type, bool>, bool> = true>
	integer(other_type other);

	this_type quotient_remainder(this_type divisor, this_type const offset = this_type());

	std::string to_string(int base = 10) const;
	static this_type from_string(std::string const &str, int base = 10);

	// Copy assignment
	this_type &operator=(this_type const &) = default;

	// Move assignment
	this_type &operator=(this_type &&) noexcept = default;

	// Returns if the stored integer is non-zero.
	explicit operator bool() const noexcept { return !backend::zero(limb_data(), limb_capacity()); }

	// Returns the stored integer.
	this_type const &operator+() const noexcept { return *this; }

	// Returns the arithmetic negation of the stored integer.
	this_type operator-() const;

	// Adds the operand to the stored integer.
	this_type &operator+=(this_type const &other);

	// Subtracts the operand from the stored integer.
	this_type &operator-=(this_type const &other);

	// Multiplies the stored integer by the operand.
	this_type &operator*=(this_type const &other);

	// Divides the stored integer by the operand and discards any fractional part (truncates towards zero).
	this_type &operator/=(this_type const &other);

	// Divides the stored integer by the operand and keeps the remainder.
	this_type &operator%=(this_type const &other);

	// Increments the stored integer by one and returns the result.
	this_type &operator++()
	{
		*this += 1;
		return *this;
	}

	// Decrements the stored integer by one and returns the result.
	this_type &operator--()
	{
		*this -= 1;
		return *this;
	}

	// Increments the stored integer by one and returns the original value before incrementation.
	this_type operator++(int)
	{
		this_type old(*this);
		operator++();
		return old;
	}

	// Decrements the stored integer by one and returns the original value before decrementation.
	this_type operator--(int)
	{
		this_type old(*this);
		operator--();
		return old;
	}

	// Returns the sum of the two operands
	friend this_type operator+(this_type lhs, this_type const &rhs)
	{
		lhs += rhs;
		return lhs;
	}

	// Returns the difference of the first operand minus the second.
	friend this_type operator-(this_type lhs, this_type const &rhs)
	{
		lhs -= rhs;
		return lhs;
	}

	// Returns the product of the two operands.
	friend this_type operator*(this_type lhs, this_type const &rhs)
	{
		lhs *= rhs;
		return lhs;
	}

	friend this_type operator/(this_type lhs, this_type const &rhs)
	{
		lhs /= rhs;
		return lhs;
	}

	friend this_type operator%(this_type lhs, this_type const &rhs)
	{
		lhs %= rhs;
		return lhs;
	}

	// Tests if the two operands are numerically equal
	friend bool operator==(this_type const &lhs, this_type const &rhs) { return backend::compare(lhs.limb_data(), lhs.limb_size(), true, 0, rhs.limb_data(), rhs.limb_size(), true, 0) == 0; }

	// Tests if the two operands are numerically unequal
	friend bool operator!=(this_type const &lhs, this_type const &rhs) { return backend::compare(lhs.limb_data(), lhs.limb_size(), true, 0, rhs.limb_data(), rhs.limb_size(), true, 0) != 0; }

	// Tests if the first operand is numerically smaller than the second operand.
	friend bool operator<(this_type const &lhs, this_type const &rhs) { return backend::compare(lhs.limb_data(), lhs.limb_size(), true, 0, rhs.limb_data(), rhs.limb_size(), true, 0) < 0; }

	// Tests if the first operand is numerically greater than the second operand.
	friend bool operator>(this_type const &lhs, this_type const &rhs) { return backend::compare(lhs.limb_data(), lhs.limb_size(), true, 0, rhs.limb_data(), rhs.limb_size(), true, 0) > 0; }

	// Tests if the first operand is numerically smaller than or equal to the second operand.
	friend bool operator<=(this_type const &lhs, this_type const &rhs) { return backend::compare(lhs.limb_data(), lhs.limb_size(), true, 0, rhs.limb_data(), rhs.limb_size(), true, 0) <= 0; }

	// Tests if the first operand is numerically greater than or equal to the second operand.
	friend bool operator>=(this_type const &lhs, this_type const &rhs) { return backend::compare(lhs.limb_data(), lhs.limb_size(), true, 0, rhs.limb_data(), rhs.limb_size(), true, 0) >= 0; }

	//
	// Auxiliary functions
	//

	limb_type const *limb_data() const noexcept { return m_limbs.data(); }
	limb_type *limb_data() noexcept { return m_limbs.data(); }

	size_t limb_capacity() const noexcept { return m_limbs.size(); }
	size_t limb_size() const noexcept { return backend::limb_size(limb_data(), limb_capacity(), true); }
	limb_type limb_extension() const noexcept { return backend::extension(limb_data(), limb_capacity(), true); }
	void limb_resize(size_t new_limb_size) { m_limbs.resize(new_limb_size, limb_extension()); }

	// Low-level function that returns the limb at the given index. Indices beyond the actual capacity return
	// the correct sign extention, negative indices return zero.
	limb_type limb_at_extend(ptrdiff_t i) const noexcept;

	// Tests if the stored integer is zero.
	bool zero() const noexcept { return backend::zero(limb_data(), limb_capacity()); }

	// Tests if the stored integer is negative.
	bool negative() const noexcept { return backend::negative(limb_data(), limb_capacity(), true); }

	// Negates the stored integer.
	void negate()
	{
		limb_resize(limb_size() + 1);
		backend::negate(limb_data(), limb_capacity());
	}
};

// Alias for a large integer type that uses 8 bit integers for its internal representation.
using integer_8 = integer<std::uint8_t>;

// Alias for a large integer type that uses 16 bit integers for its internal representation.
using integer_16 = integer<std::uint16_t>;

// Alias for a large integer type that uses 32 bit integers for its internal representation.
using integer_32 = integer<std::uint32_t>;

} // namespace large_numbers

#include "integer/construction.h"
#include "integer/from_string.h"
#include "integer/limb_at.h"
#include "integer/operators.h"
#include "integer/quotient_remainder.h"
#include "integer/to_string.h"
