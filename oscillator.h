/**
 * @file oscillator.h
 * @brief Generic digital chiptune generator - Waveform oscillator
 * @author SkyWodd
 * @version 1.0
 * @see http://skyduino.wordpress.com/
 *
 * @section intro_sec Introduction
 * This functions bundle handle all stuff related to waveform generation.\n
 * \n
 * Please report bug to <skywodd at gmail.com>
 *
 * @section licence_sec Licence
 *  This program is free software: you can redistribute it and/or modify\n
 *  it under the terms of the GNU General Public License as published by\n
 *  the Free Software Foundation, either version 3 of the License, or\n
 *  (at your option) any later version.\n
 * \n
 *  This program is distributed in the hope that it will be useful,\n
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of\n
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n
 *  GNU General Public License for more details.\n
 * \n
 *  You should have received a copy of the GNU General Public License\n
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.\n
 *
 * @section changelog_sec Changelog history
 * - 13/09/2012 : First version
 */

#ifndef _OSCILLATOR_H_
#define _OSCILLATOR_H_

/**
 * Waveforms
 *
 * @remarks WF_DC should be used for debug purpose only
 */
typedef enum {
	WF_NONE, 
	WF_SINUS, 
	WF_TRIANGLE, 
	WF_SQUARE, 
	WF_SAWTOOTH, 
	WF_NOISE, 
	WF_DC
} Waveform_t;

/**
 * Oscillator structure
 */
typedef struct {
	uint8_t waveform;
	uint8_t duty;
	uint8_t tunning_word;
	uint8_t phase_accumulator;
} Oscillator_t;

/**
 * Set oscillator waveform of an Oscillator_t object
 *
 * @param oscillator Pointer to an Oscillator_t object
 * @param waveform Wavefrom to set
 */
inline void set_oscillator_waveform(volatile Oscillator_t *oscillator, uint8_t waveform) {
	oscillator->waveform = waveform;
}

/**
 * Set duty value of an Oscillator_t object
 *
 * @param oscillator Pointer to an Oscillator_t object
 * @param duty Duty value to set (only used for square wave)
 */
inline void set_oscillator_duty(volatile Oscillator_t *oscillator, uint8_t duty) {
	oscillator->duty = duty;
}

/**
 * Set oscillator tunning word of an Oscillator_t object
 *
 * @param oscillator Pointer to an Oscillator_t object
 * @param tunning_word Tunning word to set
 */
inline void set_oscillator_tunning_word(volatile Oscillator_t *oscillator, uint8_t tunning_word) {
	oscillator->tunning_word = tunning_word;
}

/**
 * Get a waveform sample from an Oscillator_t object
 *
 * @param oscillator Pointer to an Oscillator_t object
 * @return Waveform sample
 */
uint8_t get_waveform_sample(volatile Oscillator_t *oscillator);

/**
 * Prepare next sample of an Oscillator_t object
 *
 * @param oscillator Pointer to an Oscillator_t object
 */
void prepare_next_sample(volatile Oscillator_t *oscillator);

#endif // _OSCILLATOR_H_
