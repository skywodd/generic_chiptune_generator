# Generic digital chiptune generator written in C
## by SkyWodd

This program is a generic implementation of digital chiptune generation.
This program internaly use a DDS generator with user-defined ADSR envelope.

Each oscillator can generate one of this 6 waveforms :
* No signal (yes it's a waveform)
* Sinus
* Triangle
* Square (with user-defined duty)
* Sawtooth
* Pseudo noise
(You can also generate DC signal, but it's only usefull for ADSR debug purpose)

Tracker commands are pretty obvious, take a look at file "tracker.h" to get a full list of available commands.

The ADSR generator and oscillator are not perfect.
In fact they are far away from another chiptune generators like the "Hardware Chiptune" project of Linus Akesson.
But it's work so I'm happy ^^

Two examples samples are provided, one with ADSR and another one without ADSR.
Samples are in RAW (8 bits unsigned @8KHz) format.

---

# Compatibility

My chiptune generator is currently ported on the following platform :
* Computer (windows, and with a little modification linux and mac)
* LPC1768 / LPC1769
* AVR ATtiny85 (but be honest, the result is very, very bad)

Two pre-compiled hex file are provided, one for LPC1768 and another one for ATtiny85.
Note: ATtiny85 port require my SoftDAC library for ATtiny mcu.