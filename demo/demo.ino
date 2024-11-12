
#include "XY2_100.h"

// for demo purposes, other people's wiring may be different
// the order DOES matter, the colored wires are positive (+) and the white wires
// are negative (-)

// #define default_clock D8, D7 // Blue + white
#define default_clock 15, 13 // Blue + white
// #define default_syn D1, D2   // Orange + white
#define default_syn 5, 4 // Orange + white
// #define default_x D6, D0     // Brown + white
#define default_x 12, 16 // Brown + white
// #define default_y D5, D3     // Green + white
#define default_y 14, 0 // Green + white
#define default_pins default_clock, default_syn, default_x, default_y

XY2_100 *galvo;

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println("\nGalvo up");
  galvo = new XY2_100(default_pins);
  Serial.println("Galvo ready");
  delay(500);
}

void manyIncreasingSizeRects() {
  for (int i = 0; i < 1000; i++) {
    galvo->rect(100, 100, i, i);
  }
  for (int i = 1000; i > 0; i--) {
    galvo->rect(100, 100, i, i);
  }
}

void loop() {
  manyIncreasingSizeRects();
  galvo->tickingDelay(500 * 1000);
}
