#include "XY2_100.h"
#include <Arduino.h>

XY2_100::XY2_100(int clockPinP, int clockPinM, int synPinP, int synPinM,
                 int xPinP, int xPinM, int yPinP, int yPinM) {
  _clock = new DifferentialWirePair(clockPinP, clockPinM);
  _syn = new DifferentialWirePair(synPinP, synPinM);
  _x = new DifferentialWirePair(xPinP, xPinM);
  _y = new DifferentialWirePair(yPinP, yPinM);
}

void XY2_100::tick() {
  _clock->set(1);
  _clock->set(0);
}
void XY2_100::_write(DifferentialWirePair *pair, int value) {
  // beign data frame
  _clock->set(1);
  _syn->set(1);
  // write [0, 0, 1] header
  // Data is valid on falling edge of clock
  // First 0
  pair->set(0);
  _clock->set(0);
  _clock->set(1);
  // Second 0
  pair->set(0);
  _clock->set(0);
  _clock->set(1);
  // First 1
  pair->set(1);
  _clock->set(0);
  _clock->set(1);
  // write data
  unsigned char even_parity_bit = 0;
  for (int i = 0; i < 16; i++) {
    unsigned char current_bit = (value >> (15 - i)) & 1;
    pair->set(current_bit);
    _clock->set(0);
    _clock->set(1);
    even_parity_bit ^= current_bit;
  }
  // write parity bit
  pair->set(even_parity_bit);
  _clock->set(0);
  _clock->set(1);
  // end data frame
  _syn->set(0);
}
void XY2_100::setX(int x) {
  _write(_x, x);
  _x_pos = x;
}
void XY2_100::setY(int y) {
  _write(_y, y);
  _y_pos = y;
}

/// @brief Sets the x and y position of the galvo *sequentially*
/// @param x
/// @param y
void XY2_100::setXY(int x, int y) {
  setX(x);
  setY(y);
}

void XY2_100::tickingDelay(unsigned long us) {
  unsigned long start = micros();
  while (micros() - start < us) {
    this->tick();
  }
}

void XY2_100::linearMove(DifferentialWirePair *pair, int start, int end,
                         unsigned long us) {
  unsigned long start_time = micros();
  unsigned long end_time = start_time + us;
  while (micros() < end_time) {
    unsigned long current_time = micros();
    int current_position =
        start + (end - start) * (current_time - start_time) / us;
    _write(pair, current_position);
  }
}

void XY2_100::rect(int x, int y, int w, int h) {
  linearMove(_x, x, x + w, 1000);
  linearMove(_y, y, y + h, 1000);
}