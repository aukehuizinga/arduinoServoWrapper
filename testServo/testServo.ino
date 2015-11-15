#include <Servo.h>
#include <arduino.h>
#include "signal.h"
#include <inttypes.h>

Signal main_signal=Signal(1000,1750,2,10,9);
Servo servo;

void setup() {
  Serial.begin(115200);
  main_signal.init();
  main_signal.toMaxPos();
}

void loop() {
  uint64_t now=millis();
  main_signal.update(now);
}
