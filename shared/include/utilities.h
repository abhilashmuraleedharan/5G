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

#endif // UTILITIES_H