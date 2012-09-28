/**
 * @file subtimer.h
 * @brief Generic digital chiptune generator - Software timer library
 * @author SkyWodd
 * @version 1.0
 * @see http://skyduino.wordpress.com/
 *
 * @section intro_sec Introduction
 * This mini library let user create software defined timer.\n
 * The goal of this library is to create as many timer you need with only one hardware base timer.\n
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

#ifndef _SUBTIMER_H_
#define _SUBTIMER_H_

/**
 * SubTimer structure
 */
typedef struct {
	uint32_t tick_compare;
	uint32_t tick_counter;
} SubTimer_t;

/**
 * Reset a SubTimer object
 *
 * @param timer Pointer to a SubTimer_t object
 */
inline void subtimer_reset(volatile SubTimer_t *timer, uint8_t overwrite_all) {
	if(overwrite_all)
		timer->tick_compare = 0;
	timer->tick_counter = 0;
}

/**
 * Set match compare value of a SubTimer object
 *
 * @param timer Pointer to a SubTimer_t object
 * @param compare Timer compare value
 */
inline void subtimer_set_compare(volatile SubTimer_t *timer, uint32_t compare) {
	timer->tick_compare = compare;
	timer->tick_counter = 0;
}

/**
 * Get match compare value of a SubTimer object
 *
 * @param timer Pointer to a SubTimer_t object
 * @return Match compare value of SubTimer object
 */
inline uint32_t subtimer_get_compare(volatile SubTimer_t *timer) {
	return timer->tick_compare;
}

/**
 * Get counter value of a SubTimer object
 *
 * @param timer Pointer to a SubTimer_t object
 * @return Counter value of SubTimer object
 */
inline uint32_t subtimer_get_counter(volatile SubTimer_t *timer) {
	return timer->tick_counter;
}

/**
 * Process tick event of a SubTimer object
 *
 * @param timer Pointer to a SubTimer_t object
 * @return 0 if no event (no compare match), 1 if event (compare match)
 */
uint8_t subtimer_tick(volatile SubTimer_t *timer);

/**
 * Process tick event of a SubTimer object
 *
 * @param timer Pointer to a SubTimer_t object
 * @param increment Increment value (user specified)
 * @return 0 if no event (no compare match), 1 if event (compare match)
 */
uint8_t subtimer_tick_increment(volatile SubTimer_t *timer, uint16_t increment);

#endif // _SUBTIMER_H_


