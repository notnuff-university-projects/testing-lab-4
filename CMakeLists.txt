cmake_minimum_required(VERSION 3.22.1)
project(lab4)

# interesting fact - if you would set cxx standard below some other props,
# it`s a great possibility that you wouldn`t have some latest std features
# (like i coldn`t use std::ranges, but there was present header of it)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(common/matrices)

file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.inl
)

# Collect all source files
file(GLOB_RECURSE COMPILATION_UNITS_TMP CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c++
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc
)

# Filter out the test files
set(COMPILATION_UNITS "")
foreach(file ${COMPILATION_UNITS_TMP})
    if (NOT file MATCHES "(test|main)\\.(cpp|c\\+\\+|cc)$")
        list(APPEND COMPILATION_UNITS ${file})
    endif()
endforeach()

file(GLOB_RECURSE TESTS CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*test.c++
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*test.cс
)

add_executable(lab4 src/main.cpp ${COMPILATION_UNITS} ${HEADERS})
target_link_libraries(lab4 PRIVATE matrices)
target_include_directories(lab4 PRIVATE common)

set(GTESTLIBS GTest::gtest_main GTest::GTest GTest::Main)
find_package(GTest REQUIRED)

enable_testing()

add_executable(tests-all ${TESTS} ${HEADERS} ${COMPILATION_UNITS})
target_link_libraries(tests-all matrices)
target_link_libraries(tests-all ${GTESTLIBS})
target_include_directories(tests-all PRIVATE common src/tests_common)

include(GoogleTest)
gtest_discover_tests(tests-all)

# Add post-build command to copy the file
add_custom_command(
        TARGET lab4
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/rsc"
        "$<TARGET_FILE_DIR:lab4>/rsc"
)

# Add post-build command to copy the file
add_custom_command(
        TARGET tests-all
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/rsc"
        "$<TARGET_FILE_DIR:lab4>/rsc"
)



