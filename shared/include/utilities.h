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

/**
 * Calculates the wavelength of a signal given its frequency.
 * 
 * @param frequency Frequency of the signal in hertz (Hz).
 * @return Wavelength in meters (m).
 */
double calculateWavelength(double frequency);

/**
 * @brief Calculate the frequency from wavelength.
 *
 * Given the wavelength in meters, this function calculates the frequency in Hz
 * using the speed of light (c).
 *
 * @param wavelength The wavelength in meters.
 * @return The frequency in Hz.
 */
double calculateFrequencyFromWavelength(double wavelength);

/**
 * Calculates Shannon's Capacity given bandwidth and signal-to-noise ratio.
 * 
 * @param bandwidth The bandwidth in hertz (Hz).
 * @param snr The signal-to-noise ratio (dimensionless).
 * @return Shannon's Capacity in bits per second (bps).
 */
double calculateShannonsCapacity(double bandwidth, double snr);

/**
 * @brief Calculate the OFDM symbol duration.
 *
 * This function takes the subcarrier spacing (SCS) in Hz and
 * calculates the Orthogonal Frequency-Division Multiplexing (OFDM)
 * symbol duration in microseconds.
 *
 * @param scs Subcarrier spacing in Hz.
 * @return OFDM symbol duration in microseconds.
 */
double calculateOFDMSymbolDuration(double scs);

/**
 * @brief Calculate the number of subcarriers (Nsc).
 *
 * Given the bandwidth in Hz and the subcarrier spacing (SCS) in kHz, 
 * this function calculates and returns the number of subcarriers.
 *
 * @param bandwidth The system bandwidth in Hz.
 * @param scs Subcarrier spacing in kHz.
 * @return The number of subcarriers (Nsc).
 */
int calculateNumberOfSubcarriers(double bandwidth, double scs);

/**
 * @brief Calculate the FFT size.
 *
 * Given the OFDM symbol duration in seconds and the sampling frequency in Hz,
 * this function calculates and returns the FFT size.
 *
 * @param symbolDuration OFDM symbol duration in seconds.
 * @param samplingFreq Sampling frequency in Hz.
 * @return The FFT size.
 */
int calculateFFTSize(double symbolDuration, double samplingFreq);

/**
 * @brief Calculate the traffic density GkM.
 *
 * Given the spectral efficiency, cellular density, and bandwidth, this function calculates
 * the traffic density (GkM).
 *
 * @param spectralEfficiency Spectral efficiency in bits/second/Hz/cell.
 * @param cellularDensity Cellular density in cells per square kilometer.
 * @param bandwidth Bandwidth in Hz.
 * @return Traffic density (GkM) in bits/second/km^2.
 */
double calculateTrafficDensity(double spectralEfficiency, double cellularDensity, double bandwidth);

/**
 * @brief Calculate the Coherence Time (Tc).
 *
 * Given the wavelength in meters and the speed of the wireless device in meters per second,
 * this function calculates the Coherence Time (Tc) in seconds.
 *
 * @param wavelength Wavelength in meters.
 * @param speed Speed of the wireless device in meters per second.
 * @return Coherence Time (Tc) in seconds.
 */
double calculateCoherenceTime(double wavelength, double speed);

/**
 * @brief Calculate the Coherence Bandwidth (Bc).
 *
 * Given the delay spread (Tdel) in seconds, this function calculates the Coherence Bandwidth (Bc) in Hz.
 * The formula used is Bc = 1/Tdel, assuming the delay spread is given in seconds.
 *
 * @param delaySpread Delay spread in seconds.
 * @return Coherence Bandwidth (Bc) in Hz.
 */
double calculateCoherenceBandwidth(double delaySpread);

/**
 * @brief Calculate the slot size given numerology.
 *
 * @param n Numerology value.
 * @return Slot size in milliseconds.
 */
double calculateSlotSize(int n);

/**
 * @brief Calculate the number of slots per subframe.
 *
 * A subframe is 1 millisecond long.
 * @param slotSize Slot size in milliseconds.
 * @return Number of slots per subframe.
 */
int calculateNumberOfSlots(double slotSize);

/**
 * @brief Calculate the Subcarrier Spacing (SCS) given numerology.
 *
 * @param n Numerology value.
 * @return SCS in Hz.
 */
double calculateSCS(int n);

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
 */
void QamModulationSchemeDescriptor(int M, double& b, double& sf);

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
 * @return Total large-scale loss in dB.
 */
double calculateLargeScaleTotalLoss(double pathLoss, double shadowingLoss, double o2iLoss);

