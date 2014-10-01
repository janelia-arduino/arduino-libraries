// ----------------------------------------------------------------------------
// DeviceInterface.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "DeviceInterface.h"

DeviceInterface::DeviceInterface(Stream &stream) :
  stream_(stream)
{
}

void DeviceInterface::setMessageStream(Stream &stream)
{
  stream_ = stream;
}

void DeviceInterface::processMessage()
{
  while (stream_.available() > 0)
  {
    int message_length = stream_.readBytesUntil(EOL,message_,MESSAGE_LENGTH_MAX);
    message_[message_length] = '\0';
    stream_ << message_ << endl;
    if (message_[0] == JSON_OBJECT_START_CHAR)
    {
      Parser::JsonObject json_object = parser_.parse(message_);
      if (json_object.success())
      {
        for (Parser::JsonObjectIterator i=json_object.begin(); i!=json_object.end(); ++i)
        {
          stream_ << i.key() << " : " << (char*)i.value() << endl;
        }
        processObjectMessage(json_object);
      }
      else
      {
        stream_ << "Parsing JSON object failed!" << endl;
      }
    }
    else
    {
      if (message_[0] != JSON_ARRAY_START_CHAR)
      {
        String msg_str = String("[") + String(message_) + String("]");
        msg_str.toCharArray(message_,MESSAGE_LENGTH_MAX);
        stream_ << message_ << endl;
      }
      Parser::JsonArray json_array = parser_.parse(message_);
      if (json_array.success())
      {
        for (Parser::JsonArrayIterator i=json_array.begin(); i!=json_array.end(); ++i)
        {
          stream_ << (char*)*i << endl;
        }
        processArrayMessage(json_array);
      }
      else
      {
        stream_ << "Parsing JSON array failed!" << endl;
      }
    }
  }
}

void DeviceInterface::processObjectMessage(Parser::JsonObject &json_object)
{
  stream_ << "Processing object!" << endl;
}

void DeviceInterface::processArrayMessage(Parser::JsonArray &json_array)
{
  stream_ << "Processing array!" << endl;
}

DeviceInterface deviceInterface(Serial);
