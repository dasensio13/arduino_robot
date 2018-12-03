#include "Motor.h"
#include <Servo.h>
#include <Arduino.h>

int ANGULO_MIN = 0;
int ANGULO_MAX = 180;
int ANGULO_STOP = 90;

int VELOCIDAD_MAX = 100;
int VELOCIDAD_MIN = 0;

int velocidadToAngulo(int velocidad) {
  return map(velocidad, VELOCIDAD_MIN, VELOCIDAD_MAX, ANGULO_MIN, ANGULO_STOP);
}

void Motor::Init(int pin)
{
  this->_servo.attach(pin);
  this->_invertido = false;
}

void Motor::Init(int pin, bool invertido)
{
  this->_servo.attach(pin);
  this->_invertido = invertido;
}

void Motor::Parar() const
{
  _servo.write(ANGULO_STOP);
}

void Motor::AdelanteDirecto(int velocidad) const
{
  if (velocidad >= VELOCIDAD_MIN and velocidad <= VELOCIDAD_MAX) {
    _servo.write(ANGULO_STOP + velocidadToAngulo(velocidad));
  } else {
    Parar();
  }
}

void Motor::Adelante() const
{
  Adelante(VELOCIDAD_MAX);
}

void Motor::Adelante(int velocidad) const
{
  if (_invertido) {
    AtrasDirecto(velocidad);
  } else {
    AdelanteDirecto(velocidad);
  }
}

void Motor::AtrasDirecto(int velocidad) const
{
  if (velocidad >= VELOCIDAD_MIN and velocidad <= VELOCIDAD_MAX) {
    _servo.write(ANGULO_STOP - velocidadToAngulo(velocidad));
  } else {
    Parar();
  }
}

void Motor::Atras() const
{
  Atras(VELOCIDAD_MAX);
}

void Motor::Atras(int velocidad) const
{
  if (_invertido) {
    AdelanteDirecto(velocidad);
  } else {
    AtrasDirecto(velocidad);
  }
}
