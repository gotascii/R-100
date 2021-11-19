#ifndef AD9850_H
#define AD9850_H
#include <Arduino.h>

class AD9850
{
  public:
    AD9850();

  void begin(int w_clk, int fq_ud, int data, int reset);
  void setfreq(double f, uint8_t p);
  void down();
  void up();
  void calibrate(double TrimFreq);
  
  private:
  int W_CLK;
  int FQ_UD;
  int DATA;
  int RESET;
  uint32_t deltaphase;
  uint8_t phase;
  void update();
  void begin_priv();
  void pulse(int pin);
  double calibFreq;
};

extern AD9850 DDS;

#endif
