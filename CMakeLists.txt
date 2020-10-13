############################################################################
# Copyright (c) Christian Rau, 0xBYTESHIFT                                 #
#                                                                          #
# Distributed under the terms of the MIT License.                          #
#                                                                          #
# The full license is in the file LICENSE, distributed with this software. #
############################################################################

cmake_minimum_required(VERSION 3.0.0)
project(half VERSION 2.2.0)

include(CTest)
enable_testing()
message(STATUS "${PROJECT_NAME} v${PROJECT_VERSION}")

set(HALF_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(HALF_HEADERS ${HALF_INCLUDE_DIR}/half/half.hpp)
option(HALF_TESTS "build tests for half float lib" OFF)

# Build
# =====

add_library(half INTERFACE)

target_include_directories(half INTERFACE
    $<BUILD_INTERFACE:${HALF_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:include>)

if(NOT (CMAKE_VERSION VERSION_LESS 3.15))  # CMake >= 3.15
    set_target_properties(half PROPERTIES PUBLIC_HEADER "${HALF_HEADERS}")
endif()

if(HALF_TESTS)
    add_subdirectory(tests)
endif()

# Installation
# ============

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

if(CMAKE_VERSION VERSION_LESS 3.15)  # CMake < 3.15
    install(TARGETS half
            EXPORT ${PROJECT_NAME}-targets)
else()
    install(TARGETS half
            EXPORT ${PROJECT_NAME}-targets
            PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})
endif()

# Makes the project importable from the build directory
export(EXPORT ${PROJECT_NAME}-targets
       FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Targets.cmake")

if(CMAKE_VERSION VERSION_LESS 3.15)  # CMake < 3.15
    install(FILES ${HALF_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/half)
endif()

set(HALF_CMAKECONFIG_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}" CACHE
    STRING "install path for halfConfig.cmake")

configure_package_config_file(${PROJECT_NAME}Config.cmake.in
                              "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
                              INSTALL_DESTINATION ${HALF_CMAKECONFIG_INSTALL_DIR})

# half is header-only and does not depend on the architecture.
# Remove CMAKE_SIZEOF_VOID_P from halfConfigVersion.cmake so that an halfConfig.cmake
# generated for a 64 bit target can be used for 32 bit targets and vice versa.
set(_HALF_CMAKE_SIZEOF_VOID_P ${CMAKE_SIZEOF_VOID_P})
unset(CMAKE_SIZEOF_VOID_P)
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
                                 VERSION ${${PROJECT_NAME}_VERSION}
                                 COMPATIBILITY AnyNewerVersion)
set(CMAKE_SIZEOF_VOID_P ${_HALF_CMAKE_SIZEOF_VOID_P})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
        DESTINATION ${HALF_CMAKECONFIG_INSTALL_DIR})
install(EXPORT ${PROJECT_NAME}-targets
        FILE ${PROJECT_NAME}Targets.cmake
        DESTINATION ${HALF_CMAKECONFIG_INSTALL_DIR})

configure_file(${PROJECT_NAME}.pc.in
               "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc"
                @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig/")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)