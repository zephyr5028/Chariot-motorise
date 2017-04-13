/**************************************************
    github du 01 12 2016
    chariot jlm
    le 17 11 2016
    gestion d'un moteur 250W
    Utilisation du module IBT_2 43A BTN7960
    1    RPWM    forward level or PWM signal input, active high
    2    LPWM    inversion level or PWM signal input, active high
    3    R_EN    forward drive enable input, high enable, low close
    4    L_EN    reverse drive enable input, high enable, low close
    5    R_IS    forwarde drive, -side current alarm output
    6    L_IS    reverse drive -side current alarm output
    7    VCC     5v power input, connected to the microcontroller 5v power supply
    8    GND     signal common ground terminal

    usage :
    VCC             5v microcontroller
    GND             GNG microcontroller
    R_EN et L_EN    5V level, the drive work
    L_PWM           input PWM signal, forward
    R_PWM           input PWM signal, reverse

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
  motor.setFreeStop(2000); // stop 2s, état 0 pour IBT_2  L_PWM et R_PWM
  fan.setVentilateurSpeed(0); // broche 3
}

void loop ()
{
  int speed(0); // speed
  int puissance(0);// puissance
  int poignee(0); // poignée
  bool avant (true);
  int speedSav(0);// sauvegarde de la vitesse
  int const acceleration(1); // acceleration progressive de 0 à 20 environ

  do
  {
    avant = throttle.directionAvant(); // lecture de la direction avant
    if (avant && throttle.directionArriere()) { // avant et arriere à l'arret donc frein
      speedSav = 0; // stop
      motor.setFreeStop(2000); // stop 2s, état 0  pour IBT_2   L_PWM et R_PWM
      fan.setVentilateurSpeed(0); // broche 3
    } else {
      puissance = throttle.poigneePuissance(); // lecture de la puissance
      if (avant) {
        /************************************************************************
           adaptation de la puissance en fonction de la marche avant ou arriere
           puissance minimum et puissance max pour la marche arriere
        *************************************************************************/
        // reglage de la puissace 0,88v / 4,22v vers 0 puissance min / 400 puissance max
        puissance = map(puissance, 180, 860, 200, 0); // 200 puissance maxi pour le bon fonctionnement du moteur et vitesse trop élevée si plus en marche avant
        if (puissance < 0) puissance = 0;
      } else {
        // reglage de la puissace 0,88v / 4,22v vers 400 puissance min / 0 puissance max
        puissance = map(puissance, 180, 860, 180, 0); // 100 puissance maxi pour le bon fonctionnement du moteur et vitesse trop élevée si plus em marche arrière
        if (puissance < 0) puissance = 0;
      }
      // conversion tension 0,87v / 4,37v vers 0 puissance min / 400 puissance max
      poignee =  map(throttle.poigneeThrottle(), 178, 860, 0, 30);
      speed = puissance;
      if (speed > 0 ) {
        speed = puissance + poignee;
      }
      if (speed < 0)  speed = 0; // Min PWM
      if (speed > 400)  speed = 400; // Max PWM dutycycle
      if (speed == 0 )
      {
        // motor.setBrakeStop(100); // brakes 100ms
        motor.setFreeStop(100); // stop 100ms
        fan.setVentilateurSpeed(0); // broche 3

      } else {
        /* le ventilateur est fonction de la vitesse des moteurs */
        fan.setVentilateurSpeed(map(speed, 0, 400 , 100, 255)); // broche 3
        if (speedSav < speed)
        {
          /* accélération progressive avant et arriere */
          if (avant)  motor.setForwardSpeed(speedSav, acceleration); else motor.setReverseSpeed(speedSav, acceleration);
          speedSav += 1;  // accelération progressive
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

