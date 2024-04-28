#include <iostream>
#include "utilities.h"

int main() {
    double spectralEfficiency;

    std::cout << "Enter Spectral Efficiency in bits/second/Hz: " << std::endl;
    std::cin >> spectralEfficiency;

    // Get CQI Index and Intermediate Spectral Efficiency Value from CQI table
    auto cqiResult = determineIntermediateSpectralEfficiency(spectralEfficiency);

    // Get Modulation Order Qm and Code Rate R from the MCS Table
    auto mcsResult = determineModulationAndCodeRate(cqiResult.second);

    std::cout << "Modulation Order, Qm: " << mcsResult.first << std::endl;
    std::cout << "Normalized Code Rate, R: " << mcsResult.second << std::endl;

    return 0;
}