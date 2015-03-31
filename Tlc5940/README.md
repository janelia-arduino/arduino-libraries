Tlc5940
=======

Authors:

    Alex Leone <acleone@gmail.com>

License:

    GNU GPL v3


[Usage Examples](./examples)

Code Source
-----------

<https://code.google.com/p/tlc5940arduino/>

Description
-----------

The Texas Instruments TLC5940 is a 16-channel, constant-current sink
LED driver. Each channel has an individually adjustable 4096-step
grayscale PWM brightness control and a 64-step, constant-current sink
(no LED resistors needed!). This chip is a current sink, so be sure to
use common anode RGB LEDs.

Check the tlc5940arduino project on Google Code for updates. To
install, unzip the "Tlc5940" folder to <Arduino
Folder>/hardware/libraries/

Hardware Setup
--------------

The basic hardware setup is explained at the top of the Examples. A
good place to start would be the BasicUse Example. (The examples are
in File->Sketchbook->Examples->Library-Tlc5940).

All the options for the library are located in tlc_config.h, including
NUM_TLCS, what pins to use, and the PWM period. After changing
tlc_config.h, be sure to delete the Tlc5940.o file in the library
folder to save the changes.

Library Reference
-----------------

Core Functions (see the BasicUse Example and Tlc5940):

```cpp
Tlc.init(int initialValue (0-4095)) - Call this is to setup the timers before using any other Tlc functions. initialValue defaults to zero (all channels off).
Tlc.clear() - Turns off all channels (Needs Tlc.update())
Tlc.set(uint8_t channel (0-(NUM_TLCS * 16 - 1)), int value (0-4095)) - sets the grayscale data for channel. (Needs Tlc.update())
Tlc.setAll(int value(0-4095)) - sets all channels to value. (Needs Tlc.update())
uint16_t Tlc.get(uint8_t channel) - returns the grayscale data for channel (see set).
Tlc.update() - Sends the changes from any Tlc.clear's, Tlc.set's, or Tlc.setAll's.
```

Extended Functions. These require an include statement at the top of the sketch to use.

Functions that require VPRG_ENABLED. These require VPRG_ENABLED == 1 in tlc_config.h

Arduino Mega Hardware Setup
---------------------------

Required Pins

    Mega pin 51 (MOSI) -> SIN (Tlc pin 26)
    Mega pin 52 (SCK) -> SCLK (Tlc pin 25)
    Mega pin 11 (OC1A) -> XLAT (Tlc pin 24)
    Mega pin 12 (OC1B) -> BLANK (Tlc pin 23)
    Mega pin 9 (OC2B) -> GSCLK (Tlc pin 18)

Optional Pins

VPRG - for setting dot correction (per-channel current adjustment)

    Mega pin 50 -> VPRG (Tlc pin 27)

XERR - for checking for thermal overloads or disconnected LEDs

    Mega pin 10 -> XERR (Tlc pin 16)
