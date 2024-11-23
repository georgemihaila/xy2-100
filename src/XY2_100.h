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
  unsigned int _setting_time_multiplier = 1;
  unsigned long _setting_time_us = 1000000 / (20 * 1000); // 20k pps max

  /// @brief Sets the x and y position of the galvo simultaneously; doing this
  /// sequentially results in the other axis going to 0
  /// @param x
  /// @param y
  void _write(int x, int y);

public:
  /// @brief Construct a new XY2_100 object.
  /// @param clockPinP Clock pin positive (+)
  /// @param clockPinM Clock pin negative (-)
  /// @param synPinP Sync pin positive (+)
  /// @param synPinM Sync pin negative (-)
  /// @param xPinP X pin positive (+)
  /// @param xPinM X pin negative (-)
  /// @param yPinP Y pin positive (+)
  /// @param yPinM Y pin negative (-)
  XY2_100(int clockPinP, int clockPinM, int synPinP, int synPinM, int xPinP,
          int xPinM, int yPinP, int yPinM);

  /// @brief Sends a clock tick.
  void tick();

  /// @brief Sets the x and y position of the galvo simultaneously. This cannot
  /// be done sequentially (at least for the RC1001) because whenever a packet
  /// is received, the galvo automatically assumes data for both axes is being
  /// sent. Not sending data for one axis will result in that axis going to 0
  /// (or max, depending on how the other pin is pulled).
  void setXY(int x, int y);

  /// @brief Same effect as delayMicroseconds, but ticks the device's clock.
  void tickingDelay(unsigned long us);
  /// @brief Depending on the capabilities of the device, wait for the mirror(s)
  /// to (allegedly) reach posiiton. The default value assumes a 20kpps device.
  void waitSettingTime();

  void rect(int x, int y, int w, int h);

  /// @brief Draws a circle (clockwise) with center at (x, y) and radius r, with
  /// n points
  void circleCW(int x, int y, int r, int n);

  /// @brief Draws a circle (counter-clockwise) with center at (x, y) and radius
  /// r, with n points
  void circleCCW(int x, int y, int r, int n);

  /// @brief Gets the current position of the X axis mirror
  int getX();

  /// @brief Gets the current position of the Y axis mirror
  int getY();
};