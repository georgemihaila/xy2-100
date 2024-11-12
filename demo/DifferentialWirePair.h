#pragma once

class DifferentialWirePair {
private:
  unsigned char _curent_state;
  int _pinP; // positive
  int _pinM; // negative

public:
  DifferentialWirePair(int _pinP, int _pinM);
  void set(unsigned char state);
  void invert();
};