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

/**
 * ADSR envelopes
 */
volatile Envelope_type_t adsr_envelopes[NUMBERS_OF_CHANNEL] = {
	{ 0, 0, 0, 0 }
};

void reset_envelope(volatile Envelope_t *envelope, uint8_t state) {

	if (envelope->type == ADSR_NONE)
		return;
	
	envelope->state = state;
	if(envelope->ended)
		envelope->value = 0;

	// Note : Use Time x1024 (and Timer +1024 by step) to reduce mathemical error produced by integer division

	switch (state) {
	case ENV_ATTACK:
		subtimer_set_compare(&(envelope->value_change_timer), (adsr_envelopes[envelope->type - 1].attack * 1024) / 255);
	break;

	case ENV_DECAY:
		envelope->value = 255;
		subtimer_set_compare(&(envelope->value_change_timer), (adsr_envelopes[envelope->type - 1].decay * 1024) / 255);
	break;
		
	case ENV_SUSTAIN:
		envelope->value = adsr_envelopes[envelope->type - 1].sustain_level;
		subtimer_set_compare(&(envelope->value_change_timer), (1 << 31));
		break;

	case ENV_RELEASE:
		if(envelope->ended) break;
		envelope->value = adsr_envelopes[envelope->type - 1].sustain_level;
		subtimer_set_compare(&(envelope->value_change_timer), (adsr_envelopes[envelope->type - 1].release * 1024) / 255);
	break;
	}

	envelope->ended = 0;
}

uint8_t get_envelope_sample(volatile Envelope_t *envelope) {

	/* Check for ADSR */
	if (envelope->type == ADSR_NONE)
		return 255;

	/* Check for ended ADSR */
	if (envelope->ended)
		return 0;

	/* Handle SubTimer (for envelope value change) */
	if (subtimer_tick_increment(&(envelope->value_change_timer), 1024)) {

		/* Increment or decrement value */
		if (envelope->state == ENV_ATTACK) {
			if((uint16_t)envelope->value + 1 >= 255) {
				reset_envelope(envelope, ENV_DECAY); // Attack -> Decay
			} else
				++(envelope->value);

		} else if (envelope->state == ENV_DECAY) {
			if((int16_t)envelope->value - 1 <= adsr_envelopes[envelope->type - 1].sustain_level) {
				reset_envelope(envelope, ENV_SUSTAIN); // Decay -> Sustain
			} else
				--(envelope->value);

		} else if (envelope->state == ENV_RELEASE) {
			if((int16_t)envelope->value - 1 <= 0) {
				envelope->ended = 1; // Release -> end
			} else
				--(envelope->value);
		}

	}

	/* Return sample */
	return envelope->value;
}

void setup_adsr_envelope(uint8_t envelope, uint16_t attack, uint16_t decay, uint8_t sustain_level, uint16_t release) {
	if (envelope == ADSR_NONE || envelope > NUMBERS_OF_CHANNEL + 1) { // Overflow check
		return;
	}
	--envelope; // Ignore ADSR_NONE
	adsr_envelopes[envelope].attack	= MS_TO_TICK(attack);
	adsr_envelopes[envelope].decay = MS_TO_TICK(decay);
	adsr_envelopes[envelope].sustain_level = sustain_level;		
	adsr_envelopes[envelope].release = MS_TO_TICK(release);
}
