#include <SPI.h>
#include "pins_arduino.h"

unsigned long loggingTimestamp = 0;
unsigned long loggingIntervalMs = 300;

const int RESET = 9;
const int CS_FQ_UD = 10;
const int MOSI_DATA = 11;
const int SCK_W_CLK = 12;
const double CLKIN = 125000000;
SPISettings settings(4000000, LSBFIRST, SPI_MODE0);

void setup() {
  Serial.begin(57600);

  // Reset the AD9850 before going into SPI behavior
  pinMode(RESET, OUTPUT);
  pinMode(CS_FQ_UD, OUTPUT);
  pinMode(MOSI_DATA, OUTPUT);
  pinMode(SCK_W_CLK, OUTPUT);
  pulse(RESET);
  pulse(SCK_W_CLK);
  pulse(CS_FQ_UD);

  SPI.begin();
}

void loop() {
  //if (millis() - loggingTimestamp >= loggingIntervalMs) {
  //  loggingTimestamp += loggingIntervalMs;
  //  Serial.println(z);
  //}

  SPI.beginTransaction(settings);
  digitalWrite(CS_FQ_UD, LOW);
  
  // Need to construct the 40-bit shit
  // DATA = (2^32 * F) / CLKIN
  SPI.transfer(42);

  digitalWrite(CS_FQ_UD, HIGH);
  SPI.endTransaction();
  delay(1000);
}

void pulse(int pin) {
  digitalWrite(pin, HIGH);
  digitalWrite(pin, LOW);
}
