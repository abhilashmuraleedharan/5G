#include "utilities.h"
#include <gtest/gtest.h>

// Test case for calculateWavelength
TEST(UtilityTests, PositiveFrequency) {
    // Speed of light constant (in meters per second)
    constexpr double SPEED_OF_LIGHT = 299792458.0;

    // Test with a frequency of 300 MHz (expected wavelength = speed of light / frequency)
    double frequency = 300e6; // 300 MHz
    double expectedWavelength = SPEED_OF_LIGHT / frequency;
    ASSERT_NEAR(expectedWavelength, calculateWavelength(frequency), 0.001); // Assert near with a small epsilon
}

TEST(UtilityTests, ZeroFrequency) {
    // Test with zero frequency, should handle gracefully
    ASSERT_EQ(0.0, calculateWavelength(0)); // Expect zero as error code
}

TEST(UtilityTests, CalculateLargeScaleTotalLoss) {
    EXPECT_DOUBLE_EQ(calculateLargeScaleTotalLoss(100.0, 10.0, 5.0), 115.0);
    EXPECT_DOUBLE_EQ(calculateLargeScaleTotalLoss(80.5, 20.0, 1.5), 102.0);
}

TEST(UtilityTests, CalculateThermalNoisePower) {
    // Corrected expected value calculation:
    double k = 1.38e-23;  // Boltzmann's constant
    double T = 300;       // Temperature in Kelvin
    double B = 1e9;       // Bandwidth in Hz
    double expectedNoisePower = k * T * B;
    EXPECT_NEAR(calculateThermalNoisePower(T, B), expectedNoisePower, 1e-20);
}

TEST(UtilityTests, CalculateTransmittedPowerPerLayer) {
    EXPECT_DOUBLE_EQ(calculateTransmittedPowerPerLayer(30, 1), 30);
    EXPECT_NEAR(calculateTransmittedPowerPerLayer(30, 2), 27, 0.1);  // Assuming logging is off, checks near 27 dBm
    EXPECT_NEAR(calculateTransmittedPowerPerLayer(30, 4), 24, 0.1);  // 30 - 10*log10(4) ≈ 24
}

TEST(UtilityTests, CalculateReceivedPowerPerLayer) {
    EXPECT_DOUBLE_EQ(calculateReceivedPowerPerLayer(30, 10, 5), 25);
    EXPECT_DOUBLE_EQ(calculateReceivedPowerPerLayer(50, 20, 10), 40);
}

TEST(UtilityTests, ConvertPowerdBmToWattsAndBack) {
    double power_dBm = 30;
    double power_W = dBmToWatts(power_dBm);
    EXPECT_NEAR(power_W, 1e-3 * pow(10, 30/10.0), 1e-9);
    EXPECT_DOUBLE_EQ(wattsToDbm(power_W), 30);
}

TEST(UtilityTests, CalculateSNRLinear) {
    double rxPower_dBm = 30;  // A typical received power level
    double rxPower_Watts = dBmToWatts(rxPower_dBm);
    double thermalNoisePower_Watts = 1e-9;  // Noise power in watts (1 nW)
    double expectedSNR = rxPower_Watts / thermalNoisePower_Watts;
    EXPECT_NEAR(calculateSNRLinear(rxPower_dBm, thermalNoisePower_Watts), expectedSNR, 1e-5);
}

TEST(UtilityTests, CalculateSpectralEfficiencyPerLayer) {
    double snrLinear = 1000;  // SNR of 1000:1
    EXPECT_NEAR(calculateSpectralEfficiencyPerLayer(snrLinear), log2(1 + snrLinear), 0.001);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
