#include "JlmMotor.h"

// constructor
JlmMotor::JlmMotor(byte timer) : JlmInitPWM(timer),  m_initialized(false), m_PWM_R(m_sortie1), m_PWM_L(m_sortie2)
{
}

JlmMotor::~JlmMotor()
{
}

//initialisation timer1 au demarrage
inline void JlmMotor::init()
{
  if (!m_initialized)
  {
    m_initialized = true;

    pinMode(m_PWM_R,  OUTPUT);
    pinMode(m_PWM_L,  OUTPUT);
  }
}

// set speed forward motor; speed is a number between -400 and 400
void JlmMotor::setForwardSpeed(int speed, int const acceleration)
{
  init(); // initialize if necessary
  if (speed < 0)  speed = 0;
  if (speed > 400)   speed = 400;

#ifdef USE_20KHZ_PWM
  OCR1B = speed;
#else
  analogWrite(m_PWM_L, speed * 51 / 80); // default to using analogWrite, mapping 400 to 255
#endif
  delay (acceleration); // accélération
}

// set speed reverse motor; speed is a number between -400 and 400
void JlmMotor::setReverseSpeed(int speed, int const acceleration)
{
  init(); // initialize if necessary
  if (speed < 0)  speed = 0; // Min PWM
  if (speed > 400)  speed = 400; // Max PWM dutycycle

#ifdef USE_20KHZ_PWM
  OCR1A = speed;
#else
  analogWrite(m_PWM_R, speed * 51 / 80); // default to using analogWrite, mapping 400 to 255
#endif
  delay (acceleration); // accélération
}

// brake stop avec delais  mini de 100ms
void JlmMotor::setBrakeStop(int  delais)
{
  int brakeStop(400); // sortie brake stop donc 1
  setForwardSpeed(brakeStop);  // run forward motor - broche 10
  setReverseSpeed(brakeStop); // run reverse motor - broche 9
  if (delais < 100) delais = 100;
  delay(delais);
}

// free stop avec delais  mini de 100ms
void JlmMotor::setFreeStop(int  delais)
{
  int freeStop(0); // sortie free stop donc 0
  setForwardSpeed(freeStop);  // run forward motor - broche 10
  setReverseSpeed(freeStop); // run reverse motor - broche 9
  if (delais < 100) delais = 100;
  delay(delais);
}


