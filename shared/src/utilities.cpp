#include "utilities.h"

double calculateWavelength(double frequency, bool logging) {
    // Check if the frequency is not zero to avoid division by zero
    if (frequency <= 0) {
        if (logging)
            std::cerr << "Frequency must be greater than 0 Hz." << std::endl;
        return 0.0;  // Return zero as an error indicator
    }
    return speedOfLight / frequency;
}

double calculateFrequencyFromWavelength(double wavelength, bool logging) {
    // Check if the wavelength is positive and non-zero
    if (wavelength <= 0) {
        if (logging)
            std::cerr << "Wavelength must be greater than 0 meters." << std::endl;
        return 0.0;  // Return zero as an error indicator for invalid inputs
    }

    // Calculate the frequency
    double frequency = speedOfLight / wavelength;

    return frequency;
}

double calculateShannonsCapacity(double bandwidth, double snr, bool logging) {
    // Ensure that the inputs are valid
    if (bandwidth <= 0 || snr < 0) {
        return 0.0;  // Return zero as an error indicator for invalid inputs
    }
    // Calculate Shannon's Capacity using the formula: C = B * log2(1 + SNR)
    return bandwidth * log2(1 + snr);
}

double calculateOFDMSymbolDuration(double scs, bool useExtendedCP, bool logging) {

    if (scs <= 0) {
        if (logging)
            std::cerr << "SCS must be greater than 0 KHz" << std::endl;
        return 0.0;  // Return zero as an error indicator for invalid inputs
    }

    int numerology = getNumerology(scs);
    int numOfSymbolsPerSlot = ((numerology == 2) && useExtendedCP) ? 12 : 14; // since extended CP is applicable only for n=2

    double ofdmSymbolDuration = (1.0 / (numOfSymbolsPerSlot * std::pow(2, numerology)));

    return ofdmSymbolDuration;
}

int calculateNumberOfSubcarriers(double bandwidth, double scs, bool logging) {
    // Check for valid input values
    if (bandwidth <= 0) {
        if (logging)
            std::cerr << "Bandwidth must be greater than 0 Hz." << std::endl;
        return 0;  // Return zero as an error indicator for invalid inputs
    }
    if (scs <= 0) {
        if (logging)
            std::cerr << "SCS must be greater than 0 kHz." << std::endl;
        return 0;  // Return zero as an error indicator for invalid inputs
    }

    // Convert SCS from kHz to Hz for calculation
    scs *= 1000; 

    // Calculate the number of subcarriers
    int nsc = static_cast<int>(bandwidth / scs);

    return nsc;
}

int calculateFFTSize(double symbolDuration, double samplingFreq, bool logging) {
    // Check for valid input values
    if (symbolDuration <= 0) {
        if (logging)
            std::cerr << "OFDM symbol duration must be greater than 0 seconds." << std::endl;
        return 0;  // Return zero as an error indicator for invalid inputs
    }
    if (samplingFreq <= 0) {
        if (logging)
            std::cerr << "Sampling frequency must be greater than 0 Hz." << std::endl;
        return 0;  // Return zero as an error indicator for invalid inputs
    }

    // Calculate the FFT size
    int fftSize = static_cast<int>(symbolDuration * samplingFreq);

    return fftSize;
}

double calculateTrafficDensity(double spectralEfficiency, double cellularDensity, double bandwidth, bool logging) {
    // Calculate the traffic density GkM
    double trafficDensity = spectralEfficiency * cellularDensity * bandwidth;

    return trafficDensity;
}

double calculateCoherenceTime(double wavelength, double speed, bool logging) {
    // Check for valid input values
    if (wavelength <= 0) {
        if (logging)
            std::cerr << "Wavelength must be greater than 0 meters." << std::endl;
        return 0.0;  // Return zero as an error indicator for invalid inputs
    }
    if (speed <= 0) {
        if (logging)
            std::cerr << "Speed must be greater than 0 meters/second." << std::endl;
        return 0.0;  // Return zero as an error indicator for invalid inputs
    }

    // Calculate the Coherence Time using the formula Tc = Wavelength / (2 * v)
    double coherenceTime = wavelength / (2 * speed);

    return coherenceTime;
}

double calculateCoherenceBandwidth(double delaySpread, bool logging) {
    // Check if the delay spread is positive and non-zero
    if (delaySpread <= 0) {
        if (logging)
            std::cerr << "Delay spread must be greater than 0 seconds." << std::endl;
        return 0.0;  // Return zero as an error indicator for invalid inputs
    }

    // Calculate the Coherence Bandwidth
    double coherenceBandwidth = 1.0 / delaySpread;

    return coherenceBandwidth;
}

