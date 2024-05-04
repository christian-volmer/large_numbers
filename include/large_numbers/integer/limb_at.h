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

template<typename limbT>
limbT integer<limbT>::limb_at_extend(ptrdiff_t i) const noexcept
{
	if (i < 0)
		return 0;
	else if (static_cast<size_t>(i) >= limb_capacity())
		return limb_extension();
	else
		return limb_data()[i];
}

} // namespace large_numbers
