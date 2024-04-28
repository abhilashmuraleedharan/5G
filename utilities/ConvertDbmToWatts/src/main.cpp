#include <iostream>
#include "utilities.h"

int main() {
    double powerInDbm;

    std::cout << "Enter the power in dBm: " << std::endl;
    std::cin >> powerInDbm;

    double powerInWatts = dBmToWatts(powerInDbm);
    std::cout << powerInDbm << " dBm is equivalent to " << powerInWatts << " Watts." << std::endl;

    return 0;
}