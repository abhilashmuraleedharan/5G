#ifndef UTILITIES_H
#define UTILITIES_H

/**
 * @file utilities.h
 * @brief Utility functions for telecommunications calculations.
 */

#include <cmath>
#include <cmath> // For log2 and pow functions
#include <iomanip>
#include <vector>
#include <utility>
#include <algorithm>
#include <string>
#include <sstream> // For string stream operations
#include <iostream>

// Constants
const double pi = 3.14159265358979323846;
const double speedOfLight = 3e8; // Speed of light in meters/second

/**
 * Calculates the wavelength of a signal given its frequency.
 * 
 * @param frequency Frequency of the signal in hertz (Hz).
 * @param logging Boolean flag to enable or disable logging functionality
 * @return Wavelength in meters (m).
 */
double calculateWavelength(double frequency, bool logging=false);

/**
 * @brief Calculate the frequency from wavelength.
 *
 * Given the wavelength in meters, this function calculates the frequency in Hz
 * using the speed of light (c).
 *
 * @param wavelength The wavelength in meters.
 * @param logging Boolean flag to enable or disable logging functionality
 * @return The frequency in Hz.
 */
double calculateFrequencyFromWavelength(double wavelength, bool logging=false);

/**
 * Calculates Shannon's Capacity given bandwidth and signal-to-noise ratio.
 * 
 * @param bandwidth The bandwidth in hertz (Hz).
 * @param snr The signal-to-noise ratio (dimensionless).
 * @param logging Boolean flag to enable or disable logging functionality
 * @return Shannon's Capacity in bits per second (bps).
 */
double calculateShannonsCapacity(double bandwidth, double snr, bool logging=false);

/**
 * @brief Calculate the OFDM symbol duration.
 *
 * This function takes the subcarrier spacing (SCS) in Hz and
 * calculates the Orthogonal Frequency-Division Multiplexing (OFDM)
 * symbol duration in microseconds.
 *
 * @param scs Subcarrier spacing in Hz.
 * @param logging Boolean flag to enable or disable logging functionality
 * @return OFDM symbol duration in microseconds.
 */
double calculateOFDMSymbolDuration(double scs, bool logging=false);

/**
 * @brief Calculate the number of subcarriers (Nsc).
 *
 * Given the bandwidth in Hz and the subcarrier spacing (SCS) in kHz, 
 * this function calculates and returns the number of subcarriers.
 *
 * @param bandwidth The system bandwidth in Hz.
 * @param scs Subcarrier spacing in kHz.
 * @param logging Boolean flag to enable or disable logging functionality
 * @return The number of subcarriers (Nsc).
 */
int calculateNumberOfSubcarriers(double bandwidth, double scs, bool logging=false);

/**
 * @brief Calculate the FFT size.
 *
 * Given the OFDM symbol duration in seconds and the sampling frequency in Hz,
 * this function calculates and returns the FFT size.
 *
 * @param symbolDuration OFDM symbol duration in seconds.
 * @param samplingFreq Sampling frequency in Hz.
 * @param logging Boolean flag to enable or disable logging functionality
 * @return The FFT size.
 */
int calculateFFTSize(double symbolDuration, double samplingFreq, bool logging=false);

/**
 * @brief Calculate the traffic density GkM.
 *
 * Given the spectral efficiency, cellular density, and bandwidth, this function calculates
 * the traffic density (GkM).
 *
 * @param spectralEfficiency Spectral efficiency in bits/second/Hz/cell.
 * @param cellularDensity Cellular density in cells per square kilometer.
 * @param bandwidth Bandwidth in Hz.
 * @param logging Boolean flag to enable or disable logging functionality
 * @return Traffic density (GkM) in bits/second/km^2.
 */
double calculateTrafficDensity(double spectralEfficiency, double cellularDensity, double bandwidth, bool logging=false);

/**
 * @brief Calculate the Coherence Time (Tc).
 *
 * Given the wavelength in meters and the speed of the wireless device in meters per second,
 * this function calculates the Coherence Time (Tc) in seconds.
 *
 * @param wavelength Wavelength in meters.
 * @param speed Speed of the wireless device in meters per second.
 * @param logging Boolean flag to enable or disable logging functionality
 * @return Coherence Time (Tc) in seconds.
 */
