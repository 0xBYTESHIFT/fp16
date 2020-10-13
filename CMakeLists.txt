cmake_minimum_required(VERSION 3.0.0)
project(half VERSION 2.1.2)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 17)
include_directories(include)
add_executable(half-test main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)