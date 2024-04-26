#include <iostream>
#include "utilities.h"

int main() {
    // Example usage:
    double bandwidth;
    double scs;

    std::cout << "Enter the Bandwidth in Hz: ";
    std::cin >> bandwidth;

    if (!std::cin || bandwidth <= 0) {
        std::cerr << "Error: Please enter a positive number for bandwidth." << std::endl;
        return 1;  // Return an error code
    }

    std::cout << "Enter the SCS in kHz: ";
    std::cin >> scs;

    if (!std::cin || scs <= 0) {
        std::cerr << "Error: Please enter a positive number for SCS." << std::endl;
        return 1;  // Return an error code
    }

    std::cout << "Number of subcarriers for " << bandwidth << " Hz bandwidth and " 
              << scs << " kHz SCS: " << calculateNumberOfSubcarriers(bandwidth, scs) << std::endl;
    return 0;
}