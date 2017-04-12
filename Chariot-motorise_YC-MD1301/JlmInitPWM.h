/*********************************

   classe JlmInitPWM

   pour arduino uno et nano

   11 2016

 *********************************/

#ifndef JlmInitPWM_h
#define JlmInitPWM_h

#include <Arduino.h>

class JlmInitPWM
{
  public:

    JlmInitPWM(byte timer) ; // surcharge constructeur avec n° timer de 0 à 2

    ~JlmInitPWM(); // destructeur

    void config(byte vitese = 0); // initialisation avec choix vitesse PWM o pour systeme et 20 pour 20khz


  protected:

    byte m_timer; // n° timer
    byte m_sortie1; // sortie PWM en focntion du timer
    byte m_sortie2; // sortie PWM en focntion du timer
    byte m_vitesse; // vitesse PWM

};

#endif
