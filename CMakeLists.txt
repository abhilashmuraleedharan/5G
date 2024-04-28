cmake_minimum_required(VERSION 3.14)

project(5GUtilities VERSION 1.0 DESCRIPTION "5G Utilities Collection")

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories for shared headers
include_directories(shared/include)

# Add subdirectory for Google Test
add_subdirectory(googletest)

# Create executables for each utility
add_executable(WavelengthCalculator utilities/WavelengthCalculator/src/main.cpp shared/src/utilities.cpp)
add_executable(ShannonsCapacityCalculator utilities/ShannonsCapacityCalculator/src/main.cpp shared/src/utilities.cpp)
add_executable(OFDMSymbolDurationCalculatorGivenSCS utilities/OFDMSymbolDurationCalculatorGivenSCS/src/main.cpp shared/src/utilities.cpp)
add_executable(NumOfSubCarriersGivenScsAndBandwidth utilities/NumOfSubCarriersGivenScsAndBandwidth/src/main.cpp shared/src/utilities.cpp)
add_executable(FFTSizeCalculator utilities/FFTSizeCalculator/src/main.cpp shared/src/utilities.cpp)
add_executable(CalculateFrequencyGivenWavelength utilities/CalculateFrequencyGivenWavelength/src/main.cpp shared/src/utilities.cpp)
add_executable(TrafficDensityCalculator utilities/TrafficDensityCalculator/src/main.cpp shared/src/utilities.cpp)
add_executable(CoherenceTimeCalculator utilities/CoherenceTimeCalculator/src/main.cpp shared/src/utilities.cpp)
add_executable(CoherenceBandwidthCalculator utilities/CoherenceBandwidthCalculator/src/main.cpp shared/src/utilities.cpp)
add_executable(DescribeFrameStructureGivenNumerology utilities/DescribeFrameStructureGivenNumerology/src/main.cpp shared/src/utilities.cpp)
add_executable(QamModulationSchemeDescriptor utilities/QamModulationSchemeDescriptor/src/main.cpp shared/src/utilities.cpp)
add_executable(DLThroughputCalculator utilities/DLThroughputCalculator/src/main.cpp shared/src/utilities.cpp)
add_executable(PathLossCalculator5G utilities/PathLossCalculator5G/src/main.cpp shared/src/utilities.cpp)

# Enable testing with Google Test
enable_testing()
add_executable(utilities_test tests/utilities_test.cpp shared/src/utilities.cpp)

# Link utilities_test with GoogleTest and pthread
target_link_libraries(utilities_test gtest_main pthread)