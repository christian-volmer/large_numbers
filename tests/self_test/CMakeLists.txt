add_executable(self_test
	main.cpp
)

target_link_libraries(self_test PRIVATE large_numbers)

add_test(NAME self-test COMMAND self_test)

