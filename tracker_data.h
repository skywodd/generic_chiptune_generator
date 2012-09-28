/**
 * @file tracker_data.h
 * @brief Generic digital chiptune generator - Tracker data file
 * @author SkyWodd
 * @version 1.0
 * @see http://skyduino.wordpress.com/
 *
 * @section intro_sec Introduction
 * This file is the tracker data file. All commands interpreted by chiptune generator are stored here.\n
 * If your port.c use external memory to store tracker data you can delete this file.\n
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

#ifndef _TRACKER_DATA_H_
#define _TRACKER_DATA_H_

/**
 * Music notes (english notation) in General-Midi order
 */
typedef enum {
	NOTE_A0 = 21,
	NOTE_AS0,
	NOTE_B0,
	NOTE_C1,
	NOTE_CS1,
	NOTE_D1,
	NOTE_DS1,
	NOTE_E1,
	NOTE_F1,
	NOTE_FS1,
	NOTE_G1,
	NOTE_GS1,
	NOTE_A1,
	NOTE_AS1,
	NOTE_B1,
	NOTE_C2,
	NOTE_CS2,
	NOTE_D2,
	NOTE_DS2,
	NOTE_E2,
	NOTE_F2,
	NOTE_FS2,
	NOTE_G2,
	NOTE_GS2,
	NOTE_A2,
	NOTE_AS2,
	NOTE_B2,
	NOTE_C3,
	NOTE_CS3,
	NOTE_D3,
	NOTE_DS3,
	NOTE_E3,
	NOTE_F3,
	NOTE_FS3,
	NOTE_G3,
	NOTE_GS3,
	NOTE_A3,
	NOTE_AS3,
	NOTE_B3,
	NOTE_C4,
	NOTE_CS4,
	NOTE_D4,
	NOTE_DS4,
	NOTE_E4,
	NOTE_F4,
	NOTE_FS4,
	NOTE_G4,
	NOTE_GS4,
	NOTE_A4,
	NOTE_AS4,
	NOTE_B4,
	NOTE_C5,
	NOTE_CS5,
	NOTE_D5,
	NOTE_DS5,
	NOTE_E5,
	NOTE_F5,
	NOTE_FS5,
	NOTE_G5,
	NOTE_GS5,
	NOTE_A5,
	NOTE_AS5,
	NOTE_B5,
	NOTE_C6,
	NOTE_CS6,
	NOTE_D6,
	NOTE_DS6,
	NOTE_E6,
	NOTE_F6,
	NOTE_FS6,
	NOTE_G6,
	NOTE_GS6,
	NOTE_A6,
	NOTE_AS6,
	NOTE_B6,
	NOTE_C7,
	NOTE_CS7,
	NOTE_D7,
	NOTE_DS7,
	NOTE_E7,
	NOTE_F7,
	NOTE_FS7,
	NOTE_G7,
	NOTE_GS7,
	NOTE_A7,
	NOTE_AS7,
	NOTE_B7,
	NOTE_C8,
	NOTE_CS8,
	NOTE_D8,
	NOTE_DS8,
	NOTE_E8,
	NOTE_F8,
	NOTE_FS8,
	NOTE_G8,
	NOTE_GS8,
	NOTE_A8,
	NOTE_AS8,
	NOTE_B8,
	NOTE_C9,
	NOTE_CS9,
	NOTE_D9,
	NOTE_DS9,
	NOTE_E9,
	NOTE_F9,
	NOTE_FS9,
	NOTE_G9,
	NOTE_GS9,
	NOTE_A9,
	NOTE_AS9,
	NOTE_B9
} Note_t;

/**
 * Music tracker data
 */
extern const uint8_t tracker_music_opcodes[] PROGMEM;

/**
 * Music tracker data length
 */
extern const uint16_t tracker_music_length;

#endif // _TRACKER_DATA_H_