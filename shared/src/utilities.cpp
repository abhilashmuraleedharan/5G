#include "utilities.h"

// Speed of light constant (in meters per second)
constexpr double SPEED_OF_LIGHT = 299792458.0;

double calculateWavelength(double frequency) {
    // Check if the frequency is not zero to avoid division by zero
    if (frequency <= 0) {
        return 0.0;  // Return zero as an error indicator
    }
    return SPEED_OF_LIGHT / frequency;
}

double calculateFrequencyFromWavelength(double wavelength) {
    // Check if the wavelength is positive and non-zero
    if (wavelength <= 0) {
        return 0.0;  // Return zero as an error indicator for invalid inputs
    }

    // Calculate the frequency
    double frequency = SPEED_OF_LIGHT / wavelength;

    return frequency;
}

double calculateShannonsCapacity(double bandwidth, double snr) {
    // Ensure that the inputs are valid
    if (bandwidth <= 0 || snr < 0) {
        return 0.0;  // Return zero as an error indicator for invalid inputs
    }
    // Calculate Shannon's Capacity using the formula: C = B * log2(1 + SNR)
    return bandwidth * log2(1 + snr);
}

double calculateOFDMSymbolDuration(double scs) {
    // The OFDM symbol duration is the inverse of the subcarrier spacing.
    // 1 Hz is the unit for SCS, which translates to 1 second. 
    // Since we want the duration in microseconds, we multiply by 1e6.
    if (scs <= 0) {
        return 0.0;  // Return zero as an error indicator for invalid inputs
    }

    return 1.0 / scs * 1e6; // Convert seconds to microseconds
}

int calculateNumberOfSubcarriers(double bandwidth, double scs) {
    // Check for valid input values
    if (bandwidth <= 0) {
        return 0;  // Return zero as an error indicator for invalid inputs
    }
    if (scs <= 0) {
        return 0;  // Return zero as an error indicator for invalid inputs
    }

    // Convert SCS from kHz to Hz for calculation
    scs *= 1000; 

    // Calculate the number of subcarriers
    int nsc = static_cast<int>(bandwidth / scs);

    return nsc;
}

int calculateFFTSize(double symbolDuration, double samplingFreq) {
    // Check for valid input values
    if (symbolDuration <= 0) {
        return 0;  // Return zero as an error indicator for invalid inputs
    }
    if (samplingFreq <= 0) {
        return 0;  // Return zero as an error indicator for invalid inputs
    }

    // Calculate the FFT size
    int fftSize = static_cast<int>(symbolDuration * samplingFreq);

    return fftSize;
}

double calculateTrafficDensity(double spectralEfficiency, double cellularDensity, double bandwidth) {
    // Calculate the traffic density GkM
    double trafficDensity = spectralEfficiency * cellularDensity * bandwidth;

    return trafficDensity;
}

double calculateCoherenceTime(double wavelength, double speed) {
    // Check for valid input values
    if (wavelength <= 0) {
        return 0.0;  // Return zero as an error indicator for invalid inputs
    }
    if (speed <= 0) {
        return 0.0;  // Return zero as an error indicator for invalid inputs
    }

    // Calculate the Coherence Time using the formula Tc = Wavelength / (2 * v)
    double coherenceTime = wavelength / (2 * speed);

    return coherenceTime;
}

double calculateCoherenceBandwidth(double delaySpread) {
    // Check if the delay spread is positive and non-zero
    if (delaySpread <= 0) {
        return 0.0;  // Return zero as an error indicator for invalid inputs
    }

    // Calculate the Coherence Bandwidth
    double coherenceBandwidth = 1.0 / delaySpread;

    return coherenceBandwidth;
}

double calculateSlotSize(int n) {

    if (n < 0 && n > 4) {
        return 0.0;  // Return zero as an error indicator for invalid inputs
    }

    return 1.0 / std::pow(2, n);
}

