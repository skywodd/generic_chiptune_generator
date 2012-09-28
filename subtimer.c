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

uint8_t subtimer_tick(volatile SubTimer_t *timer) {

	/* Check for match compare */
	if (timer->tick_counter >= timer->tick_compare) {

		/* Reset SubTimer */
		timer->tick_counter = 0;
		
		/* Notice parent function of event */
		return 1;
		
	} else {

		/* Increment SubTimer */
		++(timer->tick_counter);
		
		/* Notice parent function of no event */
		return 0;
	}
}

uint8_t subtimer_tick_increment(volatile SubTimer_t *timer, uint16_t increment) {

	/* Check for match compare */
	if (timer->tick_counter >= timer->tick_compare) {

		/* Reset SubTimer */
		timer->tick_counter = 0;

		/* Notice parent function of event */
		return 1;

	} else {

		/* Increment SubTimer */
		timer->tick_counter += increment;

		/* Notice parent function of no event */
		return 0;
	}
}
