#include "Arduino.h"
#include "Battery.h"

Battery::Battery() {
	Battery(0);
}

Battery::Battery(int iPin) {
	// to be modified with each circuit
	float fVoltKnown = 12.6;
	float fAnalogValue = 1023.0;
	fRatio = fVoltKnown / fAnalogValue * 0.2;
	
	fBatteryVoltage = 0.0;
	
	iAnalogPin = 0; // battery connected to pin A0
}

// returns voltage of Lipo

float Battery::getLipoV() {
	// check battery only if already positionned
	// ratio : 80% previous value + 20% read value to limit variation
	if (fBatteryVoltage > 9.0) {
		fBatteryVoltage = fBatteryVoltage * 0.8 + analogRead(0) * fRatio;
		} else {
		fBatteryVoltage = 12.0;
	}
	return fBatteryVoltage;
}
