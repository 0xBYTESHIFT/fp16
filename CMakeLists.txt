cmake_minimum_required(VERSION 3.0.0)
project(half VERSION 2.1.1)

include(CTest)
enable_testing()

include_directories(include)
add_executable(half-test main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)