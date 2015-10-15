#include "Arduino.h"
#include "Streaming.h"
#include "Flash.h"
#include "ConstantVariable.h"
#include <EEPROM.h>
#include "SavedVariable.h"

const int BAUDRATE = 9600;

CONSTANT_STRING(eeprom_initialized,"eeprom_initialized");
CONSTANT_STRING(simple_int,"simple_int");
CONSTANT_STRING(simple_double,"simple_double");
CONSTANT_STRING(complex_struct,"complex_struct");
CONSTANT_STRING(one_d_array,"one_d_array");
CONSTANT_STRING(two_d_array,"two_d_array");

const int eeprom_initialized_value = 111;
const int simple_int_default_value = 4567;
const double simple_double_default_value = 3.1415;
struct Product
{
  int weight;
  double price;
  boolean sold;
  Product() {};
  Product(int weight,double price,boolean sold) : weight(weight),price(price),sold(sold) {};
};
const Product complex_struct_default_value(100,1.25,true);
const int one_d_array_element_count = 4;
const int one_d_array_default_value[one_d_array_element_count] = {10,11,12,13};
const int two_d_array_element_count_a = 3;
const int two_d_array_element_count_b = 2;
const int two_d_array_default_value[two_d_array_element_count_a][two_d_array_element_count_b] =
  {{6,7},{16,17},{26,27}};

void setup()
{
  Serial.begin(BAUDRATE);
  Serial.flush();
  delay(1000);

  int eeprom_index = 0;

  SavedVariable eeprom_initialized_sv(eeprom_initialized,
                                      eeprom_index,
                                      eeprom_initialized_value);
  eeprom_index += eeprom_initialized_sv.getSize();

  SavedVariable simple_int_sv(simple_int,
                              eeprom_index,
                              simple_int_default_value);
  eeprom_index += simple_int_sv.getSize();

  SavedVariable simple_double_sv(simple_int,
                                 eeprom_index,
                                 simple_double_default_value);
  eeprom_index += simple_double_sv.getSize();

  SavedVariable complex_struct_sv(complex_struct,
                                  eeprom_index,
                                  complex_struct_default_value);
  eeprom_index += complex_struct_sv.getSize();

  SavedVariable one_d_array_sv(one_d_array,
                               eeprom_index,
                               one_d_array_default_value,
                               one_d_array_element_count);
  eeprom_index += one_d_array_sv.getSize();

  SavedVariable two_d_array_sv(two_d_array,
                               eeprom_index,
                               two_d_array_default_value,
                               two_d_array_element_count_a);
  eeprom_index += two_d_array_sv.getSize();

  int eeprom_initial_value;
  eeprom_initialized_sv.getValue(eeprom_initial_value);
  Serial << "eeprom_intial_value = " << eeprom_initial_value << endl;
  if (eeprom_initial_value != eeprom_initialized_value)
  {
    Serial << "Default values set for the first time!" << endl;
    eeprom_initialized_sv.setDefaultValue();
    simple_int_sv.setDefaultValue();
    complex_struct_sv.setDefaultValue();
    simple_double_sv.setDefaultValue();
    one_d_array_sv.setDefaultValue();
    two_d_array_sv.setDefaultValue();
  }
  else
  {
    Serial << "Default values already set!" << endl;
  }

  eeprom_initialized_sv.getValue(eeprom_initial_value);
  Serial << "eeprom_intial_value = " << eeprom_initial_value << endl;

  int simple_int_value;
  simple_int_sv.getValue(simple_int_value);
  Serial << "simple_int_sv.getSize() = " << simple_int_sv.getSize() << endl;
  Serial << "simple_int_value = " << simple_int_value << endl;

  double simple_double_value;
  simple_double_sv.getValue(simple_double_value);
  Serial << "simple_double_sv.getSize() = " << simple_double_sv.getSize() << endl;
  Serial << "simple_double_value = " << simple_double_value << endl;

  Product complex_struct_value;
  complex_struct_sv.getValue(complex_struct_value);
  Serial << "complex_struct_sv.getSize() = " << complex_struct_sv.getSize() << endl;
  Serial << "complex_struct_value.weight = " << complex_struct_value.weight << endl;
  Serial << "complex_struct_value.price = " << complex_struct_value.price << endl;
  Serial << "complex_struct_value.sold = " << complex_struct_value.sold << endl;
  complex_struct_value.price += 0.10;
  complex_struct_sv.setValue(complex_struct_value);

  int one_d_array_value[one_d_array_element_count];
  Serial << "one_d_array_sv.getSize() = " << one_d_array_sv.getSize() << endl;
  for (int i=0; i<one_d_array_element_count; ++i)
  {
    one_d_array_sv.getValue(one_d_array_value,i);
    Serial << "one_d_array_value[" << i << "] = " << one_d_array_value[i] << endl;
  }
  int p = 0;
  one_d_array_value[p] += 1;
  one_d_array_sv.setValue(one_d_array_value,p);

  int two_d_array_value[two_d_array_element_count_a][two_d_array_element_count_b];
  Serial << "two_d_array_sv.getSize() = " << two_d_array_sv.getSize() << endl;
  for (int i=0; i<two_d_array_element_count_a; ++i)
  {
    two_d_array_sv.getValue(two_d_array_value,i);
    for (int j=0; j<two_d_array_element_count_b; ++j)
    {
      Serial << "two_d_array_value[" << i << "][" << j << "] = "<< two_d_array_value[i][j] << endl;
    }
  }
  int q = 0;
  int r = 1;
  two_d_array_value[q][r] += 1;
  two_d_array_sv.setValue(two_d_array_value,q);

}


void loop()
{
}
