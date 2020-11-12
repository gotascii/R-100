#include <ROMSelector.h>

_ROMSelector::_ROMSelector() {
}

void _ROMSelector::begin(int p0, int p1, int p2, int p3) {
  this->p0 = p0;
  this->p1 = p1;
  this->p2 = p2;
  this->p3 = p3;

  pinMode(p0, OUTPUT);
  pinMode(p1, OUTPUT);
  pinMode(p2, OUTPUT);
  pinMode(p3, OUTPUT);

  select(0);
}

void _ROMSelector::select(byte index) {
  romAddress = romAddresses[index % 3];

  digitalWrite(p0, bitRead(romAddress, 3));
  digitalWrite(p1, bitRead(romAddress, 2));
  digitalWrite(p2, bitRead(romAddress, 1));
  digitalWrite(p3, bitRead(romAddress, 0));
}

_ROMSelector ROMSelector;
