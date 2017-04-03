/*************************
   classe JlmThrottle
   octobre 2016
   gestion des poignées

 *************************/

#ifndef JlmThrottle_h
#define JlmThrottle_h

#include <Arduino.h>

class JlmThrottle
{
  public:

    JlmThrottle();// constructor
    ~JlmThrottle(); // destructeur

    bool directionAvant(); // direction avant
    bool directionArriere(); // direction arriere
    int poigneePuissance(); // poignee puissance
    int poigneeThrottle(); // poignee vitesse


  protected:

    bool m_initialized; // initialisation  au demarrage = false

    inline void init(); //initialisation

};

#endif
