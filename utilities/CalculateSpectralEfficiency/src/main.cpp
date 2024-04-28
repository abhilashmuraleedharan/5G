#include <iostream>
#include "utilities.h"

int main() {
    double snrLinear;

    std::cout << "Enter the linear SNR value: " << std::endl;
    std::cin >> snrLinear;

    std::cout << "Spectral Efficiency for SNR " << snrLinear << " (linear scale): "
              << calculateSpectralEfficiencyPerLayer(snrLinear)
              << " bits/second/Hz" << std::endl;

    return 0;
}