/**
 * @brief Calculate the received power per layer in dBm.
 *
 * This function computes the received power per layer based on the transmitted power per layer,
 * total large-scale losses, and beamforming gain. The formula used is:
 * Rx Power (dBm) = Tx Power (dBm) - Large_Total_Loss (dB) + BF Gain (dB).
 *
 * @param txPower Transmitted power per layer in dBm.
 * @param totalLoss Total large-scale loss in dB.
 * @param bfGain Beamforming gain in dB.
 * @return Received power per layer in dBm.
 */
double calculateReceivedPowerPerLayer(double txPower, double totalLoss, double bfGain);

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
 * @return Thermal noise power in watts.
 */
double calculateThermalNoisePower(double temperature, double bandwidth);

/**
 * @brief Convert power from dBm to Watts.
 *
 * This function converts a power value from dBm (decibels relative to 1 milliwatt)
 * to Watts. The conversion formula used is:
 * P(W) = 1mW * 10^(P(dBm)/10),
 * where P(dBm) is the power in dBm.
 *
 * @param dBm Power in dBm.
 * @return Power in Watts.
 */
double dBmToWatts(double dBm);

/**
 * @brief Calculate the Signal-to-Noise Ratio (SNR) in linear scale.
 *
 * This function calculates the SNR given the received power in dBm and the thermal noise power in watts.
 * The SNR is calculated in a linear scale, not in dB.
 *
 * @param rxPower_dBm Received power in dBm.
 * @param thermalNoisePower_Watts Thermal noise power in watts.
 * @return SNR in linear scale.
 */
double calculateSNRLinear(double rxPower_dBm, double thermalNoisePower_Watts);

/**
 * @brief Calculate the spectral efficiency per layer.
 *
 * This function calculates the spectral efficiency per layer using the Shannon-Hartley theorem formula:
 * Spectral Efficiency = log2(1 + SNR(linear)),
 * where SNR(linear) is the signal-to-noise ratio in linear scale.
 *
 * @param snrLinear Signal-to-Noise Ratio in linear scale.
 * @return Spectral efficiency per layer in bits/second/Hz.
 */
double calculateSpectralEfficiencyPerLayer(double snrLinear);

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
 * @return intermediate spectral efficiency in bits/second/Hz.
 */
double determineIntermediateSpectralEfficiency(double spectralEfficiency);

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
 * @return A pair containing Modulation Order (Qm) and MCS Code Rate (R).
 */
std::pair<int, double> determineModulationAndCodeRate(double spectralEfficiency);

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
 * @return The number of REs available for data.
 */
int calculateAvailableREs(int numberOfSubcarriers, int numberOfSymbols, int numberOfREsForDMRS, int overheadFromHigherLayer);

/**
 * @brief Calculate the actual number of REs available for data transfer.
 *
 * This function determines the actual number of REs available for data transfer
 * based on the given number of REs available per RB and the number of allocated PRBs.
 * It applies a limit of 156 REs per RB as the maximum RE count that can be assumed by a UE.
 *
 * @param availableREsPerRB Number of REs per RB available for data transfer.
 * @param numberOfAllocatedPRBs Number of allocated PRBs for the UE.
 * @return Actual total number of REs available for data transfer.
 */
int calculateActualAvailableREs(int availableREsPerRB, int numberOfAllocatedPRBs);

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
 * @return The number of information bits Ninfo.
 */
int calculateNumberOfInformationBits(int N, double codeRate, int modulationOrder);

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
 * @param Ninfo Number of information bits calculated previously.
 * @return The NinfoPrime value for TBS determination.
 */
int calculateNinfoPrime(int Ninfo);

/**
 * @brief Define a structure to hold TBS table entries.
 */
struct TBSEntry {
    int index;
    int TBS;
};

/**
 * @brief Find the TBS size for a given NinfoPrime using a predefined TBS table.
 *
 * This function searches the TBS table to find the minimum TBS value that is greater
 * than or equal to NinfoPrime. It returns the TBS value corresponding to that entry.
 *
 * @param NinfoPrime Calculated NinfoPrime value.
 * @return The TBS size that meets or exceeds NinfoPrime.
 */
int findTBSForNinfoPrime(int NinfoPrime);

/**
 * @brief Calculate the TBS size when Ninfo > 3824 using specified conditions.
 *
 * @param NinfoPrime Calculated NinfoPrime value.
 * @param codeRate Code rate, provided as per 1024 units (e.g., 711 for a code rate of 711/1024).
 * @return The TBS size calculated based on the given conditions.
 */
int calculateTBS(int NinfoPrime, int codeRate);

#endif // UTILITIES_H