double calculateCoherenceTime(double wavelength, double speed, bool logging=false);

/**
 * @brief Calculate the Coherence Bandwidth (Bc).
 *
 * Given the delay spread (Tdel) in seconds, this function calculates the Coherence Bandwidth (Bc) in Hz.
 * The formula used is Bc = 1/Tdel, assuming the delay spread is given in seconds.
 *
 * @param delaySpread Delay spread in seconds.
 * @param logging Boolean flag to enable or disable logging functionality
 * @return Coherence Bandwidth (Bc) in Hz.
 */
double calculateCoherenceBandwidth(double delaySpread, bool logging=false);

/**
 * @brief Calculate the slot size given numerology.
 *
 * @param n Numerology value.
 * @param logging Boolean flag to enable or disable logging functionality
 * @return Slot size in milliseconds.
 */
double calculateSlotSize(int n, bool logging=false);

/**
 * @brief Calculate the number of slots per subframe.
 *
 * A subframe is 1 millisecond long.
 * @param slotSize Slot size in milliseconds.
 * @param logging Boolean flag to enable or disable logging functionality
 * @return Number of slots per subframe.
 */
int calculateNumberOfSlots(double slotSize, bool logging=false);

/**
 * @brief Calculate the Subcarrier Spacing (SCS) given numerology.
 *
 * @param n Numerology value.
 * @param logging Boolean flag to enable or disable logging functionality
 * @return SCS in Hz.
 */
double calculateSCS(int n, bool logging=false);

/**
 * @brief Describe the QAM Modulation Scheme.
 *
 * Given a QAM Modulation Scheme value M, this function calculates and returns the number of bits per QAM symbol (b)
 * and the scaling factor (sf). The formula for b is log2(M), and for sf, it is 2/3 * (M-1).
 * The actual scaling factor for power normalization purposes should be calculated as 1/sqrt(sf),
 * where sf is the scaling factor computed here.
 *
 * @param M Modulation order (e.g., 16, 64, 256 for 16-QAM, 64-QAM, 256-QAM).
 * @param b Reference to a double to store the number of bits per QAM symbol.
 * @param sf Reference to a double to store the scaling factor.
 * @param logging Boolean flag to enable or disable logging functionality
 */
void QamModulationSchemeDescriptor(int M, double& b, double& sf, bool logging=false);

/**
 * @brief Calculate the total large-scale loss in dB.
 *
 * This function computes the total large-scale loss in dB by summing the
 * path loss, shadow fading loss, and O2I loss. All losses should be provided
 * in decibels (dB).
 *
 * @param pathLoss Path loss in dB.
 * @param shadowingLoss Shadowing loss in dB.
 * @param o2iLoss O2I loss in dB.
 * @param logging Boolean flag to enable or disable logging functionality
 * @return Total large-scale loss in dB.
 */
double calculateLargeScaleTotalLoss(double pathLoss, double shadowingLoss, double o2iLoss, bool logging=false);

/**
 * @brief Calculate the transmitted power per layer in dBm.
 *
 * This function computes the transmitted power per layer based on the total trasnmit power
 * and number of spatial layers used.
 * The formula used is:
 * Tx Power per layer (dBm) = Tx Power (dBm) - 10log10(numOfLayers) (dB)
 *
 * @param txPower Total transmitted power in dBm
 * @param numOfLayers Number of spatial layers
 * @param logging Boolean flag to enable or disable logging functionality
 * @return Transmitted power per layer in dBm.
 */
double calculateTransmittedPowerPerLayer(double txPower, int numOfLayers, bool logging=false);

/**
 * @brief Calculate the received power per layer in dBm.
 *
 * This function computes the received power per layer based on the transmitted power per layer,
 * total large-scale losses, and beamforming gain. The formula used is:
 * Rx Power (dBm) = Tx Power (dBm) - Large_Total_Loss (dB) + BF Gain (dB).
 *
 * @param txPowerPerLayer Transmitted power per layer in dBm.
 * @param totalLoss Total large-scale loss in dB.
 * @param bfGain Beamforming gain in dB.
 * @param logging Boolean flag to enable or disable logging functionality
 * @return Received power per layer in dBm.
 */
double calculateReceivedPowerPerLayer(double txPowerPerLayer, double totalLoss, double bfGain, bool logging=false);

