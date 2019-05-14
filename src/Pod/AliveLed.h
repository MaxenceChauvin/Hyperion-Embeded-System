#ifndef AliveLed_h
#define AliveLed_h

#include "Arduino.h"

class AliveLed {
  public:
    AliveLed();
    AliveLed(int);
    void blink();
    void attach();

   private:
     int iPinId;
	 int iDelay;
};

#endif
