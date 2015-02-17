#include "Arduino.h"
#include "Streaming.h"
#include "BetterMap.h"


const int BAUDRATE = 9600;

const int in_min = 0;
const int in_max = 1023;
const int out_min = 0;
const int out_max = 15;

void setup()
{
  Serial.begin(BAUDRATE);
  delay(2000);
  Serial << "map(" << in_min << ".." << in_max << ", ";
  Serial << in_min << ", " << in_max << ", ";
  Serial << out_min << ", " << out_max << ")" << endl;
  int in;
  int out_count_array[out_max+1] = {0};
  int out;
  for(in=in_min; in<=in_max; in++)
  {
    out = map(in,in_min,in_max,out_min,out_max);
    out_count_array[out] += 1;
  }
  for(out=out_min; out<=out_max; out++)
  {
    Serial << " " << out << " " << out_count_array[out] << endl;
  }

  delay(1000);
  Serial << "betterMap(" << in_min << ".." << in_max << ", ";
  Serial << in_min << ", " << in_max << ", ";
  Serial << out_min << ", " << out_max << ")" << endl;
  int better_out_count_array[out_max+1] = {0};
  for(in=in_min; in<=in_max; in++)
  {
    out = betterMap(in,in_min,in_max,out_min,out_max);
    better_out_count_array[out] += 1;
  }
  for(out=out_min; out<=out_max; out++)
  {
    Serial << " " << out << " " << better_out_count_array[out] << endl;
  }
}


void loop()
{
}
