project(test)

add_executable(tests main.cpp arraytest.cpp)
target_link_libraries(tests PRIVATE gtest gmock array)
add_test(NAME ctests COMMAND tests)