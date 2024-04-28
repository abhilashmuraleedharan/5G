#include <iostream>
#include <string>
#include "utilities.h"

int main() {
    std::cout << "\nRunning Analytical Data Throughput Calculator" << std::endl;
    std::cout << "===============================================" << std::endl;

    char ip;
    int numOfLayers; // number of spatial layers
    int bandwidth; // in MHz
    int bandwidthInHz;
    int totalTransmitPower; // in dBm
    double pathLoss; // in dB
    int prbCount; // sets the total PRBs available to distribute among the UEs.

    // Hard Coded Values chosen for this simple DL Throughput calculator
    std::string dl_ul_ratio = "4:1";
    int applicationPacketSize = 1460; // in bytes
    int macPacketSize = 1488; // in bytes
    int numerology = 3;
    int prbPerUE = 1;  // set as 1 to calculate the minimum throughput that a UE can expect 
                       // when it is given the minimal resource allocation.
    int numOfSCsPerRB = 12;
    int numOfSymbolsPerSlot = 14;
    int numOfREsForDM_RS = 0;
    int numOfOverHeadREs = 0;
    int temperatureInKelvin = 300;
    int shadowingLoss = 0; // in dB
    int o2iLoss = 0; // in dB
    int beamFormingGainPerLayer = 0; // in dB 

    std::cout << "Choose the MIMO Configuration: " << std::endl;
    std::cout << "Press a for 1*1\nPress b for 2*2\nPress c for 4*4\nPress d for 8*8" << std::endl;
    std::cin >> ip;
    
    switch (ip) {
        case 'a':
            numOfLayers = 1;
            std::cout << "Chosen MIMO Configuration is 1 X 1" << std::endl;
            break;
        case 'b':
            numOfLayers = 2;
            std::cout << "Chosen MIMO Configuration is 2 X 2" << std::endl;
            break;
        case 'c':
            numOfLayers = 4;
            std::cout << "Chosen MIMO Configuration is 4 X 4" << std::endl;
            break;
        case 'd':
            numOfLayers = 8;
            std::cout << "Chosen MIMO Configuration is 8 X 8" << std::endl;
            break;
        default:
            std::cerr << "Invalid input. Exiting" << std::endl;
            return 1;
    }

    std::cout << "\nEnter bandwidth of operation in MHz: " << std::endl;
    std::cin >> bandwidth;
    if (!std::cin || bandwidth <= 0) {
        std::cerr << "Error: Please enter a positive number for bandwidth." << std::endl;
        return 1;
    } else {
        bandwidthInHz = static_cast<int>(bandwidth * 1e6);
        std::cout << "Bandwidth to use for calculation is " << bandwidthInHz << " Hz" << std::endl;
    }

    std::cout << "\nEnter transmit power in dBm: " << std::endl;
    std::cin >> totalTransmitPower;
    if (!std::cin || totalTransmitPower <= 0) {
        std::cerr << "Error: Please enter a positive number for transmit power." << std::endl;
        return 1;
    } else {
        std::cout << "Transmit Power to use for calculation is " << totalTransmitPower << " dBm" << std::endl;
    }

    std::cout << "\nEnter pathloss value observed (when experimented in NetSim) using same chosen configurations in dB: " << std::endl;
    std::cin >> pathLoss;
    if (!std::cin || pathLoss <= 0) {
        std::cerr << "Error: Please enter a positive number for pathLoss." << std::endl;
        return 1;
    } else {
        std::cout << "Path Loss to use for calculation is " << pathLoss << " dB\n" << std::endl;
    }

    std::cout << "\nEnter PRB Count set in gNB: " << std::endl;
    std::cin >> prbCount;
    if (!std::cin || prbCount <= 0) {
        std::cerr << "Error: Please enter a positive number for PRB Count." << std::endl;
        return 1;
    } else {
        std::cout << "PRB Count to use for calculation is " << prbCount << std::endl;
    }

    std::cout << "\nDisplaying the predefined settings in this calculator" << std::endl;
    std::cout << "=====================================================" << std::endl;
    std::cout << "Numerology: " << numerology << std::endl;
    std::cout << "nPRB: " << prbPerUE << std::endl;
    std::cout << "DL UL Ratio: " << dl_ul_ratio << std::endl;
    std::cout << "Application Packet Size: " << applicationPacketSize << " bytes" << std::endl;
    std::cout << "MAC Packet Size: " << macPacketSize << " bytes" << std::endl;
    std::cout << "Temperature used to calculate thermal noise: " << temperatureInKelvin << " Kelvin\n" << std::endl;

    std::cout << "Calculating DL Data Throughput...\n" << std::endl;
    
    std::cout << "Step 1: Calculate Large-scale Total Loss" << std::endl;
    double lsTotalLoss = calculateLargeScaleTotalLoss(pathLoss, shadowingLoss, o2iLoss);
    std::cout << "Large-scale Total Loss = " << lsTotalLoss << " dB" << std::endl;

    std::cout << "\nStep 2: Calculate Rx Power dBm: " << std::endl;
    double txPowerPerLayer = calculateTransmittedPowerPerLayer(totalTransmitPower, numOfLayers);
    std::cout << "Tx Power Per Layer = " << txPowerPerLayer << " dBm" << std::endl;
    double rxPowerPerLayer = calculateReceivedPowerPerLayer(txPowerPerLayer, lsTotalLoss, beamFormingGainPerLayer);
    std::cout << "Rx Power: " << rxPowerPerLayer << " dBm" << std::endl;

    std::cout << "\nStep 3: Calculate Thermal Noise Power" << std::endl;
    double thermalNoisePower = calculateThermalNoisePower(temperatureInKelvin, bandwidthInHz);
    std::cout << "Thermal Noise Power: " << thermalNoisePower << " watts" << std::endl;

    std::cout << "\nStep 4: Calculate SNR (Linear)" << std::endl;
    std::cout << "Converting Rx Power into watts.." << std::endl;
    double rxPowerInWatts = dBmToWatts(rxPowerPerLayer); 
    std::cout << "Rx Power in watts: " << rxPowerInWatts << std::endl;
    double linearSNR = calculateSNRLinear(rxPowerPerLayer, thermalNoisePower); 
    std::cout << "SNR (Linear): " << linearSNR << std::endl;

    std::cout << "\nStep 5: Calculate Spectral Efficiency" << std::endl;
    double spectralEfficiency = calculateSpectralEfficiencyPerLayer(linearSNR);
    std::cout << "Spectral Efficiency: " << spectralEfficiency << std::endl;

    std::cout << "\nStep 6: Determine CQI Index and Intermediate Spectral Efficiency" << std::endl;
    auto cqiResult = determineIntermediateSpectralEfficiency(spectralEfficiency);
    std::cout << "CQI Index: " << cqiResult.first << std::endl;
    std::cout << "Intermediate Spectral Efficiency: " << cqiResult.second << std::endl;

    std::cout << "\nStep 7: Detemine Modulation Order and MCS Code Rate" << std::endl;
    auto mcsResult = determineModulationAndCodeRate(cqiResult.second);
    int modulationOrder = mcsResult.first;
    int mcsCodeRate = mcsResult.second;
    std::cout << "Modulation Order Qm: " << modulationOrder << std::endl;
    std::cout << "MCS Code Rate R: " << mcsCodeRate << std::endl;

    std::cout << "\nStep 8: Calculate number of Resource Elements per RB" << std::endl;
    int availableRE = calculateAvailableREs(numOfSCsPerRB, numOfSymbolsPerSlot, numOfREsForDM_RS, numOfOverHeadREs);
    std::cout << "Number of REs per RB: " << availableRE << std::endl;

    std::cout << "\nStep 9: Calculate Total number of Resource Elements allocated for PDSCH" << std::endl;
    int actualAvailableRE = calculateActualAvailableREs(availableRE, prbPerUE);
    std::cout << "Total number of Resource Elements allocated for PDSCH: " << actualAvailableRE << std::endl;

    std::cout << "\nStep 10: Calculate intermediate number of information bits" << std::endl;
    double nInfo = calculateNumberOfInformationBits(actualAvailableRE, mcsCodeRate, modulationOrder);
    std::cout << "Intermediate number of information bits: " << nInfo << std::endl;

    std::cout << "\nStep 11: Calculate TBS Size" << std::endl;
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
        tbsSize = calculateTBS(nInfoPrime, mcsCodeRate);
    }
    std::cout << "TBS Size: " << tbsSize << std::endl;

    std::cout << "\nStep 12: Calculate total bits per PRB across all available layers" << std::endl;
    int totalBitsPerPrb = calculateTotalBitsPerPrb(numOfLayers, tbsSize);
    std::cout << "Total Bits per PRB across layers: " << totalBitsPerPrb << std::endl;

    std::cout << "\nStep 13: Calculate total PRB available" << std::endl;
    int totalPRBAvailable = calculateTotalPRBsAvailable(prbCount); // use default OH value of 0.18
    std::cout << "Total PRB available: " << totalPRBAvailable << std::endl;

    std::cout << "\nStep 14: Calculate Bits per Slot" << std::endl;
    int bitsPerSlot = calculateBitsPerSlot(totalBitsPerPrb, totalPRBAvailable);
    std::cout << "Bits per slot is: " << bitsPerSlot << std::endl;

    std::cout << "\nStep 15: Calculate DL Application Throughput" << std::endl;
    std::cout << "Calculating DL Fraction..." << std::endl;
    double dlFraction = calculateDLFraction(dl_ul_ratio);
    std::cout << "DL Fraction: " << dlFraction << std::endl;
    std::cout << "Calculating slot time..." << std::endl;
    double slotDuration = calculateSlotSize(numerology);
    std::cout << "Slot Duration: " << slotDuration << std::endl;
    double dlAppThroughput = calculateDLApplicationThroughput(bitsPerSlot, dlFraction, slotDuration, applicationPacketSize, macPacketSize);
    std::cout << "DL Application Throughput: " << dlAppThroughput/1000 << " Mbps\n" << std::endl;

    return 0;
}