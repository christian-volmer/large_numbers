/*
                 Copyright Christian Volmer 2024.
    Distributed under the Boost Software License, Version 1.0.
         (See accompanying file LICENSE_1_0.txt or copy at
              https://www.boost.org/LICENSE_1_0.txt)
*/

/*
    Example program that multiplies two 40 digit numbers and prints the result.
*/

#include <iostream>

#include <large_numbers.h>

// Pull the large integer type into the current namespace.
using large_numbers::integer;

int main()
{
	integer a = integer::from_string("9767704668857007764053867861813392352116");
	integer b = integer::from_string("3874631063700586448314871304245989240069");

	std::cout << a.to_string() << " * " << b.to_string() << " = " << (a * b).to_string() << "\n";
	return 0;
}
