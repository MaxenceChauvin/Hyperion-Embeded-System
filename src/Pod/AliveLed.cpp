#include "Arduino.h"
#include "AliveLed.h"

// init onboard LED for alive status cf alive()

AliveLed::AliveLed() {
	AliveLed(13);
}

AliveLed::AliveLed(int iLed) {
	iPinId = iLed;
	iDelay = 1000; // in ms

}

void AliveLed::attach() {
    pinMode(iPinId, OUTPUT);
}

void AliveLed::blink() {
	// we are alive
	digitalWrite(iPinId, HIGH);   // turn the LED on (HIGH is the voltage level)
	delay(iDelay);
	digitalWrite(iPinId, LOW);    // turn the LED off by making the voltage LOW
}
