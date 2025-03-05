# EEPROMProgammerPCB

This is a simple circuit for programming the 28C16, 28C64, 28C256, and similar parallel EEPROMs using an Arduino. Since the Arduino doesn’t have enough pins to directly control all of the address, data, and control lines of the EEPROM, two 74HC595 serial in parallel out are used for the 13 address lines and the output enable control line.

