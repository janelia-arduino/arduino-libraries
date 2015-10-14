// ----------------------------------------------------------------------------
// Server.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "Server.h"


Server::Server(GenericSerial &serial)
{
  setSerial(serial);
}

void Server::setSerial(GenericSerial &serial)
{
  generic_serial_ = serial;
}