/**
 * @brief Calculate the thermal noise power.
 *
 * This function computes the thermal noise power using the formula:
 * Thermal Noise Power (W) = k * T * B,
 * where k (Boltzmann's constant) = 1.38e-23 J/K, T is the temperature in Kelvin,
 * and B is the bandwidth in Hz.
 *
 * @param temperature Temperature in Kelvin.
 * @param bandwidth Bandwidth in Hz.
 * @param logging Boolean flag to enable or disable logging functionality
 * @return Thermal noise power in watts.
 */
double calculateThermalNoisePower(double temperature, double bandwidth, bool logging=false);

/**
 * @brief Convert power from dBm to Watts.
 *
 * This function converts a power value from dBm (decibels relative to 1 milliwatt)
 * to Watts. The conversion formula used is:
 * P(W) = 1mW * 10^(P(dBm)/10),
 * where P(dBm) is the power in dBm.
 *
 * @param dBm Power in dBm.
 * @param logging Boolean flag to enable or disable logging functionality
 * @return Power in Watts.
 */
double dBmToWatts(double dBm, bool logging=false);

/**
 * @brief Convert power from watts to dBm.
 *
 * The conversion formula used is:
 * P(dBm) = 10 * log10(P(W)/0.001),
 * where P(W) is the power in Watts.
 * 
 * @param watts Power level in watts.
 * @param logging Boolean flag to enable or disable logging functionality
 * @return Power level in dBm.
 */
double wattsToDbm(double watts, bool logging=false);

/**
 * @brief Calculate the Signal-to-Noise Ratio (SNR) in linear scale.
 *
 * This function calculates the SNR given the received power in dBm and the thermal noise power in watts.
 * The SNR is calculated in a linear scale, not in dB.
 *
 * @param rxPower_dBm Received power in dBm.
 * @param thermalNoisePower_Watts Thermal noise power in watts.
 * @param logging Boolean flag to enable or disable logging functionality
 * @return SNR in linear scale.
 */
double calculateSNRLinear(double rxPower_dBm, double thermalNoisePower_Watts, bool logging=false);

/**
 * @brief Calculate the spectral efficiency per layer.
 *
 * This function calculates the spectral efficiency per layer using the Shannon-Hartley theorem formula:
 * Spectral Efficiency = log2(1 + SNR(linear)),
 * where SNR(linear) is the signal-to-noise ratio in linear scale.
 *
 * @param snrLinear Signal-to-Noise Ratio in linear scale.
 * @param logging Boolean flag to enable or disable logging functionality
 * @return Spectral efficiency per layer in bits/second/Hz.
 */
double calculateSpectralEfficiencyPerLayer(double snrLinear, bool logging=false);

/**
 * @brief Define a structure to hold CQI table entries.
 */
struct CQIEntry {
    int index;
    const char* modulation;
    int codeRate;
    double intermediateSpectralEfficiency; // Expressed as bits/s/Hz
};

/**
 * @brief Calculate the intermediate spectral efficiency by referring CQI table.
 *
 * This function maps a given spectral efficiency to the closest CQI index in the CQI Table.
 * The spectral efficiency in CQI table corresponding to the chosen CQI index is considered as 
 * the intermediate spectral efficiency.
 *
 * @param spectralEfficiency Spectral efficiency in bits/second/Hz.
 * @param logging Boolean flag to enable or disable logging functionality
 * @return A pair containing CQI Index and intermediate spectral efficiency in bits/second/Hz.
 */
std::pair<int, double> determineIntermediateSpectralEfficiency(double spectralEfficiency, bool logging=false);

/**
 * @brief Define a structure to hold MCS table entries.
 */
struct MCSEntry {
    int index;
    int modulationOrder; // Qm
    const char* modulationScheme;
    double mcsCodeRate; // R
    double maxSpectralEfficiency; // Maximum spectral efficiency supported
};

/**
 * @brief Determine Modulation Order (Qm) and MCS Code Rate (R) from the MCS table.
 *
 * This function searches the MCS table to find the entry that does not exceed the given spectral efficiency.
 * It returns the modulation order and code rate that correspond to the highest feasible spectral efficiency.
 *
 * @param spectralEfficiency The target spectral efficiency.
 * @param logging Boolean flag to enable or disable logging functionality
 * @return A pair containing Modulation Order (Qm) and MCS Code Rate (R).
 */
