// ----------------------------------------------------------------------------
// BCSIII
//
// Provides an interface to the BCS III hardware
//  - IO setup
//  - SPI control
//
// Authors:
// Steve Sawtelle sawtelles@janelia.hhmi.org
// -------------------------------------------------------------

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <SPI.h>
#include <Wire.h>
#include "BCSIII.h"


//---------- constructor  ---------------------------------------

BCSIII::BCSIII(void)
{


  // congigure the I2C and Reference enables - start with both disabled (enable low)
  // I2C must be disabled while we initialize the mux
  // AREF must be disabled until we select external reference
  digitalWrite(AREF_EN_PIN, LOW);
  pinMode(AREF_EN_PIN, OUTPUT);
  analogReference(EXTERNAL);
  digitalWrite(AREF_EN_PIN, HIGH);

  digitalWrite(I2C_EN_PIN, LOW);
  pinMode(I2C_EN_PIN, OUTPUT);

  // disable chip selects and set them as ouputs
  SPIselect(NO_CS);
  pinMode(SPI1, OUTPUT);
  pinMode(SPI2, OUTPUT);
  pinMode(SPI3, OUTPUT);
  pinMode(SPI4, OUTPUT);
  pinMode(SPI5, OUTPUT);
  pinMode(SPI6, OUTPUT);
  pinMode(LED_CS_PIN, OUTPUT);
  pinMode(MUX_CS_PIN, OUTPUT);

}


//---------- public  ------------------------------------

void BCSIII::begin(void)
{

  // Initialize IO settings

  Wire.beginTransmission(PCA9555L_ADR);
  Wire.write(PCA9555_OUT1);   // set 1T45 direction value first
  Wire.write(0x00);           // 0 is BNC to IO (input)
  Wire.endTransmission();     // stop transmitting

  Wire.beginTransmission(PCA9555L_ADR);
  Wire.write(PCA9555_CFG1);   // set configuration
  Wire.write(0x00);           // now set PCA9555 as outputs
  Wire.endTransmission();     // stop transmit

  Wire.beginTransmission(PCA9555H_ADR);
  Wire.write(PCA9555_OUT0);   //
  Wire.write(0x00);           // disabled and
  Wire.write(0x00);           // 1T45 direction is input
  Wire.endTransmission();     // stop transmitting

  Wire.beginTransmission(PCA9555H_ADR);
  Wire.write(PCA9555_CFG0);   // set configuration
  Wire.write(0x00);           // outputs
  Wire.write(0x00);           // outputs
  Wire.endTransmission();     // stop transmit

  // at this point the IOs are all set as inputs (BNC in to CPU I/O) and
  //  the eight IOs with analog capabilty are set with digital off

}

uint8_t BCSIII::getPin(uint8_t BNC)
{
  return(IOpin[BNC]);
}

uint8_t BCSIII::getType(uint8_t BNC)
{
  return(IOtype[BNC]);
}


int8_t BCSIII::setIO(uint8_t BNC, uint8_t IO, uint8_t type)
{
  uint8_t i;

  Serial.print("BNC:");
  Serial.print(BNC);
  Serial.print(" to:");
  Serial.print(IO);
  Serial.print(" as:");
  Serial.println(type);

  if( (BNC < 1) || (BNC > 16) ) return BAD_BNC;
  BNC--;   // 1-8 --> 0-7

  // check for unsupported pin number
  for( i = 0; i < 16; i++ )
  {
    if( IO == pin_number[i]) break;
  }
  if( i == 16  ) return BAD_PIN;

  // clear any previous settings for the chosen IO
  //       for( ibnc  = 0; ibnc < 16; ibnc++ )
  //       {
  //          if( IOpin[ibnc] > 0 )
  //           {
  //               IOpin[ibnc] = 0;
  //               IOtype[ibnc] = NO_CONNECT;
  //           }
  //       }

  // if it's an input, set the IO as input first so we don't fight BNC vs IO out
  if( type == ANALOG_IN )
  {
    if( (IO >= A8) && (IO <= A15) ) // only IOs 8-15 can be analog
    {
      analogRead(IO);         // good one - set it - Analog inputs numbered same as IO pin names
      IOpin[BNC] = IO;
      IOtype[BNC]= type;     // and remember the new connection
    }
    else  // try to connect non-analog as analog
    {
      return BAD_ANALOG;
    }
  }
  else if( type == INPUT )     // or if it's a digital in
  {
    pinMode( IO, INPUT);     // set it
    IOpin[BNC] = IO;
    IOtype[BNC] = type; // and remember the new connection
  }
  else if( type == INPUT_PULLUP )     // or if it's a digital in w/ pullup
  {
    pinMode( IO, INPUT_PULLUP);     // set it
    IOpin[BNC] = IO;
    IOtype[BNC] = type; // and remember the new connection
  }
  else if( (type == OUTPUT) || (type == NO_CONNECT) )
  {
    IOpin[BNC] = IO;
    IOtype[BNC] = type; // and remember the new connection
  }
  else // not a known IO type
  {
    return BAD_TYPE;
  }


  UpdateIOs(); // and update the physical connections

  // if it was an input, now it safe to set as output
  if( type == OUTPUT )
    pinMode(IO, OUTPUT);

  return 0;

}




