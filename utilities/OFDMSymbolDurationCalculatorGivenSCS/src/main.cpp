#include "utilities.h"
#include <iostream>

int main() {
    double scs;
    char cp;
    bool isExtendedCP = false;

    std::cout << "Enter the SCS in kHz: " << std::endl;
    std::cin >> scs;

    if (!std::cin || scs <= 0) {
        std::cerr << "Error: Please enter a positive number for SCS." << std::endl;
        return 1;  // Return an error code
    }

    if (scs == 60) {
        std::cout << "Enter y if extended Cyclic Prefix is applicable. If not enter n" << std::endl;
        std::cin >> cp;
        if (cp == 'y') {
            std::cout << "OFDM symbol duration will be calculated by considering Extended CP" << std::endl;
            isExtendedCP = true;
        } else if (cp == 'n') {
            std::cout << "OFDM symbol duration will be calculated by considering normal CP" << std::endl;
        } else {
            std::cerr << "Invalid input! OFDM symbol duration will be calculated by considering normal CP" << std::endl;
        }
    }

    std::cout << "OFDM symbol duration for " << scs << " kHz SCS: " 
              << calculateOFDMSymbolDuration(scs, isExtendedCP) << " milliseconds" << std::endl;
    return 0;
}