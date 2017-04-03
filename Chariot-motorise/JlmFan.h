/*****************

   classe jlmFan
   11 2016

 *****************/

#ifndef JlmFan_h
#define JlmFan_h

#include <SoftwareSerial.h>
#include <Arduino.h>
#include "JlmInitPWM.h"

class JlmFan : public JlmInitPWM
{
  public:

    JlmFan(byte timer , byte fan); // surchage du contructeur avec timer, broche de sortie PWM 3 ou 11 (timer 2)
    JlmFan(byte timer,  bool debug, byte fan); // surcharge du constructeur avec timer, debug et la broche de sortie

    ~JlmFan();// destructor

    void setVentilateurSpeed(int speed);// set speed

  protected:

    bool m_debug; // debug
    bool m_initialized; // initialisation au demarrage = false
    byte m_fan; // broche de sortie PWM D3 ou D11 (timer2)

    inline void init(); //initialisation timer2 au demarrage

};

#endif
