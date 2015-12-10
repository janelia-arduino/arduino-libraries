// ----------------------------------------------------------------------------
// Callbacks.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef CALLBACKS_H
#define CALLBACKS_H
#include "ArduinoJson.h"
#include "ModularDevice.h"
#include "Constants.h"
#include "Controller.h"
#include "NonBlockBlink.h"


namespace callbacks
{
void setLedOnCallback();

void setLedOffCallback();

void getLedPinCallback();

void blinkLedCallback();
}
#endif
