#include "XY2_100.h"
#include <Arduino.h>

XY2_100::XY2_100(int clockPinP, int clockPinM, int synPinP, int synPinM,
                 int xPinP, int xPinM, int yPinP, int yPinM) {
  _clock = new DifferentialWirePair(clockPinP, clockPinM);
  _syn = new DifferentialWirePair(synPinP, synPinM);
  _x = new DifferentialWirePair(xPinP, xPinM);
  _y = new DifferentialWirePair(yPinP, yPinM);
  _setting_time_us *= _setting_multiplier;
}

void XY2_100::tick() {
  _clock->set(1);
  _clock->set(0);
}

void XY2_100::tickingDelay(unsigned long us) {
  unsigned long start = micros();
  while (micros() - start < us) {
    this->tick();
  }
}

void XY2_100::waitSettingTime() { tickingDelay(_setting_time_us); }

void XY2_100::_write(int x, int y) {
  // beign data frame
  _clock->set(1);
  _syn->set(1);
  // write [0, 0, 1] header
  // Data is valid on falling edge of clock
  // First 0
  _x->set(0);
  _y->set(0);
  _clock->set(0);
  _clock->set(1);
  // Second 0
  _x->set(0);
  _y->set(0);
  _clock->set(0);
  _clock->set(1);
  // First 1
  _x->set(1);
  _y->set(1);
  _clock->set(0);
  _clock->set(1);
  // write data
  unsigned char even_parity_bit_x = 0;
  unsigned char even_parity_bit_y = 0;
  for (int i = 0; i < 16; i++) {
    unsigned char current_bit_x = (x >> (15 - i)) & 1;
    unsigned char current_bit_y = (y >> (15 - i)) & 1;

    _x->set(current_bit_x);
    _y->set(current_bit_y);

    _clock->set(0);
    _clock->set(1);

    even_parity_bit_x ^= current_bit_x;
    even_parity_bit_y ^= current_bit_y;
  }
  // write parity bit
  _x->set(even_parity_bit_x);
  _y->set(even_parity_bit_y);
  _clock->set(0);
  _clock->set(1);
  // end data frame
  _syn->set(0);
}

/// @brief Sets the x and y position of the galvo *sequentially*
/// @param x
/// @param y
void XY2_100::setXY(int x, int y) {
  _write(x, y);
  _x_pos = x;
  _y_pos = y;
  waitSettingTime();
}

void XY2_100::rect(int x, int y, int w, int h) {
  for (int i = 0; i < w; i++) {
    setXY(x + i, y);
  }
  for (int i = 0; i < h; i++) {
    setXY(x + w, y + i);
  }
  for (int i = 0; i < w; i++) {
    setXY(x + w - i, y + h);
  }
  for (int i = 0; i < h; i++) {
    setXY(x, y + h - i);
  }
}

void XY2_100::circle(int x, int y, int r) { circle(x, y, r, 720); }

void XY2_100::circle(int x, int y, int r, int n) {
  for (int i = 0; i < n; i++) {
    setXY(x + r * cos(2 * PI * i / n), y + r * sin(2 * PI * i / n));
  }
}