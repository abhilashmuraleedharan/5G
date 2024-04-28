#include <iostream>
#include "utilities.h"

int main() {
    double spectralEfficiency; // bits/second/Hz/cell
    double cellularDensity; // cells/km^2
    double bandwidth;

    std::cout << "Enter the Spectral Efficiency in bits/second/Hz/cell: " << std::endl;
    std::cin >> spectralEfficiency;

    if (!std::cin || spectralEfficiency < 0) {
        std::cerr << "Error: Please enter a positive number for Spectral Efficiency." << std::endl;
        return 1;  // Return an error code
    }

    std::cout << "Enter the Cellular Density in cells/km^2: " << std::endl;
    std::cin >> cellularDensity;

    if (!std::cin || cellularDensity < 0) {
        std::cerr << "Error: Please enter a positive number for Cellular Density." << std::endl;
        return 1;  // Return an error code
    }

    std::cout << "Enter the Bandwidth in Hz: " << std::endl;
    std::cin >> bandwidth;

    if (!std::cin || bandwidth < 0) {
        std::cerr << "Error: Please enter a positive number for Bandwidth." << std::endl;
        return 1;  // Return an error code
    }

    std::cout << "Traffic density GkM for " << spectralEfficiency << " bits/second/Hz/cell, "
              << cellularDensity << " cells/km^2 and " << bandwidth << " Hz bandwidth: "
              << calculateTrafficDensity(spectralEfficiency, cellularDensity, bandwidth) 
              << " bits/second/km^2" << std::endl;
    return 0;
}