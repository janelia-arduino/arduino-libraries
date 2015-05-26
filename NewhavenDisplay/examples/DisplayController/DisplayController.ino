#include "Arduino.h"
#include "Streaming.h"
#include "BetterMap.h"
#include "NewhavenDisplay.h"

NewhavenDisplay display = NewhavenDisplay(Serial3);
char inputBuffer[128];
uint8_t idx = 0;
boolean inputComplete = false;
char *argv[8];
int arg1, arg2, arg3;

const int BAUDRATE = 9600;

void parse(char *line, char **argv, uint8_t maxArgs)
{
  uint8_t argCount = 0;
  while (*line != '\0') // if not the end of line .......
  {
    while (*line == ',' || *line == ' ' || *line == '\t' || *line == '\n')
    {
      *line++ = '\0'; // replace commas and white spaces with 0
    }
    *argv++ = line; // save the argument position
    argCount++;
    if (argCount == maxArgs-1)
    {
      break;
    }
    while (*line != '\0' && *line != ',' && *line != ' ' &&
           *line != '\t' && *line != '\n')
    {
      line++; // skip the argument until ...
    }
  }
  *argv = '\0'; // mark the end of argument list
}

void setup()
{
  // PC communications
  Serial.begin(BAUDRATE);
  Serial.println("* System ready *");

  display.setup();
}


void loop() {
  if (inputComplete)
  {
    parse((char*)inputBuffer, argv, sizeof(argv));
    if (strcmp(argv[0], "print") == 0)
    {
      if (0 < strlen(argv[1]))
      {
        String display_str = argv[1];
        display.print(display_str);
      } else
      {
        Serial.println("print <DISPLAY_STRING>");
      }
    }
    else if (strcmp(argv[0], "displayOn") == 0)
    {
      display.displayOn();
    }
    else if (strcmp(argv[0], "displayOff") == 0)
    {
      display.displayOff();
    }
    else if (strcmp(argv[0], "setCursor") == 0)
    {
      if ((0 < strlen(argv[1])) && (0 < strlen(argv[2]))) {
        int row = atoi(argv[1]);
        int col = atoi(argv[2]);
        display.setCursor(row,col);
      }
      else
      {
        Serial.println("setCursor <ROW> <COL>, ROW = {0..3}, COL = {0..20}");
      }
    }
    else if (strcmp(argv[0], "homeCursor") == 0)
    {
      display.homeCursor();
    }
    else if (strcmp(argv[0], "underlineCursorOn") == 0)
    {
      display.underlineCursorOn();
    }
    else if (strcmp(argv[0], "underlineCursorOff") == 0)
    {
      display.underlineCursorOff();
    }
    else if (strcmp(argv[0], "moveCursorLeft") == 0)
    {
      display.moveCursorLeft();
    }
    else if (strcmp(argv[0], "moveCursorRight") == 0)
    {
      display.moveCursorRight();
    }
    else if (strcmp(argv[0], "blinkingCursorOn") == 0)
    {
      display.blinkingCursorOn();
    }
    else if (strcmp(argv[0], "blinkingCursorOff") == 0)
    {
      display.blinkingCursorOff();
    }
    else if (strcmp(argv[0], "backspace") == 0)
    {
      display.backspace();
    }
    else if (strcmp(argv[0], "clearScreen") == 0)
    {
      display.clearScreen();
    }
    else if (strcmp(argv[0], "setContrast") == 0)
    {
      if (0 < strlen(argv[1]))
      {
        int contrast = atoi(argv[1]);
        display.setContrast(contrast);
      }
      else
      {
        Serial.println("setContrast <CONTRAST>, CONTRAST = {1..50}");
      }
    }
    else if (strcmp(argv[0], "setBrightness") == 0)
    {
      if (0 < strlen(argv[1]))
      {
        int brightness = atoi(argv[1]);
        display.setBrightness(brightness);
      }
      else
      {
        Serial.println("setBrightness <PERCENT>, PERCENT = {0..100}");
      }
    }
    else if (strcmp(argv[0], "moveDisplayLeft") == 0)
    {
      display.moveDisplayLeft();
    }
    else if (strcmp(argv[0], "moveDisplayRight") == 0)
    {
      display.moveDisplayRight();
    }
    else if (strcmp(argv[0], "displayFirmwareVersion") == 0)
    {
      display.displayFirmwareVersion();
    }
    else if (strcmp(argv[0], "displayRs232Rate") == 0)
    {
      display.displayRs232Rate();
    }
    else if (strcmp(argv[0], "printPadLeft") == 0)
    {
      if ((0 < strlen(argv[1])) && (0 < strlen(argv[2]))) {
        String display_str = argv[1];
        int length = atoi(argv[2]);
        display.printPadLeft(display_str,length);
      }
      else
      {
        Serial.println("printPadLeft <DISPLAY_STRING> <LENGTH>, LENGTH = {1..20}");
      }
    }
    else if (strcmp(argv[0], "printPadRight") == 0)
    {
      if ((0 < strlen(argv[1])) && (0 < strlen(argv[2]))) {
        String display_str = argv[1];
        int length = atoi(argv[2]);
        display.printPadRight(display_str,length);
      }
      else
      {
        Serial.println("printPadRight <DISPLAY_STRING> <LENGTH>, LENGTH = {1..20}");
      }
    }
    else if (strcmp(argv[0], "setPaddingChar") == 0)
    {
      if (0 < strlen(argv[1]))
      {
        String padding_char = argv[1];
        display.setPaddingChar(padding_char);
      } else
      {
        Serial.println("setPaddingChar <PADDING_CHAR>");
      }
    }
    else if (strcmp(argv[0], "resetDefaultPaddingChar") == 0)
    {
      display.resetDefaultPaddingChar();
    }
    else if (strcmp(argv[0], "getPaddingChar") == 0)
    {
      char padding_char = display.getPaddingChar();
      Serial.println(String("\'") + String(padding_char) + String("\'"));
    }
    else
    {
      Serial.println("print <DISPLAY_STRING>, displayOn, displayOff, setCursor <ROW> <COL>, homeCursor, underlineCursorOn, underlineCursorOff, moveCursorLeft, moveCursorRight ...");
      Serial.println("blinkingCursorOn, blinkingCursorOff, backspace, clearScreen, setContrast <CONTRAST>, setBrightness <BRIGHTNESS>, moveDisplayLeft, moveDisplayRight ...");
      Serial.println("displayFirmwareVersion, displayRs232Rate, printPadLeft, printPadRight, setPaddingChar, resetDefaultPaddingChar, getPaddingChar");
    }

    inputComplete = false;
  }
}

void serialEvent()
{
  while (Serial.available())
  {
    uint8_t inByte;
    inByte = Serial.read();
    if ((inByte == '\n') || (inByte == '\r'))
    {
      Serial.println();
      inputBuffer[idx] = 0;
      idx = 0;
      inputComplete = true;
    }
    else if (((inByte == '\b') || (inByte == 0x7f)) && (idx > 0))
    {
      idx--;
      Serial.write(inByte);
      Serial.print(" ");
      Serial.write(inByte);
    }
    else if ((inByte >= ' ') && (idx < sizeof(inputBuffer) - 1))
    {
      inputBuffer[idx++] = inByte;
      Serial.write(inByte);
    }
  }
}
