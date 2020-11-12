#ifndef ROMSelector_h
#define ROMSelector_h

#include <Arduino.h>

class _ROMSelector {
  public:
  _ROMSelector();

  void begin(int p0, int p1, int p2, int p3);
  void select(byte index);

  private:
  int p0, p1, p2, p3;
  int romAddress;
  int romAddresses[4] = {14, 13, 11, 7};
};

extern _ROMSelector ROMSelector;

#endif
