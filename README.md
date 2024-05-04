
# Working with large numbers

The ‘large_numbers’ library provides functions and classes for doing arithmetic with integers whose size is only limited by the available computer memory. 

Using the library is as easy as
```c++
integer a = integer::from_string("9767704668857007764053867861813392352116");
integer b = integer::from_string("3874631063700586448314871304245989240069");

std::cout << a.to_string() << " * " << b.to_string() << " = " << (a * b).to_string() << "\n";
```

Check out the `examples/basic` directory for a complete minimum working example.

## License

The ‘large_numbers’ library is released under the very permissive [Boost Software License (BSL)](/LICENSE_1_0.txt). The license basically says that you have to keep the copyright notice in the source code files but not in any binary code you distribute or even sell. Visit the boost website that has a [page explaining their license](https://www.boost.org/users/license.html) to learn more.