double calculateSlotSize(int n, bool logging) {

    if (n < 0 && n > 4) {
        return 0.0;  // Return zero as an error indicator for invalid inputs
    }

    return 1.0 / std::pow(2, n);
}

int calculateNumberOfSlots(double slotSize, bool logging) {

    if (slotSize <= 0) {
        return 0.0;  // Return zero as an error indicator for invalid inputs
    }

    return static_cast<int>(1.0 / slotSize);
}

double calculateSCS(int n, bool logging) {

    if (n < 0 && n > 4) {
        return 0.0;  // Return zero as an error indicator for invalid inputs
    }

    return 15 * std::pow(2, n);
}

void QamModulationSchemeDescriptor(int M, double& b, double& sf, bool logging) {
    if (M <= 1 || (M & (M - 1)) != 0) { // Check if M is a power of 2 and greater than 1
        if (logging)
            std::cerr << "Invalid Modulation order. M must be a power of 2 and greater than 1." << std::endl;
        b = 0; // Resetting values to 0 as error indication
        sf = 0;
        return;
    }

    b = std::log2(M); // Calculate bits per symbol
    sf = 2.0 / 3.0 * (M - 1); // Calculate the scaling factor
}

int getNumerology(int scs) {
    switch (scs) {
        case 15:
            return 0;
        case 30:
            return 1;
        case 60:
            return 2;
        case 120:
            return 3;
        case 240:
            return 4;
        default:
            throw std::invalid_argument("Unsupported SCS value");
    }
}

double calculateLargeScaleTotalLoss(double pathLoss, double shadowingLoss, double o2iLoss, bool logging) {
    // Calculate total large-scale loss
    double totalLoss = pathLoss + shadowingLoss + o2iLoss;
    return totalLoss;
}

double calculateTransmittedPowerPerLayer(double txPower, int numOfLayers, bool logging) {
    // Calculate the transmitted power per layer using the formula provided
    double txPowerPerLayer = txPower - (10 * std::log10(numOfLayers));
    return txPowerPerLayer;
}

double calculateReceivedPowerPerLayer(double txPowerPerLayer, double totalLoss, double bfGain, bool logging) {
    // Calculate the received power using the formula provided
    double rxPowerPerLayer = txPowerPerLayer - totalLoss + bfGain;
    return rxPowerPerLayer;
}

double calculateThermalNoisePower(double temperature, double bandwidth, bool logging) {
    // Boltzmann's constant in Joules per Kelvin
    constexpr double boltzmannConstant = 1.38e-23;

    // Calculate the thermal noise power
    double thermalNoisePower = boltzmannConstant * temperature * bandwidth;

    return thermalNoisePower;
}

double dBmToWatts(double dBm, bool logging) {
    return 1e-3 * std::pow(10, dBm / 10); // 1mW * 10^(P(dBm)/10)
}

double wattsToDbm(double watts, bool logging) {
    return 10.0 * log10(watts / 0.001); // 10 * log10(watts / 0.001)
}

double calculateSNRLinear(double rxPower_dBm, double thermalNoisePower_Watts, bool logging) {
    // Convert received power from dBm to watts
    double rxPower_Watts = dBmToWatts(rxPower_dBm);

    // Calculate SNR in linear scale
    double snrLinear = rxPower_Watts / thermalNoisePower_Watts;

    return snrLinear;
}

double calculateSpectralEfficiencyPerLayer(double snrLinear, bool logging) {
    if (snrLinear < 0) {
        return 0.0;  // Return zero as an error indicator 
                     // since snrLinear is assumed to be non-negative
    }

    // Calculate spectral efficiency using the Shannon formula
    double spectralEfficiency = std::log2(1 + snrLinear);

    return spectralEfficiency;
}

std::pair<int, double> determineIntermediateSpectralEfficiency(double spectralEfficiency, bool logging) {
    // Initialize to the lowest CQI if all else fails
    int closestCQI = 0;

    // Find the closest CQI entry
    for (const auto& entry : cqiTable) {
        if (entry.intermediateSpectralEfficiency <= spectralEfficiency) {
            closestCQI = entry.index;
        } else { 
            break; // Since CQI table is sorted, we can break the loop once we pass spectralEfficiency
        }
    }

    // Fetch the values from the specified index
    int cqiIndex = cqiTable[closestCQI].index;
    double specEfficiency = cqiTable[closestCQI].intermediateSpectralEfficiency;

    // Return them as a pair
    return std::make_pair(cqiIndex, specEfficiency);
}

