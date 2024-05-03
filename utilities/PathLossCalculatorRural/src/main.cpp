#include <iostream>
#include "utilities.h"

int main() {
    // Example usage:
    double gNBAntennaHeight; // in meters
    double ueHeight;         // in meters
    double fLow;             // in MHz
    double fHigh;            // in MHz
    double distance2D;       // in meters
    double buildingHeight;   // in meters
    double streetWidth;      // in meters
    bool isLOS;              // Line of Sight scenario

    std::cout << "Enter the gNB antenna height in meters: " << std::endl;
    std::cin >> gNBAntennaHeight;

    if (!std::cin || gNBAntennaHeight <= 0) {
        std::cerr << "Error: Please enter a positive number for gNB antenna height." << std::endl;
        return 1;  // Return an error code
    }

    std::cout << "Enter the UE height in meters: " << std::endl;
    std::cin >> ueHeight;

    if (!std::cin || ueHeight <= 0) {
        std::cerr << "Error: Please enter a positive number for UE height." << std::endl;
        return 1;  // Return an error code
    }

    std::cout << "Enter the lower frequency of the bandwidth in MHz: " << std::endl;
    std::cin >> fLow;

    if (!std::cin || fLow <= 0) {
        std::cerr << "Error: Please enter a positive number for lower frequency." << std::endl;
        return 1;  // Return an error code
    }

    std::cout << "Enter the higher frequency of the bandwidth in MHz: " << std::endl;
    std::cin >> fHigh;

    if (!std::cin || fHigh <= 0) {
        std::cerr << "Error: Please enter a positive number for higher frequency." << std::endl;
        return 1;  // Return an error code
    }

    std::cout << "Enter the 2D distance between gNB and UE in meters: " << std::endl;
    std::cin >> distance2D;

    if (!std::cin || distance2D <= 0) {
        std::cerr << "Error: Please enter a positive number for 2D distance." << std::endl;
        return 1;  // Return an error code
    }

    std::cout << "Enter the height of the building in meters: " << std::endl;
    std::cin >> buildingHeight;

    if (!std::cin || buildingHeight <= 0) {
        std::cerr << "Error: Please enter a positive number for building height." << std::endl;
        return 1;  // Return an error code
    }

    std::cout << "Enter the street width in meters: " << std::endl;
    std::cin >> streetWidth;

    if (!std::cin || streetWidth <= 0) {
        std::cerr << "Error: Please enter a positive number for street width." << std::endl;
        return 1;  // Return an error code
    }

    char ip;
    std::cout << "Choose the Path Loss Scenario: " << std::endl;
    std::cout << "Press a for LOS\nPress b for NLOS" << std::endl;
    std::cin >> ip;
    
    switch (ip) {
        case 'a':
            isLOS = true;
            std::cout << "Chosen PathLoss Scenario is LOS" << std::endl;
            break;
        case 'b':
            isLOS = false;
            std::cout << "Chosen PathLoss Scenario is NLOS" << std::endl;
            break;
        default:
            std::cerr << "Invalid input. Exiting" << std::endl;
            return 1;
    }

    double pathLoss = calculate5GPathLossRural(gNBAntennaHeight, ueHeight, fLow, fHigh, distance2D,
                                          buildingHeight, streetWidth, isLOS, true);
                                          
    std::string message = std::string("Calculated Path Loss for Rural ");
    if (isLOS) 
        message += std::string("LOS Scenario: ");
    else
        message += std::string("NLOS Scenario: ");

    std::cout << message << pathLoss << " dB" << std::endl;

    return 0;
}
