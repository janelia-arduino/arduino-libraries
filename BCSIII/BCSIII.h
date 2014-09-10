// ----------------------------------------------------------------------------
// BSCIII.h
//
// Setup and control code needed for the BCS III
//
// Authors:
// Steve Sawtelle sawtelles@janelia.hhmi.org
// ----------------------------------------------------------------------------

#ifndef BCSIII_H_
#define BCSIII_H_

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <util/atomic.h>


//#define DIN 0x30
//#define AIN 0x10
//#define DOUT 0x20
//#define NC 0x00

#define ANALOG_IN 0x08
#define NO_CONNECT 0x0f
#define NC NO_CONNECT

const uint8_t pin_number[] = {2,3,21,20,5,6,7,46, A8, A9, A10, A11, A12, A13, A14, A15 };
static uint8_t IOpin[]  = {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 };
static uint8_t IOtype[] = { NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC };

class BCSIII
{
public:
  BCSIII(void);
  void begin(void);
  uint8_t getPin(uint8_t BNC);
  uint8_t getType(uint8_t BNC);
  int8_t setIO(uint8_t BNC, uint8_t IO, uint8_t type);

#define SPI1 22
#define SPI2 23
#define SPI3 25
#define SPI4 28
#define SPI5 47
#define SPI6 49

  // errors
#define BAD_BNC -1
#define BAD_PIN -2
#define BAD_TYPE -3
#define BAD_ANALOG -4

  // BNCs
#define BNC1 1
#define BNC2 2
#define BNC3 3
#define BNC4 4
#define BNC5 5
#define BNC6 6
#define BNC7 7
#define BNC8 8
#define BNC9 9
#define BNC10 10
#define BNC11 11
#define BNC12 12
#define BNC13 13
#define BNC14 14
#define BNC15 15
#define BNC16 16

private:
  // Private Constants

#define LED_CS_PIN 44
#define MUX_CS_PIN 60
#define NO_CS  0

#define ID_SENSE_PIN 61
#define AREF_EN_PIN 42
#define I2C_EN_PIN    45
#define SPARE_I2C_PIN 53

  //   #define PIN_MASK 0x0f
  //   #define DIR_MASK 0xf0

#define PCA9555L_ADR 0x20
#define PCA9555H_ADR 0x21
#define PCA9555_OUT0 0x02
#define PCA9555_OUT1 0x03
#define PCA9555_CFG0 0x06
#define PCA9555_CFG1 0x07


#define PIN_MASK 0x0f
#define DIR_MASK 0xf0

  void SPIselect(uint8_t chip);
  void UpdateIOs(void);

};

#endif // BCSIII