std::pair<int, double> determineModulationAndCodeRate(double spectralEfficiency, bool logging=false);

/**
 * @brief Calculate the number of REs available for data transfer in a Resource Block.
 *
 * This function computes the number of Resource Elements (REs) available for data
 * within a single Resource Block using the formula:
 * N = NumberOfSubcarriersInPRB * NumberOfSymbolsPerSlot - NumberOfREsForDMRS - overheadConfiguredByHigherLayerParameter Xoh - PDSCH
 *
 * @param numberOfSubcarriers Number of subcarriers in an APRB.
 * @param numberOfSymbols Number of symbols per slot.
 * @param numberOfREsForDMRS Number of REs reserved for DMRS.
 * @param overheadFromHigherLayer Overhead REs configured by higher layer parameters.
 * @param logging Boolean flag to enable or disable logging functionality
 * @return The number of REs available for data.
 */
int calculateAvailableREs(int numberOfSubcarriers, int numberOfSymbols, int numberOfREsForDMRS, int overheadFromHigherLayer, bool logging=false);

/**
 * @brief Calculate the actual number of REs available for data transfer.
 *
 * This function determines the actual number of REs available for data transfer
 * based on the given number of REs available per RB and the number of allocated PRBs.
 * It applies a limit of 156 REs per RB as the maximum RE count that can be assumed by a UE.
 *
 * @param availableREsPerRB Number of REs per RB available for data transfer.
 * @param numberOfAllocatedPRBs Number of allocated PRBs for the UE.
 * @param logging Boolean flag to enable or disable logging functionality
 * @return Actual total number of REs available for data transfer.
 */
int calculateActualAvailableREs(int availableREsPerRB, int numberOfAllocatedPRBs, bool logging=false);

/**
 * @brief Calculate the number of information bits.
 *
 * This function calculates the number of information bits Ninfo that can be
 * transmitted given the total number of REs available, the code rate (R),
 * and the modulation order (Qm). The formula used is:
 * Ninfo = Nre * R * Qm,
 * where R is the codeRate / 1024.
 *
 * @param N Total number of REs available for data transmission.
 * @param codeRate Code rate, provided as per 1024 units (e.g., 711 for a code rate of 711/1024).
 * @param modulationOrder Modulation order (Qm), e.g., 2 for QPSK, 4 for 16QAM, etc.
 * @param logging Boolean flag to enable or disable logging functionality
 * @return The number of information bits Ninfo.
 */
double calculateNumberOfInformationBits(int N, double codeRate, int modulationOrder, bool logging=false);

/**
 * @brief Calculate NinfoPrime based on Ninfo for Transport Block Size (TBS) determination.
 *
 * If Ninfo <= 3824 bits, NinfoPrime is calculated using the formula:
 * NinfoPrime = max(24, 2^n * (Ninfo/2^n))
 * where n = max(3, [log2(Ninfo)] - 6)
 *
 * If Ninfo > 3824 bits, NinfoPrime is calculated using the formula:
 * NinfoPrime = 2^n * round((Ninfo - 24)/2^n)
 * where n = [log2(Ninfo - 24)] - 5
 *
 * @param Ninfo Number of information bits calculated.
 * @param logging Boolean flag to enable or disable logging functionality
 * @return The NinfoPrime value for TBS determination.
 */
int calculateNinfoPrime(double Ninfo, bool logging=false);

/**
 * @brief Find the TBS size for a given NinfoPrime using a predefined TBS table.
 *
 * This function searches the TBS table to find the minimum TBS value that is greater
 * than or equal to NinfoPrime. It returns the TBS value corresponding to that entry.
 *
 * @param NinfoPrime Calculated NinfoPrime value.
 * @param logging Boolean flag to enable or disable logging functionality
 * @return The TBS size that meets or exceeds NinfoPrime.
 */
int findTBSForNinfoPrime(int NinfoPrime, bool logging=false);

/**
 * @brief Calculate the TBS size when Ninfo > 3824 using specified conditions.
 *
 * @param NinfoPrime Calculated NinfoPrime value.
 * @param codeRate Code rate, provided as per 1024 units (e.g., 711 for a code rate of 711/1024).
 * @param logging Boolean flag to enable or disable logging functionality
 * @return The TBS size calculated based on the given conditions.
 */
