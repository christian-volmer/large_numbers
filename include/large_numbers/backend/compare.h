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
inline int compare(
	limb_type const *lhs, size_t lhs_size, bool lhs_signed, size_t lhs_limb_shift_left,
	limb_type const *rhs, size_t rhs_size, bool rhs_signed, size_t rhs_limb_shift_left) noexcept
{
	bool lhs_negative = negative(lhs, lhs_size, lhs_signed);
	bool rhs_negative = negative(rhs, rhs_size, rhs_signed);

	if (lhs_negative && !rhs_negative)
		return -1;
	else if (!lhs_negative && rhs_negative)
		return 1;


	// If both operands are shifted we can shift both of them back so that
	// only the shift of one operand remains.

	size_t shift_correction = std::min(lhs_limb_shift_left, rhs_limb_shift_left);
	lhs_limb_shift_left -= shift_correction;
	rhs_limb_shift_left -= shift_correction;

	// We want the RHS to be at least as long as the LHS (including their
	// respective shifts).

	bool swapped = rhs_size + rhs_limb_shift_left < lhs_size + lhs_limb_shift_left;

	if (swapped) {

		std::swap(lhs, rhs);
		std::swap(lhs_size, rhs_size);
		std::swap(lhs_signed, rhs_signed);
		std::swap(lhs_limb_shift_left, rhs_limb_shift_left);
	}

	assert(rhs_size + rhs_limb_shift_left >= lhs_size + lhs_limb_shift_left);

	limb_type lhs_extension = extension(lhs, lhs_size, lhs_signed);

	// Signed sizes for later use
	ptrdiff_t rhs_total_ssize = rhs_size + rhs_limb_shift_left;
	ptrdiff_t lhs_total_ssize = lhs_size + lhs_limb_shift_left;
	ptrdiff_t rhs_sshift = rhs_limb_shift_left;
	ptrdiff_t lhs_sshift = lhs_limb_shift_left;

	ptrdiff_t i = rhs_total_ssize - 1;

	// Compare the range of indices where LHS must be extended

	for (; i >= rhs_sshift && i >= lhs_total_ssize; --i) {

		if (lhs_extension < rhs[i - rhs_sshift])
			return swapped ? 1 : -1;
		else if (lhs_extension > rhs[i - rhs_sshift])
			return swapped ? -1 : 1;
	}

	// There could be a range of indices where there is no overlap
	// between the two operands. This happens if the shift of
	// the RHS is longer than the LHS.

	for (; i >= lhs_total_ssize; --i) {

		/*if (lhs_extension < 0)
			return swapped ? 1 : -1;
		else*/ if (lhs_extension > 0)
			return swapped ? -1 : 1;
	}

	// Compare the range of indices where both operands overlap
	// without extension or padding

	for (; i >= rhs_sshift && i >= lhs_sshift; --i) {

		if (lhs[i - lhs_sshift] < rhs[i - rhs_sshift])
			return swapped ? 1 : -1;
		else if (lhs[i - lhs_sshift] > rhs[i - rhs_sshift])
			return swapped ? -1 : 1;
	}


	if (i >= 0) {

		// Compare the remaining indices where one operand needs padding

		if (lhs_sshift > 0) {

			assert(i + 1 == lhs_sshift);
			assert(rhs_sshift == 0);

			for (; i >= 0; --i) {

				if (0 < rhs[i])
					return swapped ? 1 : -1;
			}
		}
		else {

			assert(i + 1 == rhs_sshift);
			assert(lhs_sshift == 0);

			for (; i >= 0; --i) {

				if (lhs[i] > 0)
					return swapped ? -1 : 1;
			}
		}
	}

	assert(i == -1);

	return 0;
}

} // namespace backend
} // namespace large_numbers
