#include "Arduino.h"
#include "Streaming.h"
#include "GenericSerial.h"


const int BAUDRATE = 9600;
GenericSerial generic_serial(Serial);

void setup()
{
  generic_serial.getSerial().begin(BAUDRATE);
  generic_serial.getSerial().flush();
  delay(1000);
}


void loop()
{
  generic_serial.getSerial().println("Hello ");
  generic_serial.getSerial() << "World!" << endl;
  delay(1000);  // do not print too fast!
}
