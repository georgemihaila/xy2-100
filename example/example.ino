#include "XY2_100.h"

// for demo purposes, other people's wiring may be different
// the order DOES matter, the colored wires are positive (+) and the white wires
// are negative (-)

#define default_clock 3, 4 // Blue + white
#define default_syn 7, 8   // Orange + white
#define default_x 5, 6     // Brown + white
#define default_y 10, 9    // Green + white
#define default_pins default_clock, default_syn, default_x, default_y

XY2_100 *galvo;

void setup() {
  galvo = new XY2_100(default_pins);
}

void loop() {
  for (int i = 300; i < 1000; i += 250) {
    galvo->circleCW(1000, 1000, i, 360 * 4);
    galvo->rect(1000, 1000, i, i * 4);
    galvo->tickingDelay(100000);
    galvo->circleCCW(1000, 1000, i, 360 * 4);
    galvo->rect(1000, 1000, i, i * 4);
    galvo->tickingDelay(500000);
  }
}
