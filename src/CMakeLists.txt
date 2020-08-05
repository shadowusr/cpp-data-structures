project(array)
add_library(array array.cpp ${CMAKE_SOURCE_DIR}/include/array.h)
target_include_directories(array PUBLIC ${CMAKE_SOURCE_DIR}/include)