int calculateTBS(int NinfoPrime, int codeRate, bool logging=false);

/**
 * @brief Calculate total bits per PRB for multiple layers.
 *
 * This function calculates the total bits per PRB across multiple layers by adding
 * TBS size iteratively for each layer.
 *
 * @param numLayers The number of layers.
 * @param tbsSize The TBS size used for each layer.
 * @param logging Boolean flag to enable or disable logging functionality
 * @return Total bits per PRB across all layers.
 */
int calculateTotalBitsPerPrb(int numLayers, int tbsSize, bool logging=false);

/**
 * @brief Calculate the total number of Physical Resource Blocks (PRBs) available.
 *
 * This function determines the total number of PRBs available after accounting for
 * downlink overhead. The formula used is:
 * totalPRBAvailable = prbCount - ceil(prbCount * downlinkOH)
 * By default, the downlink overhead is set to 18% per standard unless specified otherwise.
 *
 * @param prbCount Total number of PRBs initially available.
 * @param downlinkOH Downlink overhead as a fraction of total PRBs (default is 0.18 for 18% overhead).
 * @param logging Boolean flag to enable or disable logging functionality
 * @return Total number of PRBs available after accounting for overhead.
 */
int calculateTotalPRBsAvailable(int prbCount, double downlinkOH = 0.18, bool logging=false);

/**
 * @brief Calculate the total number of bits per slot.
 *
 * This function computes the total bits that can be transmitted in one slot based on the
 * number of bits per PRB and the total available PRBs.
 *
 * @param bitsPerPRB Number of bits per PRB.
 * @param totalPRBAvailable Total number of PRBs available.
 * @param logging Boolean flag to enable or disable logging functionality
 * @return Total number of bits per slot.
 */
int calculateBitsPerSlot(int bitsPerPRB, int totalPRBAvailable, bool logging=false);

/**
 * @brief Calculate Downlink Application Throughput.
 *
 * This function computes the Downlink Application Throughput based on the DL MAC Throughput and
 * the ratio of application packet size to MAC packet size. The DL MAC Throughput is given by:
 * DL MAC Throughput = (bitsPerSlot * DL Fraction) / slot time
 *
 * @param bitsPerSlot Number of bits per slot.
 * @param dlFraction Fraction of downlink time usage.
 * @param slotTime Duration of a slot in seconds.
 * @param appPacketSize Application layer packet size in bits.
 * @param macPacketSize MAC layer packet size in bits.
 * @param logging Boolean flag to enable or disable logging functionality
 * @return Downlink Application Throughput in bits per second.
 */
double calculateDLApplicationThroughput(int bitsPerSlot, double dlFraction, double slotTime, int appPacketSize, int macPacketSize, bool logging=false);

/**
 * @brief Parse a DL:UL ratio string and compute the DL fraction.
 *
 * @param ratioStr The DL:UL ratio as a string, e.g., "4:1".
 * @param logging Boolean flag to enable or disable logging functionality
 * @return The DL fraction as a double.
 */
double calculateDLFraction(const std::string& ratioStr, bool logging=false);

/**
 * @brief Calculate the 5G path loss based on the given parameters, using LOS path loss as baseline for NLOS comparison.
 *
 * @param gNBAntennaHeight Height of the gNB antenna in meters.
 * @param ueHeight Height of the UE in meters.
 * @param fLow Lower frequency in MHz.
 * @param fHigh Higher frequency in MHz.
 * @param distance2D Horizontal distance between gNB and UE in meters.
 * @param buildingHeight Height of the building in meters (for NLOS scenarios).
 * @param streetWidth Width of the street in meters (for NLOS scenarios).
 * @param isLOS Boolean indicating if the scenario is Line of Sight.
 * @param logging Boolean flag to enable or disable logging functionality
 * @return Calculated path loss in dB.
 */
double calculate5GPathLossRural(double gNBAntennaHeight, double ueHeight, double fLow, double fHigh, double distance2D, 
                           double buildingHeight, double streetWidth, bool isLOS, bool logging=false);
                           
#endif // UTILITIES_H