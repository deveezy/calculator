cmake_minimum_required(VERSION 3.0.0)

set(proj calc)
project(${proj} CXX)

set(CMAKE_CXX_STANDARD 17)
file(GLOB TARGET_SRC
	"./src/*.cpp", "./src/*.hpp")
add_executable(${proj} ${TARGET_SRC})
target_include_directories(${proj} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_compile_options(${proj} PRIVATE -Wall -Wextra -pedantic )
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_GNU_SOURCE")

# GTest
enable_testing()
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

set (test_proj calc_test)
add_executable(${test_proj} "src/calculator.hpp" "src/calculator.cpp" "test/test_calc.cpp")
add_test(tc ${test_proj})

target_include_directories(${test_proj} PRIVATE ${GTEST_INCLUDE_DIRS})
target_link_libraries(${test_proj} PRIVATE ${GTEST_BOTH_LIBRARIES})
target_include_directories(${test_proj} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")

target_compile_options(${test_proj} PRIVATE -Wall -Wextra -pedantic )
