#include "Arduino.h"
#include "Streaming.h"
#include "Array.h"
#include "Constants.h"
#include "MultiArray.h"


MultiArray multi_array;

void setup()
{
  Serial.begin(constants::baudrate);
  delay(1000);

  Serial << "multi_array:" << endl;
  multi_array.print();
}


void loop()
{
}
