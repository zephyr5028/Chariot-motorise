#include "JlmFan.h"

// constructor avec timer,  broche de sortie PWM 3 ou 11 (timer 2)
JlmFan::JlmFan(byte timer, byte fan) : JlmInitPWM(timer), m_debug(false), m_initialized(false)
{
  switch (fan) {
    case 5 : //  sortie 5
      m_fan = m_sortie1 ;
      break;
    case 6 : // sortie 6
      m_fan = m_sortie2;
      break;
    case 3 : // sortie 3
      m_fan = m_sortie1;
      break;
    case 11 : //  sortie 11
      m_fan = m_sortie2 ;
      break;
    case 9 : // sortie 9
      m_fan = m_sortie1;
      break;
    case 10 : // sortie 10
      m_fan = m_sortie2;
      break;
    default :
      m_fan = m_sortie1;
      break;
  }
}

// constructor avec timer, debug et broche de sortie PWM 3 ou 11 (timer 2)
JlmFan::JlmFan(byte timer, bool debug, byte fan) : JlmInitPWM(timer), m_debug(debug), m_initialized(false)
{
  switch (fan) {
    case 5 : //  sortie 5
      m_fan = m_sortie1 ;
      break;
    case 6 : // sortie 6
      m_fan = m_sortie2;
      break;
    case 3 : // sortie 3
      m_fan = m_sortie1;
      break;
    case 11 : //  sortie 11
      m_fan = m_sortie2 ;
      break;
    case 9 : // sortie 9
      m_fan = m_sortie1;
      break;
    case 10 : // sortie 10
      m_fan = m_sortie2;
      break;
    default :
      m_fan = m_sortie1;
      break;
  }
}

//destructor
JlmFan::~JlmFan()
{
}

//initialisation timer2 au demarrage
inline void JlmFan::init()
{
  if (!m_initialized)
  {
    m_initialized = true;
    pinMode(m_fan,  OUTPUT);
  }
}

// set speed ventilateur 0 to 255
void JlmFan::setVentilateurSpeed(int speed)
{
  init(); // initialize if necessary
  analogWrite(m_fan, speed);

  if (m_debug) {
    Serial.print("speed ventilateur  = ");
    Serial.println(speed);
  }
}

