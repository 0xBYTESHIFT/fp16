cmake_minimum_required(VERSION 3.0.0)

if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    project(half-test)

    enable_testing()
    find_package(half REQUIRED CONFIG)
endif()

set(HALF_TESTS
    main.cpp
)

add_executable(test_half ${HALF_TESTS} ${HALF_HEADERS})
target_include_directories(test_half PRIVATE ${HALF_INCLUDE_DIR})
target_link_libraries(test_half half)
add_test(test_half test_half)