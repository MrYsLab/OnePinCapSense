/*
  OnePinCapSense.cpp - Capacitive sensor library that uses a single
                       digital input pin per sensor and allows
                       for detection of multiple simultaneous
                       activations           
  Written by Alan Yorinks
  Copyright (c) 2013 Alan Yorinks All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
  
  Version .01 August 7, 2013
*/

#include "OnePinCapSense.h"
  
// Constructor
OnePinCapSense::OnePinCapSense()   // default constructor
{
    // initialize variables

   bitmask = 0 ;        // bitmask to access pin
   port    = 0;         // port register
   *ddr    = NULL ;     // data direction register
   *pinIn  = NULL ;     //input data
   *pinOut = NULL ;     //output data 
   cycles  = 16000 ;    // number of sample cycles    
   
}

// alter the number of sampling cycles
void OnePinCapSense::setNumCycles(int newNumCycles)
{
  cycles = newNumCycles ;
}

// read the capacitive value for the given arduino pin
// and return the read value
int OnePinCapSense::readCapacitivePin(int pin)
{
 port = digitalPinToPort(pin); // get the pin's port
 bitmask = digitalPinToBitMask(pin);
 ddr = portModeRegister(port); // get the ddr 
 pinIn = portInputRegister(port); // port input register
 pinOut = portOutputRegister(port);
 int numCycles = cycles ;  

  // Discharge the pin first by setting it low and output
  *pinOut &= ~(bitmask);
  *ddr  |= bitmask;
  delay(1);
  
  // Make the pin an input WITHOUT the internal pull-up on
  *ddr &= ~(bitmask);
  
  // Now see how many cycles it takes to get the pin pulled up
  for(int i = 0; i < numCycles; i++)
  {

    if (*pinIn & bitmask)
    {
      numCycles = i;
      break;
    }
  }

  // Discharge the pin again by setting it low and output
  //  It's important to leave the pins low if you want to 
  //  be able to touch more than 1 sensor at a time - if
  //  the sensor is left pulled high, when you touch
  //  two sensors, your body will transfer the charge between
  //  sensors.
  *pinOut &= ~(bitmask);
  *ddr  |= bitmask;

  return numCycles ;
}
