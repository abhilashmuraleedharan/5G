#include "utilities.h"
#include <gtest/gtest.h>

// Test case for calculateWavelength
TEST(WavelengthCalculation, PositiveFrequency) {
    // Speed of light constant (in meters per second)
    constexpr double SPEED_OF_LIGHT = 299792458.0;

    // Test with a frequency of 300 MHz (expected wavelength = speed of light / frequency)
    double frequency = 300e6; // 300 MHz
    double expectedWavelength = SPEED_OF_LIGHT / frequency;
    ASSERT_NEAR(expectedWavelength, calculateWavelength(frequency), 0.001); // Assert near with a small epsilon
}

TEST(WavelengthCalculation, ZeroFrequency) {
    // Test with zero frequency, should handle gracefully
    ASSERT_EQ(0.0, calculateWavelength(0)); // Expect zero as error code
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}