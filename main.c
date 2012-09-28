/**
 * @file main.c
 * @brief Generic digital chiptune generator written in C
 * @mainpage 
 * @author SkyWodd
 * @version 1.0
 * @see http://skyduino.wordpress.com/
 *
 * @section intro_sec Introduction
 * This program is a generic implementation of digital chiptune generation.\n
 * This program internaly use a DDS generator with user-defined ADSR envelope.\n
 * \n
 * Please report bug to <skywodd at gmail.com>
 *
 * @note For more details about DDS synthesis theory :
 * @see http://www.analog.com/library/analogdialogue/archives/38-08/dds.html
 *
 * @note For more details about ADSR envelope theory :
 * @see http://en.wikipedia.org/wiki/ADSR_envelope#ADSR_envelope
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
 *
 * @remarks Edit port.c and port.h to make this program work on your platform !
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

#ifdef EMULATE_TIMER
extern TIMER_ISR_FUNCTION;
#endif

/* Program entry point */
int main(void) {

	/* System and DAC initialization */
	system_init();
	reset_tracker();

	/* Mixer initialization */
	mixer_reset();

	/* Sampling timer initialization */
	timer_init(SAMPLE_RATE);

	/* Infinite loop */
	tracker_fetch_execute();
	for (;;) {
#ifdef EMULATE_TIMER
		sampling_fnct();
#endif
	}

	return 0;
}
