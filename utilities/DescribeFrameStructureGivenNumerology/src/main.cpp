#include <iostream>
#include "utilities.h"

int main() {
    // Read the numerology value from the user
    int n;
    std::cout << "Enter the numerology value (n): " << std::endl;
    std::cin >> n;

    // Calculate the slot size in milliseconds
    double slotSize = calculateSlotSize(n);

    // Calculate the number of slots per subframe
    int numberOfSlots = calculateNumberOfSlots(slotSize);

    // Calculate the SCS
    double scs = calculateSCS(n);
    
    // Calculate the symbol duration
    double symbolDuration = calculateOFDMSymbolDuration(scs, false);

    // Display the results
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Symbol duration: " << symbolDuration << " milliseconds" << std::endl;
    std::cout << "Slot size: " << slotSize << " milliseconds" << std::endl;
    std::cout << "Number of slots per subframe: " << numberOfSlots << std::endl;
    std::cout << "SCS: " << scs << " kHz" << std::endl;
    std::cout << "Bandwidth per RB: " << (12 * scs) << " kHz" << std::endl;

    return 0;
}