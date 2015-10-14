// ----------------------------------------------------------------------------
// Server.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef _SERVER_H_
#define _SERVER_H_
#include "GenericSerial.h"

class Server
{
public:
  Server(GenericSerial &serial);
  void setSerial(GenericSerial &serial);
  GenericSerial generic_serial_;
};

#endif
