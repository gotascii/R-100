#include <AD9850.h>

AD9850 DDS;

AD9850::AD9850() {
}

void AD9850::begin(int freq, int resetPin, int fqUdPin, int wClkPin) {
  this->resetPin = resetPin;
  this->wClkPin = wClkPin;
  this->fqUdPin = fqUdPin;

	pinMode(resetPin, OUTPUT);
	pinMode(wClkPin, OUTPUT);
	pinMode(fqUdPin, OUTPUT);

	pulse(resetPin);
  pulse(wClkPin);
	pulse(fqUdPin);

  settings = SPISettings(SPI_SPEED, LSBFIRST, SPI_MODE0);
	SPI.begin();

  setFreq(freq);
}

// Need to construct the 40-bit shit
// DATA = (2^32 * F) / CLKIN

// uint8_t transfer(uint8_t data)
// transfer sends a byte at a time
// so there will be 5 transfer calls

// uint32_t test = 5000000; // 10011000100101101000000
// test >>= 8;              // 00000000100110001001011 19531
// test & 0xFF;             //                01001011 75
void AD9850::setFreq(double frequency) {
	SPI.beginTransaction(settings);

  data = (POW_2_32 * frequency) / CLKIN;
  for (int i = 0; i < 4; i++, data >>= 8) {
    SPI.transfer(data & 0xFF);
  }
  SPI.transfer(PHASE);

  pulse(fqUdPin);
  SPI.endTransaction();
}

// void AD9850::calibrate(double frequency)
// {
// 	calibrationFreq = frequency;
// }

void AD9850::pulse(int pin) {
	digitalWrite(pin, HIGH);
	digitalWrite(pin, LOW);
}