int calculateNumberOfSlots(double slotSize) {

    if (slotSize <= 0) {
        return 0.0;  // Return zero as an error indicator for invalid inputs
    }

    return static_cast<int>(1.0 / slotSize);
}

double calculateSCS(int n) {

    if (n < 0 && n > 4) {
        return 0.0;  // Return zero as an error indicator for invalid inputs
    }

    return 15 * std::pow(2, n);
}

void QamModulationSchemeDescriptor(int M, double& b, double& sf) {
    if (M <= 1 || (M & (M - 1)) != 0) { // Check if M is a power of 2 and greater than 1
        // Invalid Modulation order. M must be a power of 2 and greater than 1
        b = 0; // Resetting values to 0 as error indication
        sf = 0;
        return;
    }

    b = std::log2(M); // Calculate bits per symbol
    sf = 2.0 / 3.0 * (M - 1); // Calculate the scaling factor
}

double calculateLargeScaleTotalLoss(double pathLoss, double shadowingLoss, double o2iLoss) {
    // Calculate total large-scale loss
    double totalLoss = pathLoss + shadowingLoss + o2iLoss;
    return totalLoss;
}

double calculateTransmittedPowerPerLayer(double txPower, int numOfLayers) {
    // Calculate the transmitted power per layer using the formula provided
    double txPowerPerLayer = txPower - (10 * std::log10(numOfLayers));
    return txPowerPerLayer;
}

double calculateReceivedPowerPerLayer(double txPowerPerLayer, double totalLoss, double bfGain) {
    // Calculate the received power using the formula provided
    double rxPowerPerLayer = txPowerPerLayer - totalLoss + bfGain;
    return rxPowerPerLayer;
}

double calculateThermalNoisePower(double temperature, double bandwidth) {
    // Boltzmann's constant in Joules per Kelvin
    constexpr double boltzmannConstant = 1.38e-23;

    // Calculate the thermal noise power
    double thermalNoisePower = boltzmannConstant * temperature * bandwidth;

    return thermalNoisePower;
}

double dBmToWatts(double dBm) {
    return 1e-3 * std::pow(10, dBm / 10); // Convert dBm to Watts
}

double calculateSNRLinear(double rxPower_dBm, double thermalNoisePower_Watts) {
    // Convert received power from dBm to watts
    double rxPower_Watts = dBmToWatts(rxPower_dBm);

    // Calculate SNR in linear scale
    double snrLinear = rxPower_Watts / thermalNoisePower_Watts;

    return snrLinear;
}

double calculateSpectralEfficiencyPerLayer(double snrLinear) {
    if (snrLinear < 0) {
        return 0.0;  // Return zero as an error indicator 
                     // since snrLinear is assumed to be non-negative
    }

    // Calculate spectral efficiency using the Shannon formula
    double spectralEfficiency = std::log2(1 + snrLinear);

    return spectralEfficiency;
}

