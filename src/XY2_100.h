#pragma once
#include "DifferentialWirePair.h"

class XY2_100 {
private:
  DifferentialWirePair *_clock;
  DifferentialWirePair *_syn;
  DifferentialWirePair *_x;
  DifferentialWirePair *_y;
  unsigned long _max_speed = 2 * 1000000; // 2 MHz (per protocol specification)
  unsigned long _max_tick_length_ns = 1000000000 / (_max_speed * 1000);
  int _x_pos = 0;
  int _y_pos = 0;
  unsigned int _setting_multiplier = 1;
  unsigned long _setting_time_us = 1000000 / (20 * 1000); // 20k pps max

  /// @brief Sets the x and y position of the galvo simultaneously; doing this
  /// sequentially results in the other axis going to 0
  /// @param x
  /// @param y
  void _write(int x, int y);

public:
  XY2_100(int clockPinP, int clockPinM, int synPinP, int synPinM, int xPinP,
          int xPinM, int yPinP, int yPinM);

  void tick(); // we do it synchronously (for now)
  void setXY(int x, int y);
  void tickingDelay(unsigned long us);
  /// @brief Depending on the capabilities of the device, wait for the mirror(s)
  /// to (allegedly) reach posiiton
  void waitSettingTime();
  void rect(int x, int y, int w, int h);
  /// @brief Draws a circle with center at (x, y) and radius r
  void circle(int x, int y, int r);

  /// @brief Draws a circle with center at (x, y) and radius r, with n points
  void circle(int x, int y, int r, int n);
};