#include <iostream>
#include "utilities.h"

int main() {
    double bandwidth, snr;

    std::cout << "Enter the bandwidth in Hz: ";
    std::cin >> bandwidth;
    std::cout << "Enter the signal-to-noise ratio (SNR): ";
    std::cin >> snr;

    if (!std::cin || bandwidth <= 0 || snr < 0) {
        std::cerr << "Error: Please enter valid positive numbers for bandwidth and non-negative for SNR." << std::endl;
        return 1;  // Return an error code
    }

    double capacity = calculateShannonsCapacity(bandwidth, snr);

    std::cout << "Shannon's Capacity is: " << capacity << " bits per second" << std::endl;

    return 0;
}