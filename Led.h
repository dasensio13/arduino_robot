#ifndef _LED_h
#define _LED_h

#include <Arduino.h>

class Led
{
  public:
    void Init(int pin); //pin al que está conectado el led
    void Encender() const;
    void Apagar() const;

  private:
    int _pin;
};

#endif
