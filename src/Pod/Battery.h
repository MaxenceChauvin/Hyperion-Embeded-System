#ifndef Battery_h
#define Battery_h
	
#include "Arduino.h"
	
class Battery {
	public:
		Battery();
		Battery(int);
		float getLipoV();
		
	private:
		float fRatio;
		float fBatteryVoltage;
		int iAnalogPin;
};
	
#endif
