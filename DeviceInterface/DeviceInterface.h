// ----------------------------------------------------------------------------
// DeviceInterface.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef _DEVICE_INTERFACE_H_
#define _DEVICE_INTERFACE_H_
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <Stream.h>
#include "Streaming.h"
#include "JsonParser.h"

using namespace ArduinoJson;

const char EOL = '\n';
const char JSON_OBJECT_START_CHAR = '{';
const char JSON_ARRAY_START_CHAR = '[';
const int MESSAGE_LENGTH_MAX = 257;
const char LEGACY_CMD_GET_DEVICE_INFO = 0;
const char LEGACY_CMD_GET_CMDS = 1;
const char LEGACY_CMD_GET_RSP_CODES = 2;

class DeviceInterface
{
public:
  DeviceInterface(Stream &stream);
  void setMessageStream(Stream &stream);
  void processMessage();
private:
  Stream &stream_;
  char message_[MESSAGE_LENGTH_MAX];
  Parser::JsonParser<32> parser_;

  void processObjectMessage(Parser::JsonObject &json_object);
  void processArrayMessage(Parser::JsonArray &json_array);
};

extern DeviceInterface deviceInterface;

#endif
