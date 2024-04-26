#include <iostream>
#include "utilities.h"

int main() {
    double symbolDuration;
    double samplingFreq;

    std::cout << "Enter the OFDM Symbol Duration in seconds: ";
    std::cin >> symbolDuration;

    if (!std::cin || symbolDuration <= 0) {
        std::cerr << "Error: Please enter a positive number for OFDM Symbol Duration." << std::endl;
        return 1;  // Return an error code
    }

    std::cout << "Enter the Sampling Frequency in Hz: ";
    std::cin >> samplingFreq;

    if (!std::cin || samplingFreq <= 0) {
        std::cerr << "Error: Please enter a positive number for Sampling Frequency." << std::endl;
        return 1;  // Return an error code
    }

    std::cout << "FFT size for " << symbolDuration << " seconds symbol duration and " 
              << samplingFreq << " Hz sampling frequency: " 
              << calculateFFTSize(symbolDuration, samplingFreq) << std::endl;
    return 0;
}