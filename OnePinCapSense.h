/*
  OnePinCapSense.h - Capacitive sensor library that uses a single
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

#ifndef ONE_PIN_CAP_SENSE_H
#define ONE_PIN_CAP_SENSE_H

#include <Arduino.h>
#include <pins_arduino.h>

// This class provides the facility to read the value of an input
// pin setup as a capacitve sensor.

// The library requires only one pin per sensor
// and when multiple sensors are used, multi-touch can
// be implemented (see OnePinCapSenseExample.h and see OnePinCapSenseExample.cpp)
// included in this library.


class OnePinCapSense
{
   public:
   // constructors
   OnePinCapSense() ; // default
  
   // methods
   // read the capacitive value for a given pin and return
   // the number of cycles it takes to charge the pin                                    
   int readCapacitivePin( int pin ) ; 
   
   // change the number of sampling cycles
   void setNumCycles(int newNumCycles) ;
   
   private:
   // variables
   uint8_t bitmask ;               // bitmask to access pin
   uint8_t port ;                  // port register
   volatile uint8_t *ddr ;         // data direction register
   volatile uint8_t *pinIn ;       //input data
   volatile uint8_t *pinOut  ;     //output data 
   int cycles ;                    // maximum number of cycles to allow
                                   // pin to charge up.
                                  

};

#endif                                         
             
