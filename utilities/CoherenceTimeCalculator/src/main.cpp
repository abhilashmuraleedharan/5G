#include <iostream>
#include "utilities.h"

int main() {
    double wavelength;
    double speed;

    std::cout << "Enter the Wavelength in meters: ";
    std::cin >> wavelength;

    if (!std::cin || wavelength <= 0) {
        std::cerr << "Error: Please enter a positive number for Wavelength." << std::endl;
        return 1;  // Return an error code
    }

    std::cout << "Enter the speed of the wireless device in meters/sec: ";
    std::cin >> speed;

    if (!std::cin || speed <= 0) {
        std::cerr << "Error: Please enter a positive number for Speed." << std::endl;
        return 1;  // Return an error code
    }

    std::cout << "Coherence Time Tc for " << wavelength << " meters wavelength and " 
              << speed << " m/s speed: " << calculateCoherenceTime(wavelength, speed) 
              << " seconds" << std::endl;
    return 0;
}