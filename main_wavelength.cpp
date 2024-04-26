#include <iostream>
#include "utilities.h"

int main() {
    double frequency;

    std::cout << "Enter the frequency of the signal in Hz: ";
    std::cin >> frequency;

    if (!std::cin || frequency <= 0) {
        std::cerr << "Error: Please enter a positive number for frequency." << std::endl;
        return 1;  // Return an error code
    }

    double wavelength = calculateWavelength(frequency);

    std::cout << "The wavelength of the signal is: " << wavelength << " meters" << std::endl;

    return 0;
}