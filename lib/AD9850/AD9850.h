#ifndef AD9850_H
#define AD9850_H

#include <Arduino.h>
#include <SPI.h>

class AD9850
{
  public:
  AD9850();

  void begin(int freq, int resetPin, int fqUdPin, int wClkPin);
  void setFreq(double frequency);
  void calibrate(double frequency);

  private:
  const double POW_2_32 = 4294967296.0;
  const double CLKIN = 125000000.0;
  const uint8_t PHASE = 0;
  const long SPI_SPEED = 8000000;

  int resetPin, fqUdPin, wClkPin;
  uint32_t data;
  SPISettings settings;

  void pulse(int pin);
};

extern AD9850 DDS;

#endif
