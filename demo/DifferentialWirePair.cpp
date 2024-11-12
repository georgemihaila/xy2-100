#include "DifferentialWirePair.h"
#include <Arduino.h>

DifferentialWirePair::DifferentialWirePair(int pinP, int pinM) {
  _pinP = pinP;
  _pinM = pinM;
  _curent_state = 0;

  Serial.print("Set pin ");
  Serial.print(_pinP);
  Serial.print(" as output\n");
  pinMode(_pinP, OUTPUT);
  Serial.print("Set pin ");
  Serial.print(_pinM);
  Serial.print(" as output\n");
  pinMode(_pinM, OUTPUT);

  set(0);
}

void DifferentialWirePair::set(unsigned char state) {
  if (state != _curent_state) {
    digitalWrite(_pinP, state == 1 ? HIGH : LOW);
    digitalWrite(_pinM, state == 0 ? HIGH : LOW);
    _curent_state = state;
  }
}

void DifferentialWirePair::invert() { set(!_curent_state); }