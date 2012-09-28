/**
 * @file common.h
 * @brief Generic digital chiptune generator - Common configuration file
 * @author SkyWodd
 * @version 1.0
 * @see http://skyduino.wordpress.com/
 *
 * @section intro_sec Introduction
 * This configuration define everything related to chiptune generator and global macro.\n
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

#ifndef _COMMON_H_
#define _COMMON_H_

/**
 * Output sample rate 
 */
#define SAMPLE_RATE 8000UL

/**
 * Number of channels 
 *
 * @warning Be sure you use the same number of channel in you tracker_data file !
 */
#define NUMBERS_OF_CHANNEL 6 //2

/**
 * Runtime configuration (uncomment this define if using a hardware timer)
 */
#define EMULATE_TIMER

/**
 * Output sample scaling configuration (uncomment this define if the sound seem strange (signed / unsigned problems))
 */
#define SCALE_WITH_AUTO_OFFSET

/* ----- General macro, do not edit anything after this line ----- */

/**
 * Convert BPM to Tick compare value (according sample rate frequency)
 */
#define BPM_TO_TICK(bpm) (SAMPLE_RATE / ((bpm) / 60) - 1)

/**
 * Convert Milliseconds to Tick compare value (according sample rate frequency)
 */
#define MS_TO_TICK(ms) (SAMPLE_RATE / (1000UL / (ms)) - 1)

/**
 * Get LSB of 16 bits value
 */
#define low(x) (0x00FF & x)

/**
 * Get MSB of 16 bits value
 */
#define high(x) ((0xFF00 & x) >> 8)

#endif // _COMMON_H_
