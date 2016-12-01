/**************************************************
github du 01 12 2016
    chariot jlm
    le 17 11 2016
    gestion d'un moteur avec la class ZumoMotors
    Utilisation du module YC-MD1301 350W
    P    D    M+   M-   motor status   note
    1    0    V+   G      forward     full speed
    0    1    G    V+     reverse     full speed
    0    0    Vcc  Vcc    free stop
    1    1    G    G      brake stop
    1   pwm  pwm   G      forward     pwm
    pwm  1    G    pwm    reverse     pwm

 **************************************************/

#include <SoftwareSerial.h>

#include "JlmMotor.h"
JlmMotor motor(1); // timer 1, broches 9 et 10

#include "JlmFan.h"
JlmFan fan(2, false, 3); // timer 2, broche de sortie PWM 3 ou 11 (timer 2)

#include "JlmThrottle.h"
JlmThrottle throttle;

#define LED_PIN 13 // led en broche 13

void setup ()
{
  pinMode(LED_PIN, OUTPUT); // led
  Serial.begin(9600);
  
  motor.config(20);
  motor.setBrakeStop(2000); // brake 2s
  fan.setVentilateurSpeed(0); // broche 3
}

void loop ()
{
  int speed(0); // speed
  int puissance(0);// puissance
  bool avant (true);
  int speedSav(400);// sauvegarde de la vitesse
  int const acceleration(3); // acceleration progressive de 0 à 20 environ

  do
  {
    avant = throttle.directionAvant(); // lecture de la direction avant
    if (avant && throttle.directionArriere()) { // avant et arriere à l'arret donc frein
      speedSav = 400;
      motor.setBrakeStop(2000); // brakes 2s
      fan.setVentilateurSpeed(0); // broche 3
    } else {
      puissance = throttle.poigneePuissance(); // lecture de la puissance
      if (avant) {
        /************************************************************************
           adaptation de la puissance en fonction de la marche avant ou arriere
           puissance minimum et puissance max pour la marche arriere
        *************************************************************************/
        // reglage de la puissace 0,88v / 4,22v vers 400 puissance min / 0 puissance max
        puissance = map(puissance, 180, 860, 300, 0); // 300 puissance minimum pour le bon fonctionnement du moteur
        if (puissance < 0) puissance = 0;
      } else {
        // reglage de la puissace 0,88v / 4,22v vers 400 puissance min / 0 puissance max
        puissance = map(puissance, 180, 860, 300, 200); // 300 puissance minimum et 200 pour la puissance maxi en marche arriere
        if (puissance < 0) puissance = 0;
      }
      // conversion tension 0,87v / 4,37v vers 0 puissance max / 400 puissance min
      speed = map(throttle.poigneeThrottle(), 178, 860, 400, puissance);
      if (speed < 0)  speed = 0; // Min PWM
      if (speed > 400)  speed = 400; // Max PWM dutycycle
      if (speed == 400 )
      {
        motor.setBrakeStop(100); // brakes 100ms
        fan.setVentilateurSpeed(0); // broche 3

      } else {
        /* le ventilateur est fonction de la vitesse des moteurs */
        fan.setVentilateurSpeed(map(speed, 400, 0 , 100, 255)); // broche 3
        if (speedSav > speed)
        {
          /* accélération progressive avant et arriere */
          if (avant)  motor.setForwardSpeed(speedSav, acceleration); else motor.setReverseSpeed(speedSav, acceleration);
          speedSav -= 1;  // accelération progressive
        } else {
          if (avant) motor.setForwardSpeed(speed); else motor.setReverseSpeed(speed);
          speedSav = speed;
        }
      }
    }
  }  while (1) ;
}

/*
  // Réglage de la fréquence PWM du Timer 1
  // vu sur : https://github.com/pololu/zumo-shield/blob/master/ZumoMotors/ZumoMotors.cpp

  int mypwm = 200; // réglage de test avec max = 400 ici

  void setup() {
  // PWM frequency calculation
  // 16MHz / 1 (prescaler) / 2 (phase-correct) / 400 (top) = 20kHz
  TCCR1A = 0b10100000;
  TCCR1B = 0b00010001;
  ICR1 = 400; // max
  }

  void loop() {
  OCR1B = mypwm; // 0-400
  }
*/

