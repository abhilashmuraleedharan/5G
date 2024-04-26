#include <iostream>
#include "utilities.h"

int main() {
    double wavelength;

    std::cout << "Enter the wavelength in meters: ";
    std::cin >> wavelength;

    if (!std::cin || wavelength <= 0) {
        std::cerr << "Error: Please enter a positive number for wavelength." << std::endl;
        return 1;  // Return an error code
    }

    std::cout << "Frequency for " << wavelength << " meters wavelength: " 
              << calculateFrequencyFromWavelength(wavelength) << " Hz" << std::endl;
    return 0;
}