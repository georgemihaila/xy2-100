#include "DifferentialWirePair.h"
#include <Arduino.h>

DifferentialWirePair::DifferentialWirePair(int pinP, int pinM) {
  _pinP = pinP;
  _pinM = pinM;
  _curent_state = 0;

  pinMode(_pinP, OUTPUT);
  pinMode(_pinM, OUTPUT);

  set(0);
}

void DifferentialWirePair::set(unsigned char state) {
  _curent_state = state;
  digitalWrite(_pinP, _curent_state == 1 ? HIGH : LOW);
  digitalWrite(_pinM, _curent_state == 0 ? HIGH : LOW);
}

void DifferentialWirePair::invert() { set(!_curent_state); }