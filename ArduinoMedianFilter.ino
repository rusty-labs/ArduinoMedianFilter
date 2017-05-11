#include "ArduinoMedianFilter.h"


// 200 - number of samples
// uint16_t - type of the output value and input samples
ArduinoMedianFilter<uint16_t, 200> medianFilter;

void setup() {
  Serial.begin(9600);
}

void loop() {

  for (uint8_t i = 0; i < 200; ++i) {
    medianFilter.set(i, analogRead(A0));
    delay(1);
  }

  uint16_t outputValue;
  medianFilter.getMedian(outputValue);

  Serial.println(outputValue);
}
