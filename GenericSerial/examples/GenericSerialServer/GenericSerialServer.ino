#include "Arduino.h"
#include "Streaming.h"
#include "GenericSerial.h"
#include "Server.h"


const int BAUDRATE = 9600;
GenericSerial generic_serial(Serial);
Server server(generic_serial);

void setup()
{
  server.generic_serial_.getSerial().begin(BAUDRATE);
  server.generic_serial_.getSerial().flush();
  delay(1000);
}


void loop()
{
  server.generic_serial_.getSerial().println("Hello ");
  server.generic_serial_.getSerial() << "World!" << endl;
  delay(1000);  // do not print too fast!
}
