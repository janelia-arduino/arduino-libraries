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

  int in_min_test = 0;
  int in_max_test = 10;
  const int out_min_test = 0;
  const int out_max_test = 100;
  delay(1000);
  Serial << "map(" << in_min_test << ".." << in_max_test << ", ";
  Serial << in_min_test << ", " << in_max_test << ", ";
  Serial << out_min_test << ", " << out_max_test << ")" << endl;
  for(in=in_min_test; in<=in_max_test; in++)
  {
    out = map(in,in_min_test,in_max_test,out_min_test,out_max_test);
    Serial << "in: " << in << " out: " << out << endl;
  }
  Serial << "betterMap(" << in_min_test << ".." << in_max_test << ", ";
  Serial << in_min_test << ", " << in_max_test << ", ";
  Serial << out_min_test << ", " << out_max_test << ")" << endl;
  for(in=in_min_test; in<=in_max_test; in++)
  {
    out = betterMap(in,in_min_test,in_max_test,out_min_test,out_max_test);
    Serial << "in: " << in << " out: " << out << endl;
  }

  in_min_test = 10;
  in_max_test = 0;
  delay(1000);
  Serial << "map(" << in_min_test << ".." << in_max_test << ", ";
  Serial << in_min_test << ", " << in_max_test << ", ";
  Serial << out_min_test << ", " << out_max_test << ")" << endl;
  for(in=in_min_test; in>=in_max_test; --in)
  {
    out = map(in,in_min_test,in_max_test,out_min_test,out_max_test);
    Serial << "in: " << in << " out: " << out << endl;
  }
  Serial << "betterMap(" << in_min_test << ".." << in_max_test << ", ";
  Serial << in_min_test << ", " << in_max_test << ", ";
  Serial << out_min_test << ", " << out_max_test << ")" << endl;
  for(in=in_min_test; in>=in_max_test; --in)
  {
    out = betterMap(in,in_min_test,in_max_test,out_min_test,out_max_test);
    Serial << "in: " << in << " out: " << out << endl;
  }
}


void loop()
{
}
