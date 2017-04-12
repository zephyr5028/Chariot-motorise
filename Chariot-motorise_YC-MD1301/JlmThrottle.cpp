#include "JlmThrottle.h"

#define THROTTLE A2 // throttle en broche analogique A2
#define PUISSANCE A3 // reglage de la puissance de sortie A3
#define AVANT 6 // avant entrée D6
#define ARRIERE 5 // arrière entré D5

// constructor
JlmThrottle::JlmThrottle() :  m_initialized(false)
{
}

//destructor
JlmThrottle::~JlmThrottle()
{
}

// initialize  entrées
void JlmThrottle::init()
{
  if (!m_initialized)
  {
    m_initialized = true;
    pinMode(AVANT, INPUT_PULLUP); // avec pull-up
    pinMode(ARRIERE, INPUT_PULLUP); // avec pull-up
  }
}

// direction avant
bool JlmThrottle::directionAvant()
{
  init(); // initialize if necessary
  bool avant (true);
  avant = digitalRead(AVANT); // lecture de la direction avant
  return avant;
}

// direction arriere
bool JlmThrottle::directionArriere()
{
  init(); // initialize if necessary
  bool arriere (true);
  arriere = digitalRead(ARRIERE); // lecture de la direction arriere
  return arriere;
}

// poignee puissance
int JlmThrottle::poigneePuissance()
{
  init(); // initialize if necessary
  int puissance(0);// puissance
  puissance = analogRead(PUISSANCE); // lecture de la puissance
  return puissance;
}

// poignee vitesse
int JlmThrottle::poigneeThrottle()
{
  init(); // initialize if necessary
  int poignee(0);// poignee vitesse
  poignee = analogRead(THROTTLE); // lecture de la poignee vitesse
  return poignee;
}


