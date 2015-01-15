// ----------------------------------------------------------------------------
// NewhavenDisplay.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "NewhavenDisplay.h"

NewhavenDisplay::NewhavenDisplay() {
  this->rowCount = 4;
  this->colCount = 20;
}

NewhavenDisplay::NewhavenDisplay(int rowCount, int colCount) {
  this->rowCount = rowCount;
  this->colCount = colCount;
}

void NewhavenDisplay::init() {
  Serial3.begin(9600);
  setBrightness(2);
  clearScreen();
  blinkingCursorOff();
  underlineCursorOff();
  displayOn();
}

void NewhavenDisplay::print(const String &s) {
  Serial3.print(s);
}

void NewhavenDisplay::print(const char str[]) {
  Serial3.print(str);
}

void NewhavenDisplay::print(char c) {
  Serial3.print(c);
}

void NewhavenDisplay::printPadLeft(const String &s, int total_length) {
  String string = s;
  stringPadLeft(string,total_length);
  Serial3.print(string);
}

void NewhavenDisplay::printPadLeft(const char str[], int total_length) {
  String string = String(str);
  stringPadLeft(string,total_length);
  Serial3.print(string);
}

void NewhavenDisplay::printPadLeft(char c, int total_length) {
  String string = String(c);
  stringPadLeft(string,total_length);
  Serial3.print(string);
}

void NewhavenDisplay::printPadRight(const String &s, int total_length) {
  String string = s;
  stringPadRight(string,total_length);
  Serial3.print(string);
}

void NewhavenDisplay::printPadRight(const char str[], int total_length) {
  String string = String(str);
  stringPadRight(string,total_length);
  Serial3.print(string);
}

void NewhavenDisplay::printPadRight(char c, int total_length) {
  String string = String(c);
  stringPadRight(string,total_length);
  Serial3.print(string);
}

void NewhavenDisplay::displayOn() {
  sendCmd(0x41);
}

void NewhavenDisplay::displayOff() {
  sendCmd(0x42);
}

void NewhavenDisplay::setCursor(int row, int col) {
  row = row%rowCount;
  col = col%colCount;
  uint8_t pos;
  switch (row) {
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
  Serial3.write(pos);
}

void NewhavenDisplay::homeCursor() {
  sendCmd(0x46);
}

void NewhavenDisplay::underlineCursorOn() {
  sendCmd(0x47);
}

void NewhavenDisplay::underlineCursorOff() {
  sendCmd(0x48);
}

void NewhavenDisplay::moveCursorLeft() {
  sendCmd(0x49);
}

void NewhavenDisplay::moveCursorRight() {
  sendCmd(0x4A);
}

void NewhavenDisplay::blinkingCursorOn() {
  sendCmd(0x4B);
}

void NewhavenDisplay::blinkingCursorOff() {
  sendCmd(0x4C);
}

void NewhavenDisplay::backspace() {
  sendCmd(0x4E);
}

void NewhavenDisplay::clearScreen() {
  sendCmd(0x51);
}

void NewhavenDisplay::setContrast(int contrast) {
  if (contrast < 1) {
    contrast = 1;
  } else if (contrast > 50) {
    contrast = 50;
  }
  sendCmd(0x52);
  Serial3.write((uint8_t)contrast);
}

void NewhavenDisplay::setBrightness(int brightness) {
  if (brightness < 1) {
    brightness = 1;
  } else if (brightness > 8) {
    brightness = 8;
  }
  sendCmd(0x53);
  Serial3.write((uint8_t)brightness);
}

void NewhavenDisplay::moveDisplayLeft() {
  sendCmd(0x55);
}

void NewhavenDisplay::moveDisplayRight() {
  sendCmd(0x56);
}

void NewhavenDisplay::displayFirmwareVersion() {
  sendCmd(0x70);
}

void NewhavenDisplay::displayRs232Rate() {
  sendCmd(0x71);
}

void NewhavenDisplay::sendCmd(int cmd) {
  // Serial3.flush();
  Serial3.write(0xFE);
  Serial3.write(cmd);
}

void NewhavenDisplay::stringPadLeft(String &str, int length_total) {
  str.trim();
  if (str.length() > length_total) {
    str = str.substring(0,length_total);
  }
  String padding = " ";
  while (str.length() < length_total) {
    str = padding + str;
  }
}

void NewhavenDisplay::stringPadRight(String &str, int length_total) {
  str.trim();
  if (str.length() > length_total) {
    str = str.substring(0,length_total);
  }
  String padding = " ";
  while (str.length() < length_total) {
    str += padding;
  }
}