std::pair<int, double> determineModulationAndCodeRate(double spectralEfficiency, bool logging) {
    // Initialize to the lowest MCS if all else fails
    int closestMcsIndex = 0;

    // Find the closest MCS entry
    for (const auto& entry : mcsTable) {
        if (entry.maxSpectralEfficiency <= spectralEfficiency) {
            closestMcsIndex = entry.index;
        } else {
            break; // Since MCS table is sorted, we can break the loop once we pass spectralEfficiency
        }
    }

    // Fetch the values from the specified index
    int modulationOrder = mcsTable[closestMcsIndex].modulationOrder;
    double mcsCodeRate = mcsTable[closestMcsIndex].mcsCodeRate;

    // Return them as a pair
    return std::make_pair(modulationOrder, mcsCodeRate);

}

std::pair<int, double> determineModulationAndCodeRateUsingMcsIndex(int mcsIdx, bool logging) {
    // Validate mcsIdx argument
    if (mcsIdx < 0 || mcsIdx > 27) {
        throw std::runtime_error("Invalid MCS index");
    }

    // Fetch the values from the specified index
    int modulationOrder = mcsTable[mcsIdx].modulationOrder;
    double mcsCodeRate = mcsTable[mcsIdx].mcsCodeRate;

    // Return them as a pair
    return std::make_pair(modulationOrder, mcsCodeRate);
}

int calculateAvailableREs(int numberOfSubcarriers, int numberOfSymbols, int numberOfREsForDMRS, int overheadFromHigherLayer, bool logging) {
    // Calculate the total number of REs for data transfer
    int totalREs = numberOfSubcarriers * numberOfSymbols;

    // Calculate available REs after subtracting DMRS and other overhead
    int availableREs = totalREs - numberOfREsForDMRS - overheadFromHigherLayer;

    return availableREs;
}

int calculateActualAvailableREs(int availableREsPerRB, int numberOfAllocatedPRBs, bool logging) {
    // The UE never assumes more than 156 REs per RB
    int cappedREsPerRB = std::min(156, availableREsPerRB);

    // Calculate the total actual REs available
    int totalActualREs = cappedREsPerRB * numberOfAllocatedPRBs;

    return totalActualREs;
}

double calculateNumberOfInformationBits(int N, double codeRate, int modulationOrder, bool logging) {
    // Calculate the scaled code rate
    double R = codeRate / 1024.0;

    // Calculate the number of information bits
    double Ninfo = N * R * modulationOrder;

    return Ninfo;
}

int calculateNinfoPrime(double Ninfo, bool logging) {
    if (Ninfo <= 3824) {
        int n = std::max(3, static_cast<int>(std::floor(std::log2(Ninfo))) - 6);
        int powerOfTwo = static_cast<int>(std::pow(2, n));
        int roundedNinfo = powerOfTwo * static_cast<int>(std::floor(Ninfo / powerOfTwo));
        return std::max(24, roundedNinfo);
    } else {
        int n = static_cast<int>(std::floor(std::log2(Ninfo - 24))) - 5;
        int powerOfTwo = static_cast<int>(std::pow(2, n));
        int roundedNinfo = static_cast<int>(std::round(static_cast<double>(Ninfo - 24) / powerOfTwo) * powerOfTwo);
        return roundedNinfo;
    }
}

// When NinfoPrime <= 3824
int findTBSForNinfoPrime(int NinfoPrime, bool logging) {
    // Find the largest TBS that is less than NinfoPrime
    int maxTBS = 0; // To keep track of the maximum TBS value that is less than NinfoPrime
    for (int TBS : tbsTable) {
        if (TBS <= NinfoPrime) {
            maxTBS = TBS; // Update maxTBS with the current TBS value
        } else {
            break; // Since TBS table is sorted, we can break the loop once we pass NinfoPrime
        }
    }

    // Check if we have found a valid TBS value
    if (maxTBS == 0) {
        // In case no valid TBS is found, return the smallest TBS for now. 
        return tbsTable.front();
    }

    return maxTBS;
}

// When NinfoPrime > 3824
int calculateTBS(int NinfoPrime, int codeRate, bool logging) {
    double R = static_cast<double>(codeRate) / 1024.0; // Convert codeRate to actual fraction
    int TBS = 0;
    if (R <= 0.25) { // If R <= 1/4
        int C = std::ceil((NinfoPrime + 24) / 3816.0);
        TBS = 8 * C * std::ceil((NinfoPrime + 24) / (8.0 * C)) - 24;
    } else { // If R > 1/4
        if (NinfoPrime >= 8424) {
            int C = std::ceil((NinfoPrime + 24) / 8424.0);
            TBS = 8 * C * std::ceil((NinfoPrime + 24) / (8.0 * C)) - 24;
        } else {
            TBS = 8 * std::ceil((NinfoPrime + 24) / 8.0) - 24;
        }
    }

    return TBS;
}

int calculateTotalBitsPerPrb(int numLayers, int tbsSize, bool logging) {
    int totalBitsPerPrb = 0;
    for (int layer = 0; layer < numLayers; ++layer) {
        totalBitsPerPrb += tbsSize; // Add TBS size for each layer
    }
    return totalBitsPerPrb;
}

