cmake_minimum_required(VERSION 3.22.1)
project(matrices LANGUAGES CXX)

# interesting fact - if you would set cxx standard below some other props,
# it`s a great possibility that you wouldn`t have some latest std features
# (like i coldn`t use std::ranges, but there was present header of it)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/*.inl
)

# Collect all source files
file(GLOB_RECURSE COMPILATION_UNITS_TMP CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c++
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.inl
)

# Filter out the test files
set(COMPILATION_UNITS "")
foreach(file ${COMPILATION_UNITS_TMP})
    if (NOT file MATCHES "(test|main)\\.(cpp|c\\+\\+|cc)$")
        list(APPEND COMPILATION_UNITS ${file})
    endif()
endforeach()

# Create the library
add_library(matrices STATIC ${COMPILATION_UNITS} ${HEADERS})

# Expose our matrices for include
target_include_directories(matrices PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Set C++ standard
target_compile_features(matrices PUBLIC cxx_std_20)

# set linker prop so
set_target_properties(matrices PROPERTIES LINKER_LANGUAGE CXX)

# Add tests only if BUILD_TESTING is enabled
# Testing configuration
option(MATRICES_ENABLE_TESTS "Enable unit tests for the matrices library" ON)

#include(CTest) # Enables the BUILD_TESTING option

#if(#[[BUILD_TESTING AND]] MATRICES_ENABLE_TESTS==ON)
    enable_testing()

    # Collect all the test files
    file(GLOB_RECURSE TESTS CONFIGURE_DEPENDS
            ${CMAKE_CURRENT_SOURCE_DIR}/src/*test.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/*test.c++
            ${CMAKE_CURRENT_SOURCE_DIR}/src/*test.cс
    )

    set(GTESTLIBS GTest::gtest_main GTest::GTest GTest::Main)
    find_package(GTest REQUIRED)

    add_executable(tests-all-matrix ${TESTS} )
    target_link_libraries(tests-all-matrix matrices ${GTESTLIBS})

    include(GoogleTest)
    gtest_discover_tests(tests-all-matrix)
#endif()
