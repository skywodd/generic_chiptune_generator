/**
 * @file port.h
 * @brief LPC1768 port of generic chiptune generator
 * @author SkyWodd
 * @version 1.0
 * @see http://skyduino.wordpress.com/
 *
 * @section intro_sec Introduction
 * This port is for LPC1768/1769 based boards.\n
 * Output sound is redirected to hardware DAC.\n
 * \n
 * Please report bug to <skywodd at gmail.com>
 * @remarks Take a look at common.h header file for runtime configuration
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

#ifndef _PORT_H_
#define _PORT_H_

/* Dependency */
#include <lpc_types.h> // For hardcoded type
#include <LPC17xx.h>   // For everything related to LPC17xx

/**
 * PROGMEM macro
 */
#define PROGMEM __attribute__((section (".USER_FLASH")))

/**
 * Get a byte (8 bits) from PROGMEM function
 *
 * @param address Address of byte in memory
 * @return Byte value
 */
inline uint8_t pgm_read_byte(const uint8_t *address) {
	return *address;
}

/**
 * Get a word (16 bits) from PROGMEM function
 *
 * @param address Address of word in memory
 * @return Word value
 */
inline uint16_t pgm_read_word(const uint8_t *address) {
	return ((uint16_t)(*address) << 8) | *(address + 1);
}

/**
 * 2 bytes value ordering macro
 */
#define value(x) high(x), low(x)

/**
 * Timer handling function name 
 */
#define TIMER_ISR_FUNCTION void RIT_IRQHandler(void)

/**
 * System init function 
 */
static inline void system_init(void) {
	SystemInit();
	SystemCoreClockUpdate();
	LPC_PINCON->PINSEL1 = 0x00200000; // Set p0.26 to DAC output
}

/** 
 * Timer init function 
 *
 * @param sample_rate Sampling rate frequency of output sound
 */
static inline void timer_init(uint32_t sample_rate) {
	/* Set sampling frequency */
	LPC_SC->PCONP |= (1 << 16);
	LPC_RIT->RICTRL &= ~((0x1 << 0) | (0x1 << 1));
	LPC_RIT->RICOMPVAL = (SystemCoreClock / 4) / sample_rate - 1;
	LPC_RIT->RICOUNTER = 0;
	NVIC_EnableIRQ(RIT_IRQn);

	/* Enable Timer */
	LPC_RIT->RICTRL |= ((0x1 << 0) | (0x1 << 1));
	LPC_RIT->RICTRL |= (1 << 1) | (1 << 3); // RIT enable + CTC
}

/**
 * Re-arm sampling timer function 
 */
static inline void rearm_sampling_timer(void) {
	LPC_RIT->RICTRL |= 1;
}

/**
 * Output sample to speaker
 *
 * @param sample Output sample to send to speaker
 */
static inline void output_sample_dac(uint8_t sample) {
	LPC_DAC->DACR = sample << (6 + 2); // 6 for reserved bits section + 2 (8 bits -> 10 bits)
}

/**
 * Stop timer and dac function 
 */
static inline void stop_timer_dac(void) {
	LPC_DAC->DACR = 0;
	LPC_RIT->RICTRL = 0;
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
