#include <iostream>
#include <string>
#include "utilities.h"

int main() {
    std::cout << "\tInformation bits per TTI Slot Calculator" << std::endl;
    std::cout << "==========================================" << std::endl;

    int prbPerUE = 1;
    int mcsIndex;
    int dlInfoSymbolsPerSC;
    int numOfREsForDM_RS = 0;
    int numOfOverHeadREs = 0;
    int prbCount = 1;

    std::cout << "Enter the number of PRBs allotted to the UE" << std::endl;
    std::cin >> prbPerUE;

    std::cout << "Enter the chosen MCS Index value" << std::endl;
    std::cin >> mcsIndex;

    std::cout << "Enter the downlink information symbols per sub carrier" << std::endl;
    std::cin >> dlInfoSymbolsPerSC;

    std::pair<int, double> cqiResult;
    try {
        cqiResult = determineModulationAndCodeRateUsingMcsIndex(mcsIndex);
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    int availableREsPerRB = calculateAvailableREs(numOfSCsPerRB, dlInfoSymbolsPerSC, numOfREsForDM_RS, numOfOverHeadREs);
    int accomadatableREs = calculateActualAvailableREs(availableREsPerRB, prbPerUE);

    double nInfo = accomadatableREs * cqiResult.first * (cqiResult.second/1024);
    std::cout << std::fixed << std::setprecision(6); // Set precision as needed
    std::cout << "nInfo: " << nInfo << std::endl;
    
    int tbsSize = 0;
    if (nInfo <= 3824) {
        std::cout << "nInfo is less than or equal to 3824" << std::endl;
        std::cout << "Calculating nInfoPrime..." << std::endl;
        int nInfoPrime = calculateNinfoPrime(nInfo);
        std::cout << "nInfoPrime: " << nInfoPrime << std::endl;
        std::cout << "Find the TBS size for the calculated NinfoPrime using the TBS Calculation table..." << std::endl;
        tbsSize = findTBSForNinfoPrime(nInfoPrime);
    } else {
        std::cout << "nInfo is greater than 3824" << std::endl;
        std::cout << "Calculating nInfoPrime..." << std::endl;
        int nInfoPrime = calculateNinfoPrime(nInfo);
        std::cout << "nInfoPrime: " << nInfoPrime << std::endl;
        std::cout << "Calculate the TBS size when Ninfo > 3824 using specified conditions..." << std::endl;
        tbsSize = calculateTBS(nInfoPrime, cqiResult.second);
    }
    std::cout << "TBS Size: " << tbsSize << std::endl;

    return 0;
}


