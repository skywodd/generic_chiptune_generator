/**
 * @file tracker.h
 * @brief Generic digital chiptune generator - Tracker file parser
 * @author SkyWodd
 * @version 1.0
 * @see http://skyduino.wordpress.com/
 *
 * @section intro_sec Introduction
 * This functions bundle handle all stuff related to tracker file parsing and interpreting.\n
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
 
#ifndef _TRACKER_H_
#define _TRACKER_H_

/**
 * Tracker opcodes
 */
typedef enum {
	NO_ACTION = 0x00, // No action
	SET_TEMPO = 0x10, // Set tempo <tempo 2 bytes>
	SET_WAVE = 0x20, // Set waveform <waveform 1 byte>
	SET_VOLUME = 0x30, // Set channel volume <volume 1 byte>
	SET_GLOBAL_VOLUME = 0x40, // Set global volume <volume 1 byte>
	NOTE_ON = 0x50, // Note on <note 1 byte>
	NOTE_OFF = 0x60, // Note off
	END_OF_STREAM = 0x70, // End of tracker file
	SOFTWARE_RESET = 0x80, // Software reset of mixer / channels and associated oscillators
	SYNC_OSCILLATOR = 0x90, // Sync channel oscillator <target 1 byte>
	RESET_OSCILLATOR = 0xA0, // Reset oscillator phase to the start point
	SET_ADSR = 0xB0, // Set ADSR envellope of channel <ADSR type 1 byte>
	JUMP_IN_FILE = 0xC0, // Jump somewhere in the tracker file <target 2 bytes>
	SET_DUTY = 0xD0, // Set square wave duty <duty 1 byte>
	DIRECT_EXEC = 0xE0, // Execute n instructions in one step <instruction_count 1 byte>
	SET_ADSR_VALUES = 0xF0
// Set ADSR envelope <Attack in ms 2 bytes> <Decay in ms 2 bytes> <Sustain volume 1 bytes> <Release in ms 2 bytes>
} Tracker_opcode;

/**
 * Reset tracker
 */
void reset_tracker(void);

/**
 * Fetch and execute opcode
 *
 * @return 1 if no more events have to be processed for this timer event, 0 otherwise
 */
uint8_t tracker_fetch_execute(void);

/**
 * Tracker tempo tick
 */
void tracker_tempo_tick(void);

/**
 * Process n opcode(s) (according numbers of channels) from tracker file
 */
void process_tracker_opcode(void);

#endif // _TRACKER_H_
