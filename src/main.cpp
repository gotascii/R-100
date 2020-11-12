#include <MIDI.h>
#include <AD9850.h>
#include <Ramp.h>
#include <ROMSelector.h>

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

// unsigned long loggingTimestamp = 0;
// unsigned long loggingIntervalMs = 300;

// rampFloat myRamp;
// float rampValue;

const double TWELVE_TET = 1.059463094359295L;
const uint32_t C_FREQ = 5000000;
const uint32_t C_MAX_FREQ = 20000000;
const uint8_t C_MIDI_NOTE = 60;

// C5 72 10000000
// C4 60 5000000
// C3 48 2500000
// C2 36 1250000
// C1 24  625000
// C0 12  312500
void handleNoteOn(byte channel, byte note, byte velocity) {
  if (channel == 2) {
    double freq = pow(TWELVE_TET, (note - C_MIDI_NOTE));
    freq = constrain(C_FREQ * freq, uint32_t(0), C_MAX_FREQ);
    DDS.setFreq(freq);
  }
}

void handleControlChange(byte channel, byte number, byte value) {
  if (number == 1) {
    ROMSelector.select(value);
  }
}

void setup() {
  Serial.begin(57600);
  ROMSelector.begin(20, 21, 22, 23);
  DDS.begin(C_FREQ, 9, 10, 13);
  MIDI.begin(2);

  MIDI.setHandleControlChange(handleControlChange);
  MIDI.setHandleNoteOn(handleNoteOn);

  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);

  // myRamp.go(1.0, 5000, SINUSOIDAL_INOUT, FORTHANDBACK);
}

void loop() {
  MIDI.read();

  //if (millis() - loggingTimestamp >= loggingIntervalMs) {
  //  loggingTimestamp += loggingIntervalMs;
  //  Serial.println(z);
  //}

  // rampValue = myRamp.update();
  // uint32_t freq = 1000000 + (8000000 * rampValue);
  // DDS.setFreq(freq);
}
