#include "utilities.h"

// Speed of light constant (in meters per second)
constexpr double SPEED_OF_LIGHT = 299792458.0;

double calculateWavelength(double frequency, bool logging) {
    // Check if the frequency is not zero to avoid division by zero
    if (frequency <= 0) {
        if (logging)
            std::cerr << "Frequency must be greater than 0 Hz." << std::endl;
        return 0.0;  // Return zero as an error indicator
    }
    return SPEED_OF_LIGHT / frequency;
}

double calculateFrequencyFromWavelength(double wavelength, bool logging) {
    // Check if the wavelength is positive and non-zero
    if (wavelength <= 0) {
        if (logging)
            std::cerr << "Wavelength must be greater than 0 meters." << std::endl;
        return 0.0;  // Return zero as an error indicator for invalid inputs
    }

    // Calculate the frequency
    double frequency = SPEED_OF_LIGHT / wavelength;

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

double calculateOFDMSymbolDuration(double scs, bool logging) {
    // The OFDM symbol duration is the inverse of the subcarrier spacing.
    // 1 Hz is the unit for SCS, which translates to 1 second. 
    // Since we want the duration in microseconds, we multiply by 1e6.
    if (scs <= 0) {
        if (logging)
            std::cerr << "SCS must be greater than 0 Hz" << std::endl;
        return 0.0;  // Return zero as an error indicator for invalid inputs
    }

    return 1.0 / scs * 1e6; // Convert seconds to microseconds
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
    // Define the CQI table
    std::vector<CQIEntry> cqiTable = {
        {0,  "Modulation_Zero",    0,   0.0},
        {1,  "Modulation_QPSK",    78,  0.1523},
        {2,  "Modulation_QPSK",    193, 0.3770},
        {3,  "Modulation_QPSK",    449, 0.8770},
        {4,  "Modulation_16_QAM",  378, 1.4766},
        {5,  "Modulation_16_QAM",  490, 1.9141},
        {6,  "Modulation_16_QAM",  616, 2.4063},
        {7,  "Modulation_64_QAM",  466, 2.7305},
        {8,  "Modulation_64_QAM",  567, 3.3223},
        {9,  "Modulation_64_QAM",  666, 3.9023},
        {10, "Modulation_64_QAM",  772, 4.5234},
        {11, "Modulation_64_QAM",  873, 5.1152},
        {12, "Modulation_256_QAM", 711, 5.5547},
        {13, "Modulation_256_QAM", 797, 6.2266},
        {14, "Modulation_256_QAM", 885, 6.9141},
        {15, "Modulation_256_QAM", 948, 7.4063}
    };

    // Initialize to the lowest CQI if all else fails
    int closestCQI = 0;
    double minDiff = std::numeric_limits<double>::max();

    // Find the closest CQI entry
    for (const auto& entry : cqiTable) {
        double diff = std::fabs(entry.intermediateSpectralEfficiency - spectralEfficiency);
        if (diff < minDiff) {
            minDiff = diff;
            closestCQI = entry.index;
        }
    }

    // Fetch the values from the specified index
    int cqiIndex = cqiTable[closestCQI].index;
    double specEfficiency = cqiTable[closestCQI].intermediateSpectralEfficiency;

    // Return them as a pair
    return std::make_pair(cqiIndex, specEfficiency);
}

std::pair<int, double> determineModulationAndCodeRate(double spectralEfficiency, bool logging) {
    // Define the MCS table
    std::vector<MCSEntry> mcsTable = {
        {0,  2, "Modulation_QPSK",    120,   0.2344},
        {1,  2, "Modulation_QPSK",    193,   0.3770},
        {2,  2, "Modulation_QPSK",    308,   0.6016},
        {3,  2, "Modulation_QPSK",    449,   0.8770},
        {4,  2, "Modulation_QPSK",    602,   1.1758},
        {5,  4, "Modulation_16_QAM",  378,   1.4766},
        {6,  4, "Modulation_16_QAM",  434,   1.6953},
        {7,  4, "Modulation_16_QAM",  490,   1.9141},
        {8,  4, "Modulation_16_QAM",  553,   2.1602},
        {9,  4, "Modulation_16_QAM",  616,   2.4063},
        {10, 4, "Modulation_16_QAM",  658,   2.5703},
        {11, 6, "Modulation_64_QAM",  466,   2.7305},
        {12, 6, "Modulation_64_QAM",  517,   3.0293},
        {13, 6, "Modulation_64_QAM",  567,   3.3223},
        {14, 6, "Modulation_64_QAM",  616,   3.6094},
        {15, 6, "Modulation_64_QAM",  666,   3.9023},
        {16, 6, "Modulation_64_QAM",  719,   4.2129},
        {17, 6, "Modulation_64_QAM",  772,   4.5234},
        {18, 6, "Modulation_64_QAM",  822,   4.8164},
        {19, 6, "Modulation_64_QAM",  873,   5.1152},
        {20, 8, "Modulation_256_QAM", 682.5, 5.3320},
        {21, 8, "Modulation_256_QAM", 711,   5.5547},
        {22, 8, "Modulation_256_QAM", 754,   5.8906},
        {23, 8, "Modulation_256_QAM", 797,   6.2266},
        {24, 8, "Modulation_256_QAM", 841,   6.5703},
        {25, 8, "Modulation_256_QAM", 885,   6.9141},
        {26, 8, "Modulation_256_QAM", 916.5, 7.1602},
        {27, 8, "Modulation_256_QAM", 948,   7.4063}
    };

    // Initialize to the lowest CQI if all else fails
    int closestMcsIndex = 0;
    double minDiff = std::numeric_limits<double>::max();

    // Find the closest MCS entry
    for (const auto& entry : mcsTable) {
        double diff = std::fabs(entry.maxSpectralEfficiency - spectralEfficiency);
        if (diff < minDiff) {
            minDiff = diff;
            closestMcsIndex = entry.index;
        }
    }

    // Fetch the values from the specified index
    int modulationOrder = mcsTable[closestMcsIndex].modulationOrder;
    int mcsCodeRate = mcsTable[closestMcsIndex].mcsCodeRate;

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
    // Define the TBS table
    std::vector<int> tbsTable = {
        24,32,40,48,56,64,72,80,88,96,104,112,120,128,136,144,152,160,168,176,184,192,208,224,240,256,
        272,288,304,320,336,352,368,384,408,432,456,480,504,528,552,576,608,640,672,704,736,768,808,848,
        888,928,984,1032,1064,1128,1160,1192,1224,1256,1288,1320,1352,1416,1480,1544,1608,1672,1736,1800,
        1864,1928,2024,2088,2152,2216,2280,2408,2472,2536,2600,2664,2728,2792,2856,2976,3104,3240,3368,
        3496,3624,3752,3824
    };

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
    double fNorm = centerFrequency / 1e9; // Normalized by 1 GHz

    // Calculate breakpoint distance
    double breakpointDistance = 2 * pi * gNBAntennaHeight * ueHeight * (centerFrequency / speedOfLight);

    // Calculate 3D distance
    double distance3D = std::sqrt(distance2D * distance2D + (gNBAntennaHeight - ueHeight) * (gNBAntennaHeight - ueHeight));

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
