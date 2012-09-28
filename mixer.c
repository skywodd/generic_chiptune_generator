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

/* Mixer object */
volatile Mixer_t mixer;

inline int16_t map_sample(int16_t x, int16_t in_min, int16_t in_max, int16_t out_min, int16_t out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/* Sampling ISR */
TIMER_ISR_FUNCTION {

	/* Re-arm sampling timer */
	rearm_sampling_timer();

	/* Handle SubTimer (for tempo) */
	tracker_tempo_tick();

	/* Final output sample (signed) */
	int16_t sample = 0;

	/* For each channels of mixer */
	for (uint8_t channel = 0; channel < NUMBERS_OF_CHANNEL; ++channel) {

		/* Get sample from waveform */
		uint8_t value = get_waveform_sample(&(mixer.channels[channel].oscillator));
		prepare_next_sample(&(mixer.channels[channel].oscillator));

		/* Get envelope sample from ADSR */
		uint8_t adsr = get_envelope_sample(&(mixer.channels[channel].envelope));

		/* Scale the value according the ADSR volume */
		value = scale_value(value, adsr);

		/* Scale the value according the channel volume */
		value = scale_value(value, mixer.channels[channel].volume);

		/* Mix channel value and output sample */
		sample += (int16_t)value - 127; // Remove DC offset
	}

	/* Avoid clipping by mapping sample output */
	sample = map_sample(sample, NUMBERS_OF_CHANNEL * -127, NUMBERS_OF_CHANNEL * 127, 0, 255);
	if(sample > 255) sample = 255;
	if(sample < 0) sample = 0;

	/* Scale the sample according the global mixer volume */
	sample = scale_value(sample, mixer.global_volume);

	/* Output sample */
	output_sample_dac(sample);
}

void mixer_reset(void) {

	/* Reset global volume */
	mixer.global_volume = 0;

	/* For each channels of mixer */
	for (uint8_t channel = 0; channel < NUMBERS_OF_CHANNEL; ++channel) {

		/* Reset channel and oscillator */
		mixer.channels[channel].volume = 0;
		
		mixer.channels[channel].envelope.type = ADSR_NONE;
		reset_envelope(&(mixer.channels[channel].envelope), ENV_ATTACK);
		mixer.channels[channel].envelope.ended = 1;
		
		mixer.channels[channel].oscillator.waveform = WF_NONE;
		mixer.channels[channel].oscillator.duty = 127;
		mixer.channels[channel].oscillator.tunning_word = 0;
		mixer.channels[channel].oscillator.phase_accumulator = 0;
	}
}
