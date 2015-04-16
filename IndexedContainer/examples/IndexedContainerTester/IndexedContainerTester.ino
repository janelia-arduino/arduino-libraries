#include "Arduino.h"
#include "Streaming.h"
#include "Array.h"
#include "IndexedContainer.h"


const int BAUDRATE = 9600;

const int ELEMENT_COUNT_MAX = 5;

typedef uint32_t IndexedContainerType;

void printIndexedContainer(IndexedContainer<IndexedContainerType,ELEMENT_COUNT_MAX> indexed_container)
{
  Serial << "[";
  for (int i=0; i<ELEMENT_COUNT_MAX; i++)
  {
    if (indexed_container.indexHasValue(i))
    {
      if (i != 0)
      {
        Serial << ",";
      }
      Serial << indexed_container[i];
    }
  }
  Serial << "]" << endl;
}

void setup()
{
  Serial.begin(BAUDRATE);
  delay(1000);

  Serial << "ELEMENT_COUNT_MAX :" << endl;
  Serial << ELEMENT_COUNT_MAX << endl;

  IndexedContainer<IndexedContainerType,ELEMENT_COUNT_MAX> indexed_container;
  Serial << "initial indexed_container :" << endl;
  printIndexedContainer(indexed_container);

  int index = indexed_container.add(1234);
  Serial << "indexed_container.add(1234) :" << endl;
  printIndexedContainer(indexed_container);

  index = indexed_container.add(5678);
  Serial << "indexed_container.add(5678) :" << endl;
  printIndexedContainer(indexed_container);

  index = indexed_container.add(90);
  Serial << "indexed_container.add(90) :" << endl;
  printIndexedContainer(indexed_container);

  index = indexed_container.add(1234);
  Serial << "indexed_container.add(1234) :" << endl;
  printIndexedContainer(indexed_container);

  index = 2;
  indexed_container.remove(index);
  Serial << "indexed_container.remove(" << index << ") :" << endl;
  printIndexedContainer(indexed_container);

  index = indexed_container.add(3456);
  Serial << "indexed_container.add(3456) :" << endl;
  printIndexedContainer(indexed_container);

  index = indexed_container.add(5678);
  Serial << "indexed_container.add(5678) :" << endl;
  printIndexedContainer(indexed_container);

  index = indexed_container.add(90);
  Serial << "indexed_container.add(90) :" << endl;
  printIndexedContainer(indexed_container);

  index = 3;
  indexed_container.remove(index);
  Serial << "indexed_container.remove(" << index << ") :" << endl;
  printIndexedContainer(indexed_container);

}


void loop()
{
}
