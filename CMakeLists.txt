# Set minimum version of CMake.
cmake_minimum_required(VERSION 3.14)

# Set project name and version
project(5GUtilities VERSION 1.0 DESCRIPTION "5G Utilities Collection")

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories for shared headers
include_directories(shared/include)

# Create executables for each utility
add_executable(WavelengthCalculator utilities/WavelengthCalculator/src/main.cpp shared/src/utilities.cpp)
add_executable(ShannonsCapacityCalculator utilities/ShannonsCapacityCalculator/src/main.cpp shared/src/utilities.cpp)

# Locate GTest package (requires that GTest is installed)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Enable testing with Google Test
enable_testing()
add_executable(utilities_test tests/utilities_test.cpp shared/src/utilities.cpp)
target_link_libraries(utilities_test ${GTEST_LIBRARIES} pthread)

# Define CTest test cases
include(GoogleTest)
gtest_discover_tests(utilities_test)