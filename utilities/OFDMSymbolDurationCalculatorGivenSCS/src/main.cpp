#include "utilities.h"
#include <iostream>

int main() {
    // Example usage:
    double scs = 15000; // 15 kHz SCS

    std::cout << "Enter the SCS in kHz: ";
    std::cin >> scs;

    if (!std::cin || scs <= 0) {
        std::cerr << "Error: Please enter a positive number for SCS." << std::endl;
        return 1;  // Return an error code
    }

    scs = scs * 1000;

    std::cout << "OFDM symbol duration for " << scs << " Hz SCS: " 
              << calculateOFDMSymbolDuration(scs) << " microseconds" << std::endl;
    return 0;
}