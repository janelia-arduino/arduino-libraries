// ----------------------------------------------------------------------------
// AD7328.h
//
// Provides an SPI based interface to the
//
// Author: Steve Sawtelle - based on TLE7232 by Peter Polidoro
// -------------------------------------------------------------

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <SPI.h>
#include "ADC_AD7328.h"


//---------- constructor  ---------------------------------------

ADC_AD7328::ADC_AD7328(uint8_t cspin)
{
  pinMode(cspin, OUTPUT);
  digitalWrite(cspin, HIGH);
  _csPin = cspin;
  _rangeL = 0xa000;
  _rangeH = 0xc000;
}


//---------- public  ------------------------------------
void ADC_AD7328::setRange( uint8_t ch, uint8_t range)
{
   switch (ch)
   {
	case 0: 
	  _rangeL = _rangeL & CH0_MASK;
       _rangeL |= range << 11;
	  break;
     case 1:
	  _rangeL = _rangeL & CH1_MASK;
       _rangeL |= range << 9;
	  break;
     case 2:
	  _rangeL = _rangeL & CH2_MASK;
       _rangeL |= range << 7;
	  break;
     case 3:
	  _rangeL = _rangeL & CH3_MASK;
       _rangeL |= range << 5;
	  break;
	case 4: 
	  _rangeH = _rangeL & CH4_MASK;
       _rangeH |= range << 11;
	  break;
     case 5:
	  _rangeH = _rangeL & CH5_MASK;
       _rangeH |= range << 9;
	  break;
     case 6:
	  _rangeH = _rangeL & CH6_MASK;
       _rangeH |= range << 7;
	  break;
     case 7:
	  _rangeH = _rangeL & CH7_MASK;
       _rangeH |= range << 5;
	  break;

   } 
    
   ATOMIC_BLOCK(ATOMIC_RESTORESTATE) 
  {
      SPI.setDataMode(SPI_MODE2);  // set proper mode, clk idle hi, edeg = 0 => mode = 2
      digitalWrite(_csPin, LOW);
      if( ch < 4 ) 
      {
         SPI.transfer( _rangeL >> 8); 
         SPI.transfer( _rangeL & 0xff); 
      }
      else
      {
         SPI.transfer( _rangeH >> 8); 
         SPI.transfer( _rangeH & 0xff); 
      }
      digitalWrite(_csPin, HIGH);

  }
}


uint8_t ADC_AD7328::getRange( uint8_t ch)
{
   switch (ch)
   {
	case 0: 
	  return(( _rangeL >> 11 ) & 0x03);
	  break;
     case 1:
	  return(( _rangeL >>  9 ) & 0x03);
	  break;
     case 2:
	  return(( _rangeL >>  7 ) & 0x03) ;
	  break;
     case 3:
	  return(( _rangeL >>  5 ) & 0x03);
	  break;
	case 4: 
	  return(( _rangeH >> 11 ) & 0x03);
	  break;
     case 5:
	  return(( _rangeH >>  9 ) & 0x03);
	  break;
     case 6:
	  return(( _rangeH >>  7 ) & 0x03) ;
	  break;
     case 7:
	  return(( _rangeH >>  5 ) & 0x03);
	  break;

   } 
   return 0;
}

uint16_t ADC_AD7328::read(uint8_t adc) //, uint8_t coding)
{
uint16_t adcValue;
uint16_t setup;

  ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
  {
      adc--;  // convert ADC1-8 to 0-7
      // first transaction - select the channel by writing to the control register
      SPI.setDataMode(SPI_MODE2);  // set proper mode, clk idle hi, edeg = 0 => mode = 2
      digitalWrite(_csPin, LOW);
      setup = 0b1000000000010000;  // write to control, single ended, normal mode, int ref, 2's comp
      setup |= ((adc & 0x07) << 10); // get adc reg number to right place and add it in
      adcValue = (SPI.transfer(setup >> 8)) << 8;
      adcValue |= SPI.transfer(setup & 0xff);
      digitalWrite(_csPin, HIGH);

      // second transaction - read the analog value
//      digitalWrite(_csPin, LOW);
//      adcValue = SPI.transfer(0) << 8;
//      adcValue |= SPI.transfer(0);
//      digitalWrite(_csPin, HIGH);

      // sign-extend if negative
    //  if ((coding == 0) && ((adcValue & 0x1000) == 0x1000)) {
    //    adcValue = (adcValue >> 1) | 0xf000;
    //  }
    //  else {
    //    adcValue = (adcValue >> 1) & 0x0fff;
    //  } 
  } // end atomic block
  // return the 12 bit value
  return adcValue;

}












