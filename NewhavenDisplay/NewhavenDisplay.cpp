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

NewhavenDisplay::NewhavenDisplay(HardwareSerial &serial, const int row_count, const int col_count) :
  row_count_(row_count),
  col_count_(col_count)
{
  setSerial(serial);
}

void NewhavenDisplay::setSerial(HardwareSerial &serial)
{
  serial_ptr_ = &serial;
}

void NewhavenDisplay::setup()
{
  resetDefaultPaddingChar();
  serial_ptr_->begin(BAUDRATE);
  setContrastDefault();
  setBrightnessDefault();
  clearScreen();
  blinkingCursorOff();
  underlineCursorOff();
  displayOn();
}

void NewhavenDisplay::resetDefaultPaddingChar()
{
  padding_char_ = ' ';
}

char NewhavenDisplay::getPaddingChar()
{
  return padding_char_;
}

void NewhavenDisplay::displayOn()
{
  sendCmd(0x41);
}

void NewhavenDisplay::displayOff()
{
  sendCmd(0x42);
}

void NewhavenDisplay::setCursor(const int row, const int col)
{
  int row_mod = row%row_count_;
  int col_mod = col%col_count_;
  uint8_t pos;
  switch (row_mod)
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
  pos += col_mod;
  sendCmd(0x45);
  serial_ptr_->write(pos);
}

void NewhavenDisplay::setCursor(const int pos)
{
  int row = pos / col_count_;
  int col = pos % col_count_;
  setCursor(row,col);
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

void NewhavenDisplay::setContrast(const int percent)
{
  int percent_checked = percent;
  if (percent_checked < PERCENT_MIN)
  {
    percent_checked = PERCENT_MIN;
  }
  else if (percent_checked > PERCENT_MAX)
  {
    percent_checked = PERCENT_MAX;
  }
  uint8_t contrast = betterMap(percent_checked,
                               PERCENT_MIN,
                               PERCENT_MAX,
                               CONTRAST_MIN,
                               CONTRAST_MAX);
  sendCmd(0x52);
  serial_ptr_->write(contrast);
}

void NewhavenDisplay::setContrastDefault()
{
  setContrast(CONTRAST_PERCENT_DEFAULT);
}

void NewhavenDisplay::setBrightness(const int percent)
{
  int percent_checked = percent;
  if (percent_checked < PERCENT_MIN)
  {
    percent_checked = PERCENT_MIN;
  }
  else if (percent_checked > PERCENT_MAX)
  {
    percent_checked = PERCENT_MAX;
  }
  uint8_t brightness = betterMap(percent_checked,
                                 PERCENT_MIN,
                                 PERCENT_MAX,
                                 BRIGHTNESS_MIN,
                                 BRIGHTNESS_MAX);
  sendCmd(0x53);
  serial_ptr_->write(brightness);
}

void NewhavenDisplay::setBrightnessDefault()
{
  setBrightness(BRIGHTNESS_PERCENT_DEFAULT);
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

int NewhavenDisplay::getRowCount()
{
  return row_count_;
}

int NewhavenDisplay::getColCount()
{
  return col_count_;
}

void NewhavenDisplay::sendCmd(const int cmd)
{
  // serial_ptr_->flush();
  serial_ptr_->write(0xFE);
  serial_ptr_->write(cmd);
}

void NewhavenDisplay::stringPadLeft(String &str, const int length_total)
{
  str.trim();
  if (str.length() > length_total)
  {
    str = str.substring(0,length_total);
  }
  String padding = String(padding_char_);
  while (str.length() < length_total)
  {
    str = padding + str;
  }
}

void NewhavenDisplay::stringPadRight(String &str, const int length_total)
{
  str.trim();
  if (str.length() > length_total)
  {
    str = str.substring(0,length_total);
  }
  String padding = String(padding_char_);
  while (str.length() < length_total)
  {
    str += padding;
  }
}
