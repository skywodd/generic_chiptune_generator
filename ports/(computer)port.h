/**
 * @file port.h
 * @brief Computer port of generic chiptune generator
 * @author SkyWodd
 * @version 1.0
 * @see http://skyduino.wordpress.com/
 *
 * @section intro_sec Introduction
 * This port is for windows computer only.\n
 * Output sound is redirected to a raw (8bits, unsigned value) music file named "output.raw".\n
 * Use music editor like audacity to import the output file.\n
 * \n
 * Please report bug to <skywodd at gmail.com>
 * @note With just a little modification of dependencies this port can run smoothly on linux and mac 
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
#include <windows.h> // For exit code
#include <stdio.h>   // For file I/O
FILE *fo_ptr;

/**
 * PROGMEM macro
 */
#define PROGMEM 

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
#define TIMER_ISR_FUNCTION void sampling_fnct(void)

/**
 * System init function 
 */
static inline void system_init(void) {
	fo_ptr = fopen("output.raw", "wb");
	if(!fo_ptr) {
		printf("Unable to open file!");
		exit(1);
	}
}

/** 
 * Timer init function 
 *
 * @param sample_rate Sampling rate frequency of output sound
 */
static inline void timer_init(uint32_t sample_rate) {
	setvbuf(stdout, NULL, _IONBF, 0); // Eclipse CDT for windows bug-fix
	setvbuf(stderr, NULL, _IONBF, 0);
}

/**
 * Re-arm sampling timer function 
 */
static inline void rearm_sampling_timer(void) {

}

/**
 * Output sample to speaker
 *
 * @param sample Output sample to send to speaker
 */
static inline void output_sample_dac(uint8_t sample) {
	fwrite(&sample, 1, 1, fo_ptr);
}

/**
 * Stop timer and dac function 
 */
static inline void stop_timer_dac(void) {
	fclose(fo_ptr);
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
