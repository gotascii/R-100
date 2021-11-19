#include <MIDI.h>

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

const int PIN_D2 = 2;
const int PIN_D3 = 3;
const int PIN_D4 = 4;
const int PIN_D5 = 5;

unsigned long t = 0;
unsigned long binCounter = 0;

int romAddress;
int romAddresses[4] = {14, 13, 11, 7};

unsigned long loggingTimestamp = 0;
unsigned long loggingIntervalMs = 300;

void setup() {
  MIDI.begin(MIDI_CHANNEL_OMNI);
  Serial.begin(57600);
  Serial.println("MIDI Input Test");

  pinMode(PIN_D2, OUTPUT);
  pinMode(PIN_D3, OUTPUT);
  pinMode(PIN_D4, OUTPUT);
  pinMode(PIN_D5, OUTPUT);

  digitalWrite(PIN_D2, 1);
  digitalWrite(PIN_D3, 1);
  digitalWrite(PIN_D4, 0);
  digitalWrite(PIN_D5, 1);
}

void loop() {
  int note, velocity, channel, d1, d2;
  if (MIDI.read()) {                    // Is there a MIDI message incoming ?
    byte type = MIDI.getType();
    switch (type) {
      case midi::NoteOn:
        note = MIDI.getData1();
        velocity = MIDI.getData2();
        channel = MIDI.getChannel();
        if (velocity > 0) {
          //Serial.println(String("Note On:  ch=") + channel + ", note=" + note + ", velocity=" + velocity);
        } else {
          //Serial.println(String("Note Off: ch=") + channel + ", note=" + note);
        }
        break;
      case midi::NoteOff:
        note = MIDI.getData1();
        velocity = MIDI.getData2();
        channel = MIDI.getChannel();
        //Serial.println(String("Note Off: ch=") + channel + ", note=" + note + ", velocity=" + velocity);
        break;
      default:
        d1 = MIDI.getData1();
        d2 = MIDI.getData2();
        //Serial.println(String("Message, type=") + type + ", data = " + d1 + " " + d2);
    }
    t = millis();
  }
  if (millis() - t > 10000) {
    t += 10000;
    Serial.println("(inactivity)");

    romAddress = romAddresses[binCounter];

    //    Serial.print(bitRead(romAddress, 3));
    //    Serial.print(bitRead(romAddress, 2));
    //    Serial.print(bitRead(romAddress, 1));
    //    Serial.println(bitRead(romAddress, 0));

    //    digitalWrite(PIN_D2, bitRead(romAddress, 3));
    //    digitalWrite(PIN_D3, bitRead(romAddress, 2));
    //    digitalWrite(PIN_D4, bitRead(romAddress, 1));
    //    digitalWrite(PIN_D5, bitRead(romAddress, 0));

    binCounter = binCounter + 1;
    binCounter = binCounter % 3;
  }
}
