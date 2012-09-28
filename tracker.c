/*
 * See header file for details
 *
 *  This program is free software: you can redistribute it and/or modify\n
 *  it under the terms of the GNU General Public License as published by\n
 *  the Free Software Foundation, either version 3 of the License, or\n
 *  (at your option) any later version.\n
 * 
 *  This program is distributed in the hope that it will be useful,\n
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of\n
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n
 *  GNU General Public License for more details.\n
 * 
 *  You should have received a copy of the GNU General Public License\n
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.\n
 */

/* Includes */
#include <stdint.h>       // For hardcoded type
#include "common.h"       // For common macro
#include "port.h"         // For platform dependent macro
#include "tracker.h"      // For tracker commands
#include "tracker_data.h" // For english note notation
#include "subtimer.h"     // For SubTimer structure
#include "envelope.h"     // For ADSR envelope name
#include "oscillator.h"   // For Waveform name
#include "mixer.h"        // For channel name

/* Frequency lookup table @8KHz */
static const uint8_t frequency_table[128] PROGMEM = { 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5, 6, 6, 6,
		7, 7, 7, 8, 8, 9, 9, 10, 11, 11, 12, 13, 13, 14, 15, 16, 17, 18, 19,
		20, 21, 22, 24, 25, 27, 28, 30, 32, 34, 35, 38, 40, 42, 45, 47, 50, 53,
		56, 60, 63, 67, 71, 75, 80, 84, 89, 95, 100, 106, 113, 119, 126, 134,
		142, 150, 159, 169, 179, 189, 201, 213, 225, 239, 253, 0, 0, 0, 0, 0,
		0, 0, 0 };

/* Tempo timer */
volatile SubTimer_t tempo_timer = { BPM_TO_TICK(300), 0 };

/* Tracker file index */
uint16_t tracker_index = 0;

/* Reset tracker */
void reset_tracker(void) {
	tracker_index = 0;
	subtimer_reset(&tempo_timer, 0);
}

uint8_t tracker_fetch_execute(void) {
	/* Fetch an byte from music file */
	uint8_t command = get_byte_from_tracker(tracker_index++);
	uint8_t channel = command & 0x0F;

	/* Interpret opcode */
	switch (command & 0xF0) {
	case NO_ACTION: // No action
		break;

	case SET_TEMPO: // Set tempo <tempo 2 bytes>
		subtimer_set_compare(
				&tempo_timer,
				BPM_TO_TICK(get_word_from_tracker(tracker_index)));
		tracker_index += 2;
		break;

	case SET_WAVE: // Set waveform <waveform 1 byte>
		mixer_set_wave(channel, get_byte_from_tracker(tracker_index++));
		break;

	case SET_VOLUME: // Set channel volume <volume 1 byte>
		mixer_set_volume(channel, get_byte_from_tracker(tracker_index++));
		break;

	case SET_GLOBAL_VOLUME: // Set global volume <volume 1 byte>
		mixer_set_global_volume(get_byte_from_tracker(tracker_index++));
		break;

	case NOTE_ON: // Note on <note 1 byte>
		command = get_byte_from_tracker(tracker_index++) & 127;
		mixer_note_on(channel, pgm_read_byte(frequency_table + command));
		break;

	case NOTE_OFF: // Note off
		mixer_note_off(channel);
		break;

	case END_OF_STREAM: // End of tracker file
		stop_timer_dac();
#ifndef EMULATE_TIMER
		for (;;)
			;
#else
		puts("END OF STREAM\n");
		exit(0);
#endif
		break;

	case SOFTWARE_RESET: // Software reset of mixer / channels and associated oscillators
		mixer_reset();
		break;

	case SYNC_OSCILLATOR: // Sync channel oscillator <target 1 byte>
		mixer_sync_oscillators(channel, get_byte_from_tracker(tracker_index++) & 0x0F);
		break;

	case RESET_OSCILLATOR: // Reset oscillator phase to the start point
		mixer_reset_oscillator(channel);
		break;

	case SET_ADSR: // Set ADSR envelope of channel <ADSR type 1 byte>
		mixer_set_adsr(channel, get_byte_from_tracker(tracker_index++));
		break;

	case JUMP_IN_FILE: // Jump somewhere in the tracker file <target 2 bytes>
		tracker_index = get_word_from_tracker(tracker_index);
		break;

	case SET_DUTY: // Set square wave duty <duty 1 byte>
		mixer_set_duty(channel, get_byte_from_tracker(tracker_index++));
		break;

	case DIRECT_EXEC: // Execute n instructions in one step <instruction_count 1 byte>
		// Re-use command variable to store instruction count to execute
		command = get_byte_from_tracker( tracker_index++);
		for (uint8_t i = 0; i < command; ++i) {
			tracker_fetch_execute();
		}
		return 1;
		break;

	case SET_ADSR_VALUES: // Set ADSR envelope <Attack in ms 2 bytes> <Decay in ms 2 bytes> <Sustain volume 1 bytes> <Release in ms 2 bytes>
	{
		uint16_t attack = get_word_from_tracker(tracker_index);
		tracker_index += 2;
		uint16_t decay = get_word_from_tracker(tracker_index);
		tracker_index += 2;
		uint8_t sustain_level = get_byte_from_tracker(tracker_index++);
		uint16_t release = get_word_from_tracker(tracker_index);
		tracker_index += 2;
		setup_adsr_envelope(channel, attack, decay, sustain_level, release);
	}
		break;
	}
	return 0;
}

void tracker_tempo_tick(void) {
	if (subtimer_tick(&tempo_timer)) {

		/* Handle endless tracker file */
		if (tracker_index >= tracker_music_length)
			tracker_index = 0;

		/* For each channels of mixer */
		for (uint8_t i = 0; i < NUMBERS_OF_CHANNEL; ++i) {
			if (tracker_fetch_execute())
				break;
		}
	}
}
