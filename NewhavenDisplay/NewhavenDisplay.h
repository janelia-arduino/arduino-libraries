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

class NewhavenDisplay {
 public:
  NewhavenDisplay(HardwareSerial &serial);
  NewhavenDisplay(HardwareSerial &serial, int row_count, int col_count);
  void setSerial(HardwareSerial &serial);
  void init();
  void print(const String &);
  void print(const char[]);
  void print(char);
  void printPadLeft(const String &, int total_length);
  void printPadLeft(const char[], int total_length);
  void printPadLeft(char, int total_length);
  void printPadRight(const String &, int total_length);
  void printPadRight(const char[], int total_length);
  void printPadRight(char, int total_length);
  void displayOn();
  void displayOff();
  void setCursor(int row, int col);
  void homeCursor();
  void underlineCursorOn();
  void underlineCursorOff();
  void moveCursorLeft();
  void moveCursorRight();
  void blinkingCursorOn();
  void blinkingCursorOff();
  void backspace();
  void clearScreen();
  void setContrast(int percent);
  void setBrightness(int percent);
  void moveDisplayLeft();
  void moveDisplayRight();
  void displayFirmwareVersion();
  void displayRs232Rate();

 private:
  HardwareSerial *serial_ptr_;
  int row_count_;
  int col_count_;
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
  void sendCmd(int cmd);
  void stringPadLeft(String &, int length_total);
  void stringPadRight(String &, int length_total);
};


#endif
