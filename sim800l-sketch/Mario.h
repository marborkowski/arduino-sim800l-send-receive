#ifndef Mario_h
#define Mario_h
#include "Arduino.h"

class Mario
{
  public:
    Mario(int pin);
    void play();
    void buzz(int targetPin, long frequency, long length);
    void sing(int index);
  private:
    int _pin;
};

#endif
