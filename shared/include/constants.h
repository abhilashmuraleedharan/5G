#ifndef CONSTANTS_H
#define CONSTANTS_H

/**
 * @file constants.h
 * @brief Constants used by the utility functions for telecommunications calculations.
 */

constexpr double pi            = 3.14159265358979323846;
constexpr double speedOfLight  = 299792458.0; // in meters/second
constexpr    int numOfSCsPerRB = 12;

/**
 * @brief Structure to hold CQI table entries.
 */
struct CQIEntry {
    int index;
    const char* modulation;
    int codeRate;
    double intermediateSpectralEfficiency; // Expressed as bits/s/Hz
};

// CQI table
const std::vector<CQIEntry> cqiTable = {
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

/**
 * @brief Structure to hold MCS table entries.
 */
struct MCSEntry {
    int index;
    int modulationOrder; // Qm
    const char* modulationScheme;
    double mcsCodeRate; // R
    double maxSpectralEfficiency; // Maximum spectral efficiency supported
};

// MCS table
const std::vector<MCSEntry> mcsTable = {
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

// Define the TBS table
const std::vector<int> tbsTable = {
    24,32,40,48,56,64,72,80,88,96,104,112,120,128,136,144,152,160,168,176,184,192,208,224,240,256,
    272,288,304,320,336,352,368,384,408,432,456,480,504,528,552,576,608,640,672,704,736,768,808,848,
    888,928,984,1032,1064,1128,1160,1192,1224,1256,1288,1320,1352,1416,1480,1544,1608,1672,1736,1800,
    1864,1928,2024,2088,2152,2216,2280,2408,2472,2536,2600,2664,2728,2792,2856,2976,3104,3240,3368,
    3496,3624,3752,3824
};

#endif