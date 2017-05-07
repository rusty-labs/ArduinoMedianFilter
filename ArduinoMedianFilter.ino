#include "ArduinoMedianFilter.h"


// 100 - number of samples
// uint8_t - using type enough to store value of 100 (max is 255 for uint8_t)
// uint16_t - type of the output value and input samples
ArduinoMedianFilter<uint16_t, uint8_t, 100> medianFilter;

void setup() {
}

void loop() {

  for (uint8_t i = 0; i < 100; ++i) {
    medianFilter.add(analogRead(A0));
    delay(1);
  }

  uint16_t outputValue;
  medianFilter.getMedian(outputValue);

  Serial.println(outputValue);
}
