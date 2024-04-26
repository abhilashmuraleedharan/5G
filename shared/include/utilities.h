#ifndef UTILITIES_H
#define UTILITIES_H

/**
 * @file utilities.h
 * @brief Utility functions for telecommunications calculations.
 */

#include <cmath>
#include <cmath>
#include <iomanip>

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

#endif // UTILITIES_H