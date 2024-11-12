#pragma once
#include "DifferentialWirePair.h"

#define K 1000
#define M K *K
#define G M *K

class XY2_100 {
private:
  DifferentialWirePair *_clock;
  DifferentialWirePair *_syn;
  DifferentialWirePair *_x;
  DifferentialWirePair *_y;
  unsigned long _max_speed = 2 * M; // 2 MHz (per protocol specification)
  unsigned long _max_tick_length_ns = 1 * G / (_max_speed * K);
  int _x_pos = 0;
  int _y_pos = 0;

  void _write(DifferentialWirePair *pair, int value);

public:
  XY2_100(int clockPinP, int clockPinM, int synPinP, int synPinM, int xPinP,
          int xPinM, int yPinP, int yPinM);

  void tick(); // we do it synchronously (for now)
  void setX(int x);
  void setY(int y);
  void setXY(int x, int y);
  void tickingDelay(unsigned long us);
  void linearMove(DifferentialWirePair *pair, int start, int end,
                  unsigned long us);
  void rect(int x, int y, int w, int h);
};