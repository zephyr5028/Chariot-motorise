#include "JlmInitPWM.h"

#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__) || defined (__AVR_ATmega32U4__)
#define USE_20KHZ_PWM
#endif

// surcharge constructeur avec timer
JlmInitPWM::JlmInitPWM(byte timer)
{
  switch (timer) {
    case 1 : // timer1 sortie 8 et 10
      m_timer = 1;
      m_sortie1 = 9;
      m_sortie2 = 10;
      break;
    case 2 : // timer2 sortie 3 et 11
      m_timer = 2;
      m_sortie1 = 3;
      m_sortie2 = 11;
      break;
    default : // timer0 sortie 5 et 6
      m_timer = 0;
      m_sortie1 = 5;
      m_sortie2 = 6;
      break;
  }
}

// destrcuteur
JlmInitPWM::~JlmInitPWM()
{
}

//initialisation  au demarrage
void JlmInitPWM::config(byte vitesse)
{
  if (m_timer = 1 and vitesse == 20)  // timer 1 et vitesse 20khz
  {
#ifdef USE_20KHZ_PWM
    /****************************
       Timer 1 configuration
       prescaler: clockI/O / 1
       outputs enabled
       phase-correct PWM
       top of 400
    *****************************/

    // PWM frequency calculation
    // 16MHz / 1 (prescaler) / 2 (phase-correct) / 400 (top) = 20kHz
    TCCR1A = 0b10100000;
    TCCR1B = 0b00010001;
    ICR1 = 400;
#endif
  }
}

