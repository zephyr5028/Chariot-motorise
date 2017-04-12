/*********************************

   classe jlmMotor
   classe dérivée de ZumoMotors
   11 2016

 *********************************/

#ifndef JlmMotor_h
#define JlmMotor_h

#include <Arduino.h>
#include "JlmInitPWM.h"

class JlmMotor : public JlmInitPWM
{
  public:

    JlmMotor(byte timer); // surchage du contructor avec le n° du timer pour la classe JlmInitPWM
    ~JlmMotor(); // destructeur

    void setForwardSpeed(int speed, int const acceleration = 0); // set speed for forward avec acceleration
    void setReverseSpeed(int speed, int const acceleration = 0); // set speed for reverse avec acceleration
    void setBrakeStop(int  delais = 100); // brake stop avec delais avec mini de 100ms
    void setFreeStop(int  delais = 100); // free stop avec delais avec mini de 100ms

  protected:

    bool m_initialized; // initialisation du timer1 au demarrage = false
    byte m_PWM_R ; // sortie 9 PWM Timer 1
    byte m_PWM_L ; // sortie 10 PWM Timer 1

    inline void init(); //initialisation  au demarrage
   
};

#endif
