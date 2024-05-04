/*
                 Copyright Christian Volmer 2024.
    Distributed under the Boost Software License, Version 1.0.
         (See accompanying file LICENSE_1_0.txt or copy at
              https://www.boost.org/LICENSE_1_0.txt)
*/

/*
    Main include for the large number backend functions
*/

#pragma once

#include <cassert>
#include <algorithm>
#include <cstdint>
#include <type_traits>
#include <stdexcept>
#include <string>

#include "backend/traits.h"
#include "backend/negative.h"
#include "backend/zero.h"
#include "backend/clear.h"
#include "backend/extension.h"
#include "backend/limb_size.h"
#include "backend/bit_size.h"
#include "backend/negate.h"
#include "backend/shift.h"
#include "backend/assign_same.h"
#include "backend/assign_system.h"
#include "backend/add_to.h"
#include "backend/multiply_add_to.h"
#include "backend/subtract_from.h"
#include "backend/multiply_add_to_full.h"
#include "backend/multiply_subtract_from.h"
#include "backend/compare.h"
#include "backend/normalize.h"
#include "backend/quotient_remainder.h"
