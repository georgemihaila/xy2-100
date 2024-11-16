#include "XY2_100.h"

// for demo purposes, other people's wiring may be different
// the order DOES matter, the colored wires are positive (+) and the white wires
// are negative (-)

#define default_clock 3, 4 // Blue + white
#define default_syn 7, 8   // Orange + white
#define default_x 5, 6     // Brown + white
#define default_y 10, 9    // Green + white
#define default_pins default_clock, default_syn, default_x, default_y

#define laser_pin 10

XY2_100 *galvo;

/// Returns a number between 0 and 1 representing the laser's max ON ratio. This
/// number is calculated based on the user's potentiometer input
double pwm_ratio() {

  // y: [816-883] => [0,1]
  int y = round(analogRead(A0));
  double a1 = ((double)883 - y) / (883 - 816);
  double a2 = pow(a1, 8 - a1);
  if (a2 < 0.01) {
    a2 *= 10;
  } else if (a2 > 0.7) {
    a2 += ((pow(2.71, a2)) - 1) / 10;
  }
  return a2 > 1 ? 1 : a2;
}

bool is_laser_on = false;

void recalculate_laser_pwm() {
  if (!is_laser_on)
    return;
  // pwm_set_chan_level(laser_slice, PWM_CHAN_A, UINT16_T_MAX * pwm_ratio());
  analogWrite(laser_pin, pwm_max_unsafe * pwm_ratio());
}

void laser_on() {
  is_laser_on = true;
  recalculate_laser_pwm();
}

void laser_off() {
  analogWrite(laser_pin, 0);
  is_laser_on = false;
}

void pico_init_laser_pwm() {
  pinMode(laser_pin, OUTPUT);
  laser_off();
}

void setup() {
  delay(1000);
  Serial.begin(9600);
  galvo = new XY2_100(default_pins);
  pico_init_laser_pwm();
  delay(500);

  pinMode(0, OUTPUT);
  digitalWrite(0, HIGH);
  Serial.println("Galvo ready");
}

void expose() {
  laser_on();
  galvo->tickingDelay(10000); // 10ms/pixel exposure time; equivalent to 5mJ/px
                              // with a 500mW laser
  laser_off();
}

void rect(int x, int y, int w, int h) {
  for (int i = 0; i < w; i++, expose()) {
    galvo->setXY(x + i, y);
  }
  for (int i = 0; i < h; i++, expose()) {
    galvo->setXY(x + w, y + i);
  }
  for (int i = 0; i < w; i++, expose()) {
    galvo->setXY(x + w - i, y + h);
  }
  for (int i = 0; i < h; i++, expose()) {
    galvo->setXY(x, y + h - i);
  }
}

void manyIncreasingSizeRects() {
  for (int i = 0; i < 1000; i += 10) {
    rect(1000, 1000, i, 2 * i);
    galvo->tickingDelay(250 * 1000);
  }
  for (int i = 1000; i > 0; i -= 10) {
    rect(1000, 1000, 2 * i, i);
    galvo->tickingDelay(250 * 1000);
  }
}

void loop2() {
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
  delay(1000);
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  delay(1000);
}

void loop() {
  for (int i = 300; i < 1000; i += 100) {
    galvo->circle(1000, 1000, i, 360 * 4);
    galvo->tickingDelay(500000);
  }
}
