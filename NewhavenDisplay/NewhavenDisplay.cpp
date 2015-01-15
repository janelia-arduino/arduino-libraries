// ----------------------------------------------------------------------------
// NewhavenDisplay.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "NewhavenDisplay.h"

NewhavenDisplay::NewhavenDisplay(HardwareSerial &serial) :
  row_count_(ROW_COUNT_DEFAULT),
  col_count_(COL_COUNT_DEFAULT)
{
  setSerial(serial);
}

NewhavenDisplay::NewhavenDisplay(HardwareSerial &serial, int row_count, int col_count)
{
  setSerial(serial);
  row_count_ = row_count;
  col_count_ = col_count;
}

void NewhavenDisplay::setSerial(HardwareSerial &serial)
{
  serial_ptr_ = &serial;
}

void NewhavenDisplay::init()
{
  serial_ptr_->begin(BAUDRATE);
  setBrightness(BRIGHTNESS_PERCENT_DEFAULT);
  setContrast(CONTRAST_PERCENT_DEFAULT);
  clearScreen();
  blinkingCursorOff();
  underlineCursorOff();
  displayOn();
}

void NewhavenDisplay::print(const String &s)
{
  serial_ptr_->print(s);
}

void NewhavenDisplay::print(const char str[])
{
  serial_ptr_->print(str);
}

void NewhavenDisplay::print(char c)
{
  serial_ptr_->print(c);
}

void NewhavenDisplay::printPadLeft(const String &s, int total_length)
{
  String string = s;
  stringPadLeft(string,total_length);
  serial_ptr_->print(string);
}

void NewhavenDisplay::printPadLeft(const char str[], int total_length)
{
  String string = String(str);
  stringPadLeft(string,total_length);
  serial_ptr_->print(string);
}

void NewhavenDisplay::printPadLeft(char c, int total_length)
{
  String string = String(c);
  stringPadLeft(string,total_length);
  serial_ptr_->print(string);
}

void NewhavenDisplay::printPadRight(const String &s, int total_length)
{
  String string = s;
  stringPadRight(string,total_length);
  serial_ptr_->print(string);
}

void NewhavenDisplay::printPadRight(const char str[], int total_length)
{
  String string = String(str);
  stringPadRight(string,total_length);
  serial_ptr_->print(string);
}

void NewhavenDisplay::printPadRight(char c, int total_length)
{
  String string = String(c);
  stringPadRight(string,total_length);
  serial_ptr_->print(string);
}

void NewhavenDisplay::displayOn()
{
  sendCmd(0x41);
}

void NewhavenDisplay::displayOff()
{
  sendCmd(0x42);
}

void NewhavenDisplay::setCursor(int row, int col)
{
  row = row%row_count_;
  col = col%col_count_;
  uint8_t pos;
  switch (row)
  {
    case 0:
      pos = 0;
      break;
    case 1:
      pos = 64;
      break;
    case 2:
      pos = 20;
      break;
    case 3:
      pos = 84;
      break;
    default:
      pos = 0;
      break;
  }
  pos += col;
  sendCmd(0x45);
  serial_ptr_->write(pos);
}

void NewhavenDisplay::homeCursor()
{
  sendCmd(0x46);
}

void NewhavenDisplay::underlineCursorOn()
{
  sendCmd(0x47);
}

void NewhavenDisplay::underlineCursorOff()
{
  sendCmd(0x48);
}

void NewhavenDisplay::moveCursorLeft()
{
  sendCmd(0x49);
}

void NewhavenDisplay::moveCursorRight()
{
  sendCmd(0x4A);
}

void NewhavenDisplay::blinkingCursorOn()
{
  sendCmd(0x4B);
}

void NewhavenDisplay::blinkingCursorOff()
{
  sendCmd(0x4C);
}

void NewhavenDisplay::backspace()
{
  sendCmd(0x4E);
}

void NewhavenDisplay::clearScreen()
{
  sendCmd(0x51);
}

void NewhavenDisplay::setContrast(int percent)
{
  if (percent < PERCENT_MIN)
  {
    percent = PERCENT_MIN;
  }
  else if (percent > PERCENT_MAX)
  {
    percent = PERCENT_MAX;
  }
  uint8_t contrast = map(percent,
                         PERCENT_MIN,
                         PERCENT_MAX,
                         CONTRAST_MIN,
                         CONTRAST_MAX);
  sendCmd(0x52);
  serial_ptr_->write(contrast);
}

void NewhavenDisplay::setBrightness(int percent)
{
  if (percent < PERCENT_MIN)
  {
    percent = PERCENT_MIN;
  }
  else if (percent > PERCENT_MAX)
  {
    percent = PERCENT_MAX;
  }
  uint8_t brightness = map(percent,
                           PERCENT_MIN,
                           PERCENT_MAX,
                           BRIGHTNESS_MIN,
                           BRIGHTNESS_MAX);
  sendCmd(0x53);
  serial_ptr_->write(brightness);
}

void NewhavenDisplay::moveDisplayLeft()
{
  sendCmd(0x55);
}

void NewhavenDisplay::moveDisplayRight()
{
  sendCmd(0x56);
}

void NewhavenDisplay::displayFirmwareVersion()
{
  sendCmd(0x70);
}

void NewhavenDisplay::displayRs232Rate()
{
  sendCmd(0x71);
}

void NewhavenDisplay::sendCmd(int cmd)
{
  // serial_ptr_->flush();
  serial_ptr_->write(0xFE);
  serial_ptr_->write(cmd);
}

void NewhavenDisplay::stringPadLeft(String &str, int length_total)
{
  str.trim();
  if (str.length() > length_total)
  {
    str = str.substring(0,length_total);
  }
  String padding = " ";
  while (str.length() < length_total)
  {
    str = padding + str;
  }
}

void NewhavenDisplay::stringPadRight(String &str, int length_total)
{
  str.trim();
  if (str.length() > length_total)
  {
    str = str.substring(0,length_total);
  }
  String padding = " ";
  while (str.length() < length_total)
  {
    str += padding;
  }
}