std::pair<int, double> determineIntermediateSpectralEfficiency(double spectralEfficiency) {
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

std::pair<int, double> determineModulationAndCodeRate(double spectralEfficiency) {
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

int calculateAvailableREs(int numberOfSubcarriers, int numberOfSymbols, int numberOfREsForDMRS, int overheadFromHigherLayer) {
    // Calculate the total number of REs for data transfer
    int totalREs = numberOfSubcarriers * numberOfSymbols;

    // Calculate available REs after subtracting DMRS and other overhead
    int availableREs = totalREs - numberOfREsForDMRS - overheadFromHigherLayer;

    return availableREs;
}

int calculateActualAvailableREs(int availableREsPerRB, int numberOfAllocatedPRBs) {
    // The UE never assumes more than 156 REs per RB
    int cappedREsPerRB = std::min(156, availableREsPerRB);

    // Calculate the total actual REs available
    int totalActualREs = cappedREsPerRB * numberOfAllocatedPRBs;

    return totalActualREs;
}

double calculateNumberOfInformationBits(int N, double codeRate, int modulationOrder) {
    // Calculate the scaled code rate
    double R = codeRate / 1024.0;

    // Calculate the number of information bits
    double Ninfo = N * R * modulationOrder;

    return Ninfo;
}

int calculateNinfoPrime(double Ninfo) {
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
int findTBSForNinfoPrime(int NinfoPrime) {
    // Define the TBS table
    std::vector<TBSEntry> tbsTable = {
        {1,24},{2,32},{3,40},{4,48},{5,56},{6,64},{7,72},{8,80},{9,88},{10,96},
        {11,104},{12,112},{13,120},{14,128},{15,136},{16,144},{17,152},{18,160},
        {19,168},{20,176},{21,184},{22,192},{23,208},{24,224},{25,240},{26,256},
        {27,272},{28,288},{29,304},{30,320},{31,336},{32,352},{33,368},{34,384},
        {35,408},{36,432},{37,456},{38,480},{39,504},{40,528},{41,552},{42,576},
        {43,608},{44,640},{45,672},{46,704},{47,736},{48,768},{49,808},{50,848},
        {51,888},{52,928},{53,984},{54,1032},{55,1064},{56,1128},{57,1160},{58,1192},
        {59,1224},{60,1256},{61,1288},{62,1320},{63,1352},{64,1416},{65,1480},
        {66,1544},{67,1608},{68,1672},{69,1736},{70,1800},{71,1864},{72,1928},
        {73,2024},{74,2088},{75,2152},{76,2216},{77,2280},{78,2408},{79,2472},
        {80,2536},{81,2600},{82,2664},{83,2728},{84,2792},{85,2856},{86,2976},
        {87,3104},{88,3240},{89,3368},{90,3496},{91,3624},{92,3752},{93,3824}
    };

    // Use std::find_if to find the first entry where TBS >= NinfoPrime
    auto it = std::find_if(tbsTable.begin(), tbsTable.end(), [NinfoPrime](const TBSEntry& entry) {
        return entry.TBS >= NinfoPrime;
    });

    if (it != tbsTable.end()) {
        return it->TBS;
    } else {
        // In case no valid TBS is found, return the largest TBS or handle error
        return tbsTable.back().TBS; // Returning the largest TBS as a fallback for now
    }
}

// When NinfoPrime > 3824
int calculateTBS(int NinfoPrime, int codeRate) {
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

int calculateTotalBitsPerPrb(int numLayers, int tbsSize) {
    int totalBitsPerPrb = 0;
    for (int layer = 0; layer < numLayers; ++layer) {
        totalBitsPerPrb += tbsSize; // Add TBS size for each layer
    }
    return totalBitsPerPrb;
}

int calculateTotalPRBsAvailable(int prbCount, double downlinkOH) {
    int overhead = std::ceil(prbCount * downlinkOH);
    int totalPRBAvailable = prbCount - overhead;
    return totalPRBAvailable;
}

int calculateBitsPerSlot(int bitsPerPRB, int totalPRBAvailable) {
    int bitsPerSlot = bitsPerPRB * totalPRBAvailable;
    return bitsPerSlot;
}

double calculateDLApplicationThroughput(int bitsPerSlot, double dlFraction, double slotTime, int appPacketSize, int macPacketSize) {
    // Calculate DL MAC Throughput
    double dlMacThroughput = (bitsPerSlot * dlFraction) / slotTime;

    // Calculate DL Application Throughput
    double throughputRatio = static_cast<double>(appPacketSize) / static_cast<double>(macPacketSize);
    double dlApplicationThroughput = dlMacThroughput * throughputRatio;

    return dlApplicationThroughput;
}

double calculateDLFraction(const std::string& ratioStr) {
    std::istringstream iss(ratioStr);
    int dl, ul;
    char colon;

    if (!(iss >> dl >> colon >> ul) || colon != ':' || ul == 0) {
        return -1; // Return an error indicator
    }

    double totalParts = dl + ul;
    return dl / totalParts;
}