// -------------- PRIVATE
void BCSIII::SPIselect(uint8_t chip)
{
  digitalWrite(SPI1, HIGH);
  digitalWrite(SPI2, HIGH);
  digitalWrite(SPI3, HIGH);
  digitalWrite(SPI4, HIGH);
  digitalWrite(SPI5, HIGH);
  digitalWrite(SPI6, HIGH);
  digitalWrite(LED_CS_PIN, HIGH);
  digitalWrite(MUX_CS_PIN, HIGH);

  if( chip != NO_CS)
  {
    digitalWrite(chip, LOW);
  }
}


// set the mux and directions according to the setup info in the arrays
// the mux expects 256 contiguous bits, we will use 32 8 bit bytes
// Y15-X15, Y15-X14, .... etc
// Y is BNC side, X is IO side
// of course I have it messed up
// Let's call bottom left front BNC1
// then it goes top left front is BNC2
// So ---
// IOMUX[0] will be MUX0
// The value will be dir, BNC with BNC = bits 0-3
//

void BCSIII::UpdateIOs(void)
{
  //uint16_t dir = 0;
  //uint16_t en = 0;
  //uint16_t offset;
  uint8_t  dirL = 0;
  uint16_t dirH = 0;
  uint16_t muxbit;    // only allow one connection per BNC
  uint8_t shift;
  uint8_t pindex;

  Serial.print("10is");
  Serial.print(IOpin[9]);
  Serial.print(" ");
  Serial.println(IOtype[9]);


  //Set the multiplexer connection
  SPIselect(MUX_CS_PIN);
  SPI.setDataMode(SPI_MODE1);   // clock idles low, latched on rising edge

  for( int8_t bnc = 0; bnc < 16; bnc++) // walk through BNC array- low to high -
    // - should be high to low but then BNCs are all backwards - fix that in SW
  {

    // figure which IO channel this is
    for( pindex = 0; pindex < 16; pindex++ )
    {
      if( pin_number[pindex] == IOpin[bnc]) break;
    }

    // only set a channel if it has a direction (not a NC)
    if( IOtype[bnc] == NO_CONNECT )
      muxbit = 0;
    else
      muxbit = 1 << pindex; //put a connection '1' in right spot

    SPI.transfer( muxbit >> 8);    // do this BNC
    SPI.transfer( muxbit & 0xff);

    //Serial.println(muxbit, HEX);

    if( pindex < 16 ) // we have a real channel
    {
      // and while we are here, set the dir and enable lines
      if( pindex < 8 ) // lower 8 IOs are only digital so no enables
      {
        if( IOtype[bnc] == OUTPUT ) // if output
          dirL |= (1 << pindex); // an output needs a '1' in right spot
      }
      else  // higher 8 - have dir and enable , intermixed
      {   // get bit position of enable
        shift = pindex - 8; // 8-15 -> 0-7
        shift += shift;     // 0-7 -> 0-14

        if( IOtype[bnc] == OUTPUT ) // if output
        {  // set direction to '1'
          dirH |= (1 << (shift+1) ); // dir is one above enable (1-15)
        }

        if( IOtype[bnc] == ANALOG_IN ) // if analog, disable digital
        {
          dirH &= ~(1 << shift); // analog needs a '0' in the right spot
        }
        else
        {
          dirH |= (1 << shift); // digital needs a '1' in right spot
        }

      } // endif low or high ports
    }
  } // next BNC

  SPIselect(NO_CS);


  //Serial.print("dirL, dirH:");


  //Serial.print(dirL, HEX);
  Wire.beginTransmission(PCA9555L_ADR);
  Wire.write(PCA9555_OUT1);   // set direction
  Wire.write(dirL);           // dir is in
  Wire.endTransmission();     // stop transmitting
  //Serial.print(",");

  //Serial.println(dirH,HEX);

  Wire.beginTransmission(PCA9555H_ADR);
  Wire.write(PCA9555_OUT0);   // set direction and enables
  Wire.write(dirH & 0x00ff);  // low part
  Wire.write(dirH >> 8);      // high part
  Wire.endTransmission();     // stop transmitting
}
