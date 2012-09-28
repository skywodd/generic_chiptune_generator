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
#include <stdint.h>
#include "port.h"
#include "tracker_data.h"

uint8_t get_byte_from_tracker(const uint16_t address) {
	return pgm_read_byte(tracker_music_opcodes + address);
}

uint16_t get_word_from_tracker(const uint16_t address) {
	return pgm_read_word(tracker_music_opcodes + address);
}
