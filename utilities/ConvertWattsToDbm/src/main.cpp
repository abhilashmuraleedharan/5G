#include <iostream>
#include "utilities.h"

int main() {
    double powerInWatts;

    std::cout << "Enter the power in Watts: " << std::endl;
    std::cin >> powerInWatts;

    double powerInDbm = wattsToDbm(powerInWatts);
    std::cout << powerInWatts << " Watts is equivalent to " << powerInDbm << " dBm." << std::endl;

    return 0;
}