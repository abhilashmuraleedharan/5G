cmake_minimum_required(VERSION 3.14)

project(5GUtilities VERSION 1.0 DESCRIPTION "5G Utilities Collection")

# Use the C++11 standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories for shared headers
include_directories(shared/include)

# If you want to set a specific C++ compiler, uncomment the lines below
# set(CMAKE_C_COMPILER "/usr/bin/clang")
# set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

# On macOS, use the libc++ library with Clang
if(APPLE)
  include_directories(/usr/include)
  include_directories(/usr/local/include)
  link_directories(/usr/local/lib)
  link_directories(/usr/lib)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif()

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Enable testing with Google Test
enable_testing()

# Add an executable for the utilities and link the required libraries
add_executable(WavelengthCalculator utilities/WavelengthCalculator/src/main.cpp shared/src/utilities.cpp)
add_executable(ShannonsCapacityCalculator utilities/ShannonsCapacityCalculator/src/main.cpp shared/src/utilities.cpp)

# Add an executable for the unit tests
add_executable(utilities_test tests/utilities_test.cpp shared/src/utilities.cpp)
target_link_libraries(utilities_test ${GTEST_LIBRARIES})

# For macOS, link against the proper C++ libraries and pthread
if(APPLE)
  target_link_libraries(utilities_test "-framework CoreFoundation" "-framework IOKit" pthread)
endif()

# Add Google Test based tests
include(GoogleTest)
gtest_discover_tests(utilities_test)