int calculateTotalPRBsAvailable(int prbCount, double downlinkOH, bool logging) {
    int overhead = std::ceil(prbCount * downlinkOH);
    int totalPRBAvailable = prbCount - overhead;
    return totalPRBAvailable;
}

int calculateBitsPerSlot(int bitsPerPRB, int totalPRBAvailable, bool logging) {
    int bitsPerSlot = bitsPerPRB * totalPRBAvailable;
    return bitsPerSlot;
}

double calculateDLApplicationThroughput(int bitsPerSlot, double dlFraction, double slotTime, int appPacketSize, int macPacketSize, bool logging) {
    // Calculate DL MAC Throughput
    double dlMacThroughput = (bitsPerSlot * dlFraction) / slotTime;
    if (logging)
        std::cout << "DL MAC Throughput: " << dlMacThroughput/1000 << " Mbps" << std::endl;

    // Calculate DL Application Throughput
    double throughputRatio = static_cast<double>(appPacketSize) / static_cast<double>(macPacketSize);
    double dlApplicationThroughput = dlMacThroughput * throughputRatio;

    return dlApplicationThroughput;
}

double calculateDLFraction(const std::string& ratioStr, bool logging) {
    std::istringstream iss(ratioStr);
    int dl, ul;
    char colon;

    if (!(iss >> dl >> colon >> ul) || colon != ':' || ul == 0) {
        return -1; // Return an error indicator
    }

    double totalParts = dl + ul;
    return dl / totalParts;
}

double calculate5GPathLossRural(double gNBAntennaHeight, double ueHeight, double fLow, double fHigh, double distance2D, 
                           double buildingHeight, double streetWidth, bool isLOS, bool logging) {
    // Calculate center frequency and normalized frequency
    double centerFrequency = (fLow + fHigh) / 2;
    if (logging)
        std::cout << "centerFrequency: " << centerFrequency << " MHz" << std::endl;

    // convert centerFrequency to Hz for further calculations
    centerFrequency = centerFrequency * 1e6;
    
    double fNorm = centerFrequency / 1e9; // Normalized by 1 GHz
    if (logging)
        std::cout << "fNorm: " << fNorm << " GHz" << std::endl;

    // Calculate breakpoint distance
    double breakpointDistance = 2 * pi * gNBAntennaHeight * ueHeight * (centerFrequency / speedOfLight);
    if (logging)
        std::cout << "breakPointDistance: " << breakpointDistance << std::endl;

    // Calculate 3D distance
    double distance3D = std::sqrt(distance2D * distance2D + (gNBAntennaHeight - ueHeight) * (gNBAntennaHeight - ueHeight));
    if (logging)
        std::cout << "distance3D: " << distance3D << std::endl;

    // Calculate LOS path loss for all distances to use as baseline
    double plLos = 0;
    if (distance2D >= 10 && distance2D <= breakpointDistance) {
        plLos = 20 * log10(40 * pi * distance3D * fNorm / 3) +
                std::min(0.03 * pow(buildingHeight, 1.72), 10.0) * log10(distance3D) -
                std::min(0.044 * pow(buildingHeight, 1.72), 14.77) + 0.002 * log10(buildingHeight) * distance3D;
    } else if (distance2D >= breakpointDistance && distance2D <= 10000) {
        // First calculate PL1 at breakpoint distance
        double pl1Breakpoint = 20 * log10((40 * pi * breakpointDistance * fNorm) / 3) +
                       std::min(0.03 * pow(buildingHeight, 1.72), 10.0) * log10(breakpointDistance) -
                       std::min(0.044 * pow(buildingHeight, 1.72), 14.77) + 0.002 * log10(buildingHeight) * breakpointDistance;
        // Then use PL2 formula
        plLos = pl1Breakpoint + 40 * log10(distance3D / breakpointDistance);
    }

    // Calculate NLOS path loss and compare it to LOS path loss
    double plNlos = 0;
    if (distance2D >= 10 && distance2D <= 5000) {
        plNlos = 161.04 - 7.1 * log10(streetWidth) + 7.5 * log10(buildingHeight) -
                    (24.37 - 3.7 * pow((buildingHeight / gNBAntennaHeight), 2)) * log10(gNBAntennaHeight) +
                    (43.42 - (3.1 * pow(log10(gNBAntennaHeight), 2))) * (log10(distance3D) - 3) +
                    20 * (log10(fNorm)) - (3.2 * pow(log10(11.75 * ueHeight), 2) - 4.97);
    }

    // Use the greater of the LOS and NLOS path loss values
    double pathLoss = isLOS ? plLos : std::max(plLos, plNlos);

    return pathLoss;
}
