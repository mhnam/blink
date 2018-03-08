/*
   Blink.cpp - Library for blinking led light.
   Created by Minhyuk Nam, March 9, 2018.
   Released into the public domain.
 */

#include "Arduino.h"
#include "Blink.h"

Blink::Blink(int pin){
  pinMode(pin, OUTPUT);   // initialize digital pin as an output.
  _pin = pin;
}

void Blink::on(int time){
  digitalWrite(_pin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(time);   // wait for a second
}

void Blink::off(int time){
  digitalWrite(_pin, LOW);   // turn the LED off by making the voltage LOW
  delay(time);   // wait for a second 
}
 
