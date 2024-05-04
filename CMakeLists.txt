cmake_minimum_required(VERSION 3.21)

project(large_numbers CXX)

add_library(large_numbers INTERFACE)
target_include_directories(large_numbers INTERFACE include)
add_subdirectory(src)


if(PROJECT_IS_TOP_LEVEL)

	if(MSVC)
		add_compile_options(/W4 /std:c++17)
	else()
		add_compile_options(-Wall -Wextra -Wpedantic -std=c++17)
	endif()

else()

	target_compile_features(large_numbers INTERFACE cxx_std_17)

endif()


if(PROJECT_IS_TOP_LEVEL)

	enable_testing()

	add_subdirectory(examples)
	add_subdirectory(tests)

endif()
