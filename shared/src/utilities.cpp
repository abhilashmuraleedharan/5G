#include "utilities.h"

// Speed of light constant (in meters per second)
constexpr double SPEED_OF_LIGHT = 299792458.0;

double calculateWavelength(double frequency) {
    // Check if the frequency is not zero to avoid division by zero
    if (frequency <= 0) {
        return 0.0;  // Return zero as an error indicator
    }
    return SPEED_OF_LIGHT / frequency;
}

double calculateShannonsCapacity(double bandwidth, double snr) {
    // Ensure that the inputs are valid
    if (bandwidth <= 0 || snr < 0) {
        return 0.0;  // Return zero as an error indicator for invalid inputs
    }
    // Calculate Shannon's Capacity using the formula: C = B * log2(1 + SNR)
    return bandwidth * log2(1 + snr);
}