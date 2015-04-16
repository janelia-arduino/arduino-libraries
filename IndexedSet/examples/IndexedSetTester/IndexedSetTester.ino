#include "Arduino.h"
#include "Streaming.h"
#include "Array.h"
#include "IndexedSet.h"


const int BAUDRATE = 9600;

const int ELEMENT_COUNT_MAX = 10;

typedef uint32_t IndexedSetType;

void printIndexedSet(IndexedSet<IndexedSetType,ELEMENT_COUNT_MAX> indexed_set)
{
  Serial << "[";
  for (int i=0; i<ELEMENT_COUNT_MAX; i++)
  {
    if (indexed_set.indexHasValue(i))
    {
      if (i != 0)
      {
        Serial << ",";
      }
      Serial << indexed_set[i];
    }
  }
  Serial << "]" << endl;
}

void setup()
{
  Serial.begin(BAUDRATE);
  delay(1000);

  IndexedSet<IndexedSetType,ELEMENT_COUNT_MAX> indexed_set;
  Serial << "initial indexed_set :" << endl;
  printIndexedSet(indexed_set);

  indexed_set.add(1234);
  Serial << "indexed_set.add(1234) :" << endl;
  printIndexedSet(indexed_set);

  indexed_set.add(5678);
  Serial << "indexed_set.add(5678) :" << endl;
  printIndexedSet(indexed_set);

  indexed_set.add(90);
  Serial << "indexed_set.add(90) :" << endl;
  printIndexedSet(indexed_set);

  indexed_set.add(1234);
  Serial << "indexed_set.add(1234) :" << endl;
  printIndexedSet(indexed_set);

  int index = indexed_set.findIndex(5678);
  Serial << "indexed_set.findIndex(5678) :" << endl;
  Serial << index << endl;

  indexed_set.removeUsingValue(5678);
  Serial << "indexed_set.removeUsingValue(5678) :" << endl;
  printIndexedSet(indexed_set);

  index = indexed_set.findIndex(5678);
  Serial << "indexed_set.findIndex(5678) :" << endl;
  Serial << index << endl;

  indexed_set.add(3456);
  Serial << "indexed_set.add(3456) :" << endl;
  printIndexedSet(indexed_set);

  indexed_set.add(5678);
  Serial << "indexed_set.add(5678) :" << endl;
  printIndexedSet(indexed_set);

  index = indexed_set.findIndex(5678);
  Serial << "indexed_set.findIndex(5678) :" << endl;
  Serial << index << endl;

  indexed_set.removeUsingIndex(index);
  Serial << "indexed_set.removeUsingIndex(" << index << ") :" << endl;
  printIndexedSet(indexed_set);

}


void loop()
{
}
