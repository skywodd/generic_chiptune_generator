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

/* Sinus waveform */
static const uint8_t wave_sinus[256] PROGMEM = { 127, 130, 133, 136, 139, 143,
		146, 149, 152, 155, 158, 161, 164, 167, 170, 173, 176, 179, 181, 184,
		187, 190, 193, 195, 198, 200, 203, 205, 208, 210, 213, 215, 217, 219,
		221, 223, 225, 227, 229, 231, 233, 235, 236, 238, 239, 241, 242, 243,
		245, 246, 247, 248, 249, 250, 250, 251, 252, 252, 253, 253, 253, 254,
		254, 254, 254, 254, 254, 254, 253, 253, 252, 252, 251, 251, 250, 249,
		248, 247, 246, 245, 244, 243, 241, 240, 239, 237, 235, 234, 232, 230,
		228, 226, 224, 222, 220, 218, 216, 214, 211, 209, 207, 204, 202, 199,
		196, 194, 191, 188, 186, 183, 180, 177, 174, 171, 168, 166, 163, 159,
		156, 153, 150, 147, 144, 141, 138, 135, 132, 129, 125, 122, 119, 116,
		113, 110, 107, 104, 101, 98, 95, 91, 88, 86, 83, 80, 77, 74, 71, 68,
		66, 63, 60, 58, 55, 52, 50, 47, 45, 43, 40, 38, 36, 34, 32, 30, 28, 26,
		24, 22, 20, 19, 17, 15, 14, 13, 11, 10, 9, 8, 7, 6, 5, 4, 3, 3, 2, 2,
		1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 2, 2, 3, 4, 4, 5, 6, 7, 8, 9, 11,
		12, 13, 15, 16, 18, 19, 21, 23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 44,
		46, 49, 51, 54, 56, 59, 61, 64, 67, 70, 73, 75, 78, 81, 84, 87, 90, 93,
		96, 99, 102, 105, 108, 111, 115, 118, 121, 124, 126
};

/* Noise seed */
volatile uint32_t noise_seed = 0xB16B00B5;

uint8_t get_waveform_sample(volatile Oscillator_t *oscillator) {

	/* Compute noise */
	noise_seed ^= (noise_seed << 13);
	noise_seed ^= (noise_seed >> 17);
	noise_seed ^= (noise_seed << 5);

	/* For Sawtooth */
	uint16_t tmp;

	/* Switch according oscillator waveform */
	switch (oscillator->waveform) {
	case WF_NONE: // No output
		break;

	case WF_SINUS: // Sinus wave
		return pgm_read_byte(wave_sinus + oscillator->phase_accumulator);
		break;

	case WF_TRIANGLE: // Triangle wave
		if (oscillator->phase_accumulator < 64) {
			tmp = 127 - (oscillator->phase_accumulator * 2);
		} else if (oscillator->phase_accumulator < 192) {
			tmp = (oscillator->phase_accumulator - 64) * 2;
		} else {
			tmp = 255 - ((oscillator->phase_accumulator - 192) * 2);
		}
		return tmp;
		break;

	case WF_SQUARE: // Square wave
		return (oscillator->phase_accumulator > oscillator->duty) ? 0 : 0xFF;
		break;

	case WF_SAWTOOTH: // Sawtooth wave
		tmp = oscillator->phase_accumulator + 127;
		return tmp % 256;
		break;

	case WF_NOISE: // Pseudo noise
		return noise_seed;
		break;

	case WF_DC: // Lineary value
		return oscillator->duty;
		break;
	}
	
	return 127; // WF_NONE
}

void prepare_next_sample(volatile Oscillator_t *oscillator) {
	uint16_t next_phase = oscillator->phase_accumulator + oscillator->tunning_word;
	next_phase %= 256;
	oscillator->phase_accumulator = next_phase;
}
