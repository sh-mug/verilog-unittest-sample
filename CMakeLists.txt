cmake_minimum_required(VERSION 3.14)
project(verilog_unittest_sample)

####################
# Verilator
####################

find_package(verilator HINTS $ENV{VERILATOR_ROOT} ${VERILATOR_ROOT})
if (NOT verilator_FOUND)
  message(FATAL_ERROR "Verilator was not found. Either install it, or set the VERILATOR_ROOT environment variable")
endif()

####################
# GoogleTest
####################

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_COLOR_DIAGNOSTICS ON)
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

####################
# Test
####################

enable_testing()
add_executable(test_all
  test/test_alu.cpp
  test/main.cpp
)
target_link_libraries(
  test_all
  PRIVATE
  GTest::gtest_main
)

set_target_properties(test_all PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
  COMPILE_FLAGS "-Wall -g -fsanitize=address"
  LINK_FLAGS "-fsanitize=address"
)

include(GoogleTest)
gtest_discover_tests(test_all)

####################
# Verilate
####################

verilate(test_all
  INCLUDE_DIRS "src"
  SOURCES
  src/alu.sv
  PREFIX Valu
)
