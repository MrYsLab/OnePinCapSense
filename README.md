OnePinCapSense
==============

A one pin capacitive sensor library for Ardino that support multi-touch

Rationale for this library:

I wanted to have an inexpensive and simple way to detect user touch of an object,
with the requirements of utilizing one pin per sensor, no user grounding, and allowing for 
multi-touch capabilities.  

Written by Alan Yorinks
  Copyright (c) 2013 Alan Yorinks All right reserved.

  
  Version .01 August 7, 2013


Manifest:
   This package contains:
   
     1. The library files OnePinCapSense.h and OnePinCapSense.cpp
     
     2. An example program, called OnePinCapSenseExample.ino , 
        demonstrating 5 capacitive sensors and 5 associated LED
        indicators.
        
     3. A diagram showing a typical hardware implementation for a 
        single sensor and LED. Duplicate this for as many sensors
        as you require.
        
     4. A sample Scratch 2.0 test program called testCapSense.sb2
     
     5. This README file
     
     
To install, follow the library installation instructions on:
     http://arduino.cc/en/Guide/Libraries
     

This library was based upon the following references and previous projects:

References: 
http://urbanhonking.com/ideasfordozens/2009/05/18/an_tour_of_the_arduino_interna/

http://www.instructables.com/id/Turn-a-pencil-drawing-into-a-capacitive-sensor-for/

http://www.youtube.com/watch?v=LnpQgfTomNs



The instructables project listed above did everything I wanted for the UNO but not for the Leonardo.
I have modified that work to allow for use with the Leonardo as well as the UNO, by using 
standard Macros provided as part of the Arduino software IDE. Although only tested
with the UNO and Leonardo, it should work with all other Arduino boards.

The example program sends out key strokes using the Keyboard facility of the Leonardo.
This feature can be turned off by commenting out a #ifdef in the example.
