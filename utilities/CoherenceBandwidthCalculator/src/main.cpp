#include <iostream>
#include "utilities.h"

int main() {
    double delaySpread;

    std::cout << "Enter the Delay Spread in seconds: " << std::endl;
    std::cin >> delaySpread;

    if (!std::cin || delaySpread <= 0) {
        std::cerr << "Error: Please enter a positive number for Delay Spread." << std::endl;
        return 1;  // Return an error code
    }

    std::cout << "Coherence Bandwidth Bc for " << delaySpread << " seconds delay spread: "
              << calculateCoherenceBandwidth(delaySpread) << " Hz" << std::endl;
    return 0;
}