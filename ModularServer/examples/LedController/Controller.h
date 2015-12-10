// ----------------------------------------------------------------------------
// Controller.h
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "ModularDevice.h"
#include "Constants.h"
#include "Callbacks.h"
#include "NonBlockBlink.h"


class Controller
{
public:
  Controller();
  void setup();
  void update();

private:
};

extern Controller controller;

#endif
