#include "Led.h"
#include <Arduino.h>

void Led::Init(int pin)
{
  Serial.begin(9600);
  this->_pin = pin;
  pinMode(pin, OUTPUT);
  this->Apagar();
}

void Led::Encender() const
{
  Serial.print("Encender: ");
  Serial.println(_pin);
  digitalWrite(_pin, HIGH);
}

void Led::Apagar() const
{
  Serial.print("Apagar: ");
  Serial.println(_pin);
  digitalWrite(_pin, LOW);
}
