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

double calculateFrequencyFromWavelength(double wavelength) {
    // Check if the wavelength is positive and non-zero
    if (wavelength <= 0) {
        return 0.0;  // Return zero as an error indicator for invalid inputs
    }

    // Calculate the frequency
    double frequency = SPEED_OF_LIGHT / wavelength;

    return frequency;
}

double calculateShannonsCapacity(double bandwidth, double snr) {
    // Ensure that the inputs are valid
    if (bandwidth <= 0 || snr < 0) {
        return 0.0;  // Return zero as an error indicator for invalid inputs
    }
    // Calculate Shannon's Capacity using the formula: C = B * log2(1 + SNR)
    return bandwidth * log2(1 + snr);
}

double calculateOFDMSymbolDuration(double scs) {
    // The OFDM symbol duration is the inverse of the subcarrier spacing.
    // 1 Hz is the unit for SCS, which translates to 1 second. 
    // Since we want the duration in microseconds, we multiply by 1e6.
    if (scs <= 0) {
        return 0.0;  // Return zero as an error indicator for invalid inputs
    }

    return 1.0 / scs * 1e6; // Convert seconds to microseconds
}

int calculateNumberOfSubcarriers(double bandwidth, double scs) {
    // Check for valid input values
    if (bandwidth <= 0) {
        return 0;  // Return zero as an error indicator for invalid inputs
    }
    if (scs <= 0) {
        return 0;  // Return zero as an error indicator for invalid inputs
    }

    // Convert SCS from kHz to Hz for calculation
    scs *= 1000; 

    // Calculate the number of subcarriers
    int nsc = static_cast<int>(bandwidth / scs);

    return nsc;
}

int calculateFFTSize(double symbolDuration, double samplingFreq) {
    // Check for valid input values
    if (symbolDuration <= 0) {
        return 0;  // Return zero as an error indicator for invalid inputs
    }
    if (samplingFreq <= 0) {
        return 0;  // Return zero as an error indicator for invalid inputs
    }

    // Calculate the FFT size
    int fftSize = static_cast<int>(symbolDuration * samplingFreq);

    return fftSize;
}

double calculateTrafficDensity(double spectralEfficiency, double cellularDensity, double bandwidth) {
    // Calculate the traffic density GkM
    double trafficDensity = spectralEfficiency * cellularDensity * bandwidth;

    return trafficDensity;
}

double calculateCoherenceTime(double wavelength, double speed) {
    // Check for valid input values
    if (wavelength <= 0) {
        return 0.0;  // Return zero as an error indicator for invalid inputs
    }
    if (speed <= 0) {
        return 0.0;  // Return zero as an error indicator for invalid inputs
    }

    // Calculate the Coherence Time using the formula Tc = Wavelength / (2 * v)
    double coherenceTime = wavelength / (2 * speed);

    return coherenceTime;
}

double calculateCoherenceBandwidth(double delaySpread) {
    // Check if the delay spread is positive and non-zero
    if (delaySpread <= 0) {
        return 0.0;  // Return zero as an error indicator for invalid inputs
    }

    // Calculate the Coherence Bandwidth
    double coherenceBandwidth = 1.0 / delaySpread;

    return coherenceBandwidth;
}
