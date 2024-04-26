#include <iostream>
#include "utilities.h"

int main() {
    int M; // Modulation order
    double b; // Bits per QAM symbol
    double sf; // Scaling factor

    // Example usage
    std::cout << "Enter the QAM Modulation Scheme Value M (e.g., 16, 64, 256): ";
    std::cin >> M;

    QamModulationSchemeDescriptor(M, b, sf);

    if (b != 0 && sf != 0) { // Check if no error
        std::cout << "Number of bits per QAM symbol (b): " << b << std::endl;
        std::cout << "Calculated scaling factor (sf): " << sf << std::endl;
        std::cout << "Actual scaling factor for power normalization (1/sqrt(sf)): " 
                  << 1 / sqrt(sf) << std::endl;
    }

    return 0;
}