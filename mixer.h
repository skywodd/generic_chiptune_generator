/**
 * @file mixer.h
 * @brief Generic digital chiptune generator - Sound channel mixer
 * @author SkyWodd
 * @version 1.0
 * @see http://skyduino.wordpress.com/
 *
 * @section intro_sec Introduction
 * This functions bundle handle all stuff related to channels mixing.\n
 * My implementation of sound mixing is based on signed values addition with scaling.\n
 * For platform with unsigned sound output the scaling function can be truncated to unsigned output.\n
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

#ifndef _MIXER_H_
#define _MIXER_H_

/**
 * Channel structure
 */
typedef struct {
	Oscillator_t oscillator;
	Envelope_t envelope;
	uint8_t volume;
} Channel_t;

/**
 * Mixer structure
 */
typedef struct {
	Channel_t channels[NUMBERS_OF_CHANNEL];
	uint8_t global_volume;
} Mixer_t;

/**
 * Channel enumeration
 */
typedef enum {
  CHANNEL_1,
  CHANNEL_2,
  CHANNEL_3,
  CHANNEL_4,
  CHANNEL_5,
  CHANNEL_6,
  CHANNEL_7,
  CHANNEL_8,
  CHANNEL_9,
  CHANNEL_10,
  CHANNEL_11,
  CHANNEL_12,
  CHANNEL_13,
  CHANNEL_14,
  CHANNEL_15,
  CHANNEL_16
} Channel_name_t;

/**
 * Mixer object
 */
extern volatile Mixer_t mixer;

/**
 * Scale value according to another one
 *
 * @param value Value to scale
 * @param scale Scaling value
 * @return Scaled value
 * @remarks Undefine SCALE_WITH_AUTO_OFFSET to truncate the ouput to unsigned value
 */
inline uint8_t scale_value(uint16_t value, uint16_t scale) {
#ifdef SCALE_WITH_AUTO_OFFSET
	if(value == 0)
		return 0;
	if(scale == 0)
		return value / 2;
	uint8_t new_value = ((value * scale) >> 8) + 1;
	return new_value + ((value - new_value) / 2);
#else
	if(value == 0 || scale == 0)
		return 0;
	return ((value * scale) >> 8) + 1;
#endif
}

/**
 * Reset mixer
 */
void mixer_reset(void);

/**
 * Set waveform of specified channel
 *
 * @param channel Channel to set
 * @param waveform Waveform to set
 */
inline void mixer_set_wave(uint8_t channel, uint8_t waveform) {
	mixer.channels[channel].oscillator.waveform = waveform;
}

/**
 * Set volume of specified channel
 *
 * @param channel Channel to set
 * @param volume Volume to set
 */
inline void mixer_set_volume(uint8_t channel, uint8_t volume) {
	mixer.channels[channel].volume = volume;
}

/**
 * Set global volume of mixer
 *
 * @param volume Volume to set
 */
inline void mixer_set_global_volume(uint8_t volume) {
	mixer.global_volume = volume;
}

/**
 * Start note ON event on specified channel
 *
 * @param channel Channel to set
 * @param frequency Frequency of note ON event
 */
inline void mixer_note_on(uint8_t channel, uint8_t frequency) {
	set_oscillator_tunning_word(&(mixer.channels[channel].oscillator), frequency);
	reset_envelope(&(mixer.channels[channel].envelope), ENV_ATTACK);
}

/**
 * Start note OFF on specified channel
 *
 * @param channel Channel to set
 */
inline void mixer_note_off(uint8_t channel) {
	if (mixer.channels[channel].envelope.type == ADSR_NONE) {
		set_oscillator_tunning_word(&(mixer.channels[channel].oscillator), 0);
	} else {
		reset_envelope(&(mixer.channels[channel].envelope), ENV_RELEASE);
	}
}

/**
 * Sync two channels
 *
 * @param channel_1 Channel to sync
 * @param channel_2 Channel to sync with
 */
inline void mixer_sync_oscillators(uint8_t channel_1, uint8_t channel_2) {
	mixer.channels[channel_1].oscillator.phase_accumulator = mixer.channels[channel_2].oscillator.phase_accumulator;
}

/**
 * Reset oscillator of specified channel
 *
 * @param channel Channel of oscillator to reset
 */
inline void mixer_reset_oscillator(uint8_t channel) {
	mixer.channels[channel].oscillator.phase_accumulator = 0;
}

/**
 * Set ADSR envelope of specified channel
 *
 * @param channel Channel to set
 * @param envelope Envelope to set
 */
inline void mixer_set_adsr(uint8_t channel, uint8_t envelope) {
	if (envelope > NUMBERS_OF_CHANNEL + 1)
		return;
	mixer.channels[channel].envelope.type = envelope;
	reset_envelope(&(mixer.channels[channel].envelope), ENV_ATTACK);
	mixer.channels[channel].envelope.ended = 1;
}

/**
 * Set duty of oscillator of specified channel
 *
 * @param channel Channel of oscillator to set
 * @param duty Duty value to set
 */
inline void mixer_set_duty(uint8_t channel, uint8_t duty) {
	mixer.channels[channel].oscillator.duty = duty;
}


#endif // _MIXER_H_
