#ifndef UTILITIES_H
#define UTILITIES_H

/**
 * @file utilities.h
 * @brief Utility functions for telecommunications calculations.
 */

#include <cmath>

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

#endif // UTILITIES_H