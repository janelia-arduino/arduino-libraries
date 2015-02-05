// ----------------------------------------------------------------------------
// AD7328.h
//
// Provides an SPI based interface to the AD7328 eight channel
// 12 bit plus sign ADC
//
// Authors:
// Steve Sawtelle sawtelles@janelia.hhmi.org
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "AD7328.h"


AD7328::AD7328(uint8_t cs_pin) :
  cs_pin_(cs_pin)
{
  pinMode(cs_pin_, OUTPUT);
  digitalWrite(cs_pin_, HIGH);
  range_l_ = 0xa000;
  range_h_ = 0xc000;
}

void AD7328::setRange( uint8_t ch, uint8_t range)
{
  switch (ch)
  {
    case 0:
      range_l_ = range_l_ & CH0_MASK;
      range_l_ |= range << 11;
      break;
    case 1:
      range_l_ = range_l_ & CH1_MASK;
      range_l_ |= range << 9;
      break;
    case 2:
      range_l_ = range_l_ & CH2_MASK;
      range_l_ |= range << 7;
      break;
    case 3:
      range_l_ = range_l_ & CH3_MASK;
      range_l_ |= range << 5;
      break;
    case 4:
      range_h_ = range_l_ & CH4_MASK;
      range_h_ |= range << 11;
      break;
    case 5:
      range_h_ = range_l_ & CH5_MASK;
      range_h_ |= range << 9;
      break;
    case 6:
      range_h_ = range_l_ & CH6_MASK;
      range_h_ |= range << 7;
      break;
    case 7:
      range_h_ = range_l_ & CH7_MASK;
      range_h_ |= range << 5;
      break;

  }

  ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
  {
    SPI.setDataMode(SPI_MODE2);  // set proper mode, clk idle hi, edeg = 0 => mode = 2
    digitalWrite(cs_pin_, LOW);
    if( ch < 4 )
    {
      SPI.transfer( range_l_ >> 8);
      SPI.transfer( range_l_ & 0xff);
    }
    else
    {
      SPI.transfer( range_h_ >> 8);
      SPI.transfer( range_h_ & 0xff);
    }
    digitalWrite(cs_pin_, HIGH);

  }
}


uint8_t AD7328::getRange( uint8_t ch)
{
  switch (ch)
  {
    case 0:
      return(( range_l_ >> 11 ) & 0x03);
      break;
    case 1:
      return(( range_l_ >>  9 ) & 0x03);
      break;
    case 2:
      return(( range_l_ >>  7 ) & 0x03) ;
      break;
    case 3:
      return(( range_l_ >>  5 ) & 0x03);
      break;
    case 4:
      return(( range_h_ >> 11 ) & 0x03);
      break;
    case 5:
      return(( range_h_ >>  9 ) & 0x03);
      break;
    case 6:
      return(( range_h_ >>  7 ) & 0x03) ;
      break;
    case 7:
      return(( range_h_ >>  5 ) & 0x03);
      break;

  }
  return 0;
}

uint16_t AD7328::read(uint8_t adc) //, uint8_t coding)
{
  uint16_t adc_value;
  uint16_t setup;

  ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
  {
    adc--;  // convert ADC1-8 to 0-7
    // first transaction - select the channel by writing to the control register
    SPI.setDataMode(SPI_MODE2);  // set proper mode, clk idle hi, edeg = 0 => mode = 2
    digitalWrite(cs_pin_, LOW);
    setup = 0b1000000000010000;  // write to control, single ended, normal mode, int ref, 2's comp
    setup |= ((adc & 0x07) << 10); // get adc reg number to right place and add it in
    adc_value = (SPI.transfer(setup >> 8)) << 8;
    adc_value |= SPI.transfer(setup & 0xff);
    digitalWrite(cs_pin_, HIGH);

    // second transaction - read the analog value
    //      digitalWrite(cs_pin_, LOW);
    //      adc_value = SPI.transfer(0) << 8;
    //      adc_value |= SPI.transfer(0);
    //      digitalWrite(cs_pin_, HIGH);

    // sign-extend if negative
    //  if ((coding == 0) && ((adc_value & 0x1000) == 0x1000)) {
    //    adc_value = (adc_value >> 1) | 0xf000;
    //  }
    //  else {
    //    adc_value = (adc_value >> 1) & 0x0fff;
    //  }
  } // end atomic block
  // return the 12 bit value
  return adc_value;
}
