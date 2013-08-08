/*
  OnePinCapSenseExample.ino
                     Example program that demonstrates the use
                     of the OnePineCapSense library.
          
  Written by Alan Yorinks
  Copyright (c) 2013 Alan Yorinks All right reserved.

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
  
  Version .01
*/

#include "OnePinCapSense.h"

// uncomment to enable various debug statements sent to 
// serial monitor

//#define DEBUG
//#define DEBUG_BASELINE
#define SEND_KEY_EVENTS // allow leonardo to send out keystrokes

// This sketch will read the capcitive values from pins digital
// pins 2, 4, 6, 8, 10.

// Digital input sensor pins
int capSensePin2   =  2;
int capSensePin4   =  4;
int capSensePin6   =  6;
int capSensePin8   =  8;
int capSensePin10  = 10;

// led output pins
// An LED is provided for each sense pin and will be set
// HIGH when a sense pin is "touched"
int led3  =  3 ;
int led5  =  5 ;
int led7  =  7 ;
int led9  =  9 ;
int led11 = 11 ;

// baseLine is the maximum quiescent value for all sensor pins.
// It will be determined by the calibrate function below.
int baseLine = 0 ;

// offset will be added to the baseLine to provide a value
// to determine when a sensor is touched.
const int offset = 50 ;

// after calibration, touched will be set by adding offset to the 
// calibrated baseLine
int touched = 0 ;

// Cap sense values returned from the library.
// There is a seperate value for each sensor to allow for
// Multi-touch
int capSense2 ;
int capSense4 ;
int capSense6 ;
int capSense8 ;
int capSense10 ;

// create an instance of OnePinCapSense class
OnePinCapSense opcs = OnePinCapSense();

void setup()
{
  // Establish serial speed
  Serial.begin(9600);
  
  // flash the LEDs
  lightShow() ;
  
  // calibrate the system for touched value
  calibrate() ;

  
#ifdef DEBUG_BASELINE  
  // give some time to bring up the serial monitor
  delay(3000) ;
  
  Serial.print("Baseline: ") ;
  Serial.println(baseLine) ;
  
  Serial.print("Offset: ") ;
  Serial.println(offset) ;
  
  Serial.print("Touched: ") ;
  Serial.println(touched) ;
#endif
}   // end of setup()


void loop()
{
 
#ifdef DEBUG
  // Every 50 ms, print the value of the capacitive sensor
  if ( (millis() % 50) == 0)
  {
    // for debug
    Serial.print("Pin2: ");
    Serial.print(opcs.readCapacitivePin(capSensePin2));
    //delay(10) ;
    Serial.print("  Pin4: ");
    Serial.print(opcs.readCapacitivePin(capSensePin4));
    //    delay(10) ;
    Serial.print("  Pin6: ");
    Serial.print(opcs.readCapacitivePin(capSensePin6));
    //    delay(10) ;
    Serial.print("  Pin8:" );
    Serial.print(opcs.readCapacitivePin(capSensePin8));
     //   delay(10) ;
    Serial.print("  Pin10: ");
    Serial.println(opcs.readCapacitivePin(capSensePin10)); 
     //delay(10) ;   

  }
#endif

  // Get the values for all sensor pins.
  // If the capacitive sensor reads above a certain threshold,
  // turn on the associated LED
  
  // Allows for multi-touch
  
  capSense2 = opcs.readCapacitivePin(capSensePin2) ;
  if( capSense2 > touched)
  {
    digitalWrite(led3, HIGH) ;
    sendKeyEvents(KEY_UP_ARROW) ;

  }
  else
  {
    digitalWrite(led3, LOW) ;
  }
  
  capSense4 = opcs.readCapacitivePin(capSensePin4) ;
  if( capSense4 > touched)
  {
    digitalWrite(led5, HIGH) ;
    sendKeyEvents(KEY_DOWN_ARROW) ;

  }
  else
  {
    digitalWrite(led5, LOW) ;
  }
  
  capSense6 = opcs.readCapacitivePin(capSensePin6) ;
  if( capSense6 > touched)
  {
    digitalWrite(led7, HIGH) ;
    sendKeyEvents(KEY_LEFT_ARROW) ;
  }
  else
  {
    digitalWrite(led7, LOW) ;
  }
  
  capSense8 = opcs.readCapacitivePin(capSensePin8) ;
  if( capSense8 > touched)
  {
    digitalWrite(led9, HIGH) ;
    sendKeyEvents(KEY_RIGHT_ARROW) ;
  }
  else
  {
    digitalWrite(led9, LOW) ;
  }
  
  capSense10 = opcs.readCapacitivePin(capSensePin10) ;
  if( capSense10 > touched)
  {
    digitalWrite(led11, HIGH) ;
    sendKeyEvents(' ') ;
  }
  else
  {
    digitalWrite(led11, LOW) ;
  }
} // end of loop()

// voidligthShow()
// flash the leds

void lightShow()
{
  // test the 5 leds by sequencing them
  for(int i = 3 ; i < 12 ; i+=2)
  {
      pinMode(i, OUTPUT);
      digitalWrite(i, HIGH) ;
      delay(100) ;
      digitalWrite(i, LOW);
  }
  
  // flash all leds 5 times for fun
  for(int i = 0 ; i < 5 ; i++)
  {
    digitalWrite(led3,  HIGH)  ;
    digitalWrite(led5,  HIGH)  ;
    digitalWrite(led7,  HIGH)  ;
    digitalWrite(led9,  HIGH)  ;  
    digitalWrite(led9,  HIGH)  ;   
    digitalWrite(led11, HIGH)  ; 
    delay(500) ;
    digitalWrite(led3,  LOW)  ;
    digitalWrite(led5,  LOW)  ;
    digitalWrite(led7,  LOW)  ;
    digitalWrite(led9,  LOW)  ;  
    digitalWrite(led9,  LOW)  ;   
    digitalWrite(led11, LOW)  ; 
    delay(500) ;
  }  
}  // end of lightShow()


// The calibrate function will find the highest quiescent sensor
// value for all of the sensors and assign that to baseline.

// It will offset to calculated baseLine and assign that to the
// touched threshold.

int calibrate()
{
  int sample = 0 ;
  
  for(int i = 2 ; i < 11 ; i+=2)
  {
     // take 30 samples and return the highest value for the pin
     for( int j = 0 ; j < 30 ; j++ )
     {
       sample = opcs.readCapacitivePin(i) ;
       if( sample > baseLine)
       {
         baseLine = sample ;
       }
     }
  }
  touched = baseLine + offset ;
} // end of calibrate

// for Leonardo, send keyboard events


void sendKeyEvents( byte keyPress)
{
#ifdef SEND_KEY_EVENTS  
    Keyboard.begin() ;
    Keyboard.write(keyPress) ;
    Keyboard.end() ;
    
    // delay a little to "debounce"
    delay(100) ;
#endif
}
    

