# EEPROMProgammerPCB

This is a simple circuit for programming the **AT28C64 EEPROM** using an **Arduino Nano**. Since the Arduino doesn't have enough pins to directly control all the data and address pins of the EEPROM, this design utilizes two **74HC595** serial-in parallel-out shift register chips to cummunicate with the EEPROM.

