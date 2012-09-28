/**
 * @file envelope.h
 * @brief Generic digital chiptune generator - Envelope generator
 * @author SkyWodd
 * @version 1.0
 * @see http://skyduino.wordpress.com/
 *
 * @section intro_sec Introduction
 * This function bundle handle ADSR envelope generation.\n
 * ADSR envelope are defined by three time in milliseconds (Attack, Delay, Release) and a Sustain level.\n
 * @remarks My implementation of ADSR envelope is far away from a "perfect" ADSR generator, but work.
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
 
#ifndef _ENVELOPE_H_
#define _ENVELOPE_H_

/**
 * ADSR envelopes
 */
typedef enum {
	ADSR_NONE,
	ADSR_USER_1,
	ADSR_USER_2,
	ADSR_USER_3,
	ADSR_USER_4,
	ADSR_USER_5,
	ADSR_USER_6,
	ADSR_USER_7,
	ADSR_USER_8,
	ADSR_USER_9,
	ADSR_USER_10,
	ADSR_USER_11,
	ADSR_USER_12,
	ADSR_USER_13,
	ADSR_USER_14,
	ADSR_USER_15,
	ADSR_USER_16
} ADSR_envelope_t;

/**
 * ADSR states
 */
typedef enum {
	ENV_ATTACK, 
	ENV_DECAY, 
	ENV_SUSTAIN, 
	ENV_RELEASE
} ADSR_state_t;

/**
 * ADSR envelope component structure
 */
typedef struct {
	uint16_t attack;
	uint16_t decay;
	uint8_t sustain_level;
	uint16_t release;
} Envelope_type_t;

/**
 * ADSR envelope structure
 */
typedef struct {
	uint8_t type;
	uint8_t state;
	uint8_t ended;
	uint8_t value;
	SubTimer_t value_change_timer;
} Envelope_t;

/**
 * Reset ADSR envelope
 *
 * @param envelope Pointer to an Envelope_t object
 * @param state New state of envelope to set
 */
void reset_envelope(volatile Envelope_t *envelope, uint8_t state);

/**
 * Get a sample from ADSR envelope
 *
 * @param envelope Pointer to an Envelope_t object
 * @return Envelope sample
 */
uint8_t get_envelope_sample(volatile Envelope_t *envelope);

/**
 * Setup ADSR envelope
 *
 * @param envelope Envelope index
 * @param attack Attack time in ms
 * @param decay Decay time in ms
 * @param sustain_level Sustain volume level
 * @param release Release time in ms
 */
void setup_adsr_envelope(uint8_t envelope, uint16_t attack, uint16_t decay, uint8_t sustain_level, uint16_t release);

#endif // _ENVELOPE_H_
