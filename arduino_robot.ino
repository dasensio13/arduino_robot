#include "Motor.h"
#include "HCSR04.h"
#include "IRremote.h"
#include "Mando.h"
#include "Led.h"

int ULTRASONIDOS_ECHO = 2;
int LED2_PIN = 10;
int ULTRASONIDOS_TRIG = 11;
int MOTOR1_PIN = 12;
int MOTOR2_PIN = 13;

UltraSonicDistanceSensor distanceSensor(ULTRASONIDOS_TRIG, ULTRASONIDOS_ECHO);
Motor motor1;
Motor motor2;
Led led1;
Led led2;

int velocidad = 0;

void setup()
{
  Serial.begin(9600);
  led1.Init(LED_BUILTIN);
  led2.Init(LED2_PIN);
  motor1.Init(MOTOR1_PIN);
  motor2.Init(MOTOR2_PIN, true);
  MandoInit();
}

void loop()
{
  float distancia = distanceSensor.measureDistanceCm();
  Serial.print("Distancia: ");
  Serial.println(distancia);

  if (distancia == -1) {
    led2.Apagar();
    velocidad = 0;
  }
  else if (distancia > 0 && distancia < 20)
  {
    led2.Encender();
    velocidad = map(distancia, 0, 20, 0, 100);
  }
  else
  {
    led2.Apagar();
    char tecla = TeclaPulsada();
    if (tecla == '*')
    {
      led1.Encender();
    }
    else if (tecla == '#')
    {
      led1.Apagar();
    }
    else if (tecla == 'l')
    {
      led2.Apagar();
    }
    else if (tecla == 'r')
    {
      led2.Encender();
    }
    else if (tecla == 'u')
    {
      velocidad += 5;
    }
    else if (tecla == 'd')
    {
      velocidad -= 5;
    }
    else if (tecla == '0')
    {
      velocidad = 0;
    }
    else if (tecla == '9')
    {
      velocidad = 90;
    }
  }

  Serial.print("Velocidad: ");
  Serial.println(velocidad);
  motor1.Adelante(velocidad);
  motor2.Adelante(velocidad);
  delay(500);
}
