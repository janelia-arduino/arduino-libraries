// ----------------------------------------------------------------------------
// NewhavenDisplay.h
//
// Provides an interface to the Newhaven serial liquid crystal display
// modules.
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef NEWHAVEN_DISPLAY_H
#define NEWHAVEN_DISPLAY_H
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <Stream.h>
#include <HardwareSerial.h>
#include "Streaming.h"
#include "BetterMap.h"

class NewhavenDisplay {
 public:
  NewhavenDisplay(HardwareSerial &serial);
  NewhavenDisplay(HardwareSerial &serial, const int row_count, const int col_count);
  void setSerial(HardwareSerial &serial);
  void setup();
  template<typename T>
  void print(const T value)
  {
    serial_ptr_->print(value);
  }
  template<typename T>
  void printPadLeft(const T value, const int total_length)
  {
    String string = String(value);
    stringPadLeft(string,total_length);
    serial_ptr_->print(string);
  }
  template<typename T>
  void printPadRight(const T value, const int total_length)
  {
    String string = String(value);
    stringPadRight(string,total_length);
    serial_ptr_->print(string);
  }
  template<typename T>
  void setPaddingChar(const T value)
  {
    String string = String(value);
    if (string.length() > 0)
    {
      padding_char_ = string.charAt(0);
    }
    else
    {
      padding_char_ = ' ';
    }
  }
  void resetDefaultPaddingChar();
  char getPaddingChar();
  void displayOn();
  void displayOff();
  void setCursor(const int row, const int col);
  void setCursor(const int pos);
  void homeCursor();
  void underlineCursorOn();
  void underlineCursorOff();
  void moveCursorLeft();
  void moveCursorRight();
  void blinkingCursorOn();
  void blinkingCursorOff();
  void backspace();
  void clearScreen();
  void setContrast(const int percent);
  void setContrastDefault();
  void setBrightness(const int percent);
  void setBrightnessDefault();
  void moveDisplayLeft();
  void moveDisplayRight();
  void displayFirmwareVersion();
  void displayRs232Rate();
  int getRowCount();
  int getColCount();

 private:
  HardwareSerial *serial_ptr_;
  const int row_count_;
  const int col_count_;
  char padding_char_;
  const static int ROW_COUNT_DEFAULT = 4;
  const static int COL_COUNT_DEFAULT = 20;
  const static int BAUDRATE = 9600;
  const static int PERCENT_MIN = 0;
  const static int PERCENT_MAX = 100;
  const static int BRIGHTNESS_MIN = 1;
  const static int BRIGHTNESS_MAX = 8;
  const static int BRIGHTNESS_PERCENT_DEFAULT = 15;
  const static int CONTRAST_MIN = 1;
  const static int CONTRAST_MAX = 50;
  const static int CONTRAST_PERCENT_DEFAULT = 80;
  void sendCmd(const int cmd);
  void stringPadLeft(String &, const int length_total);
  void stringPadRight(String &, const int length_total);
};


#endif
