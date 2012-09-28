/**
 * LPC_Chiptune - Chiptune for LPC1768/69
 *
 * @author SkyWodd
 * @version 1.0
 * @link http://skyduino.wordpress.com
 *
 * Please report bug to <skywodd at gmail.com>
 */
/**
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _PORT_H_
#define _PORT_H_

/* Dependency */
#include <avr/io.h>        // For registers
#include <avr/pgmspace.h>  // For PROGMEM
#include <avr/interrupt.h> // For interrupts ISR
#include "soft_dac.h"      // For DAC output

/**
 * 2 bytes value ordering macro
 */
#define value(x)  low(x), high(x) // Little-endian

/**
 * Timer handling function name 
 */
#define TIMER_ISR_FUNCTION ISR(TIMER1_COMPA_vect)

/**
 * System init function 
 */
static inline void system_init(void) {
	soft_dac_initialize();
}

/** 
 * Timer init function 
 *
 * @param sample_rate Sampling rate frequency of output sound
 */
static inline void timer_init(uint32_t sample_rate) {
	soft_dac_sampling_frequency(sample_rate);
	soft_dac_start();
}

/**
 * Re-arm sampling timer function 
 */
static inline void rearm_sampling_timer(void) {
	soft_dac_sampling_reset();
}

/**
 * Output sample to speaker
 *
 * @param sample Output sample to send to speaker
 */
static inline void output_sample_dac(uint8_t sample) {
	soft_dac_output(sample);
}

/**
 * Stop timer and dac function 
 */
static inline void stop_timer_dac(void) {
	soft_dac_stop();
}

/* ---------- */

/**
 * Get byte from tracker data
 *
 * @param address Base address of byte
 * @return Byte value from tracker data
 */
uint8_t get_byte_from_tracker(const uint16_t address);

/**
 * Get word from tracker data
 *
 * @param address Base address of word
 * @return Word value from tracker data
 */
uint16_t get_word_from_tracker(const uint16_t address);

#endif // _PORT_H_
