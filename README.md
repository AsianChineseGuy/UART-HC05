# Description
Basic UART communication with HC-05 bluetooth module.

## Devices
- MPLABv5.50

- Microchip PIC16F887

- Pickit3

- HC-05 bluetooth module

## What does it do
Receive any length of characters from a serial bluetooth terminal 
Transmits them back using interrupts instead of polling.

## Storing chracters as string
Did not test it out yet but probably the best way is to
use an array to store each bit while incrementing the array.
And check for CR & LF as the end of a word or sentence that
you are sending.
