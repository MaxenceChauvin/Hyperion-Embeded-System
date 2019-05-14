#include "AliveLed.h"
#include "Battery.h"
#include "AccGyro.h"

long timeLastIter = 0;

AliveLed aliveLed(13);
AccGyro accGyro;

void setup(){
    Serial.begin(9600);

    aliveLed.attach();

    accGyro.initState();

    timeLastIter = millis();
}

void loop(){
    accGyro.getSpeed(timeLastIter);
    accGyro.getPosition(timeLastIter);
    Serial.print(accGyro.getSpeedX());
    Serial.print(" | ");
    Serial.println(accGyro.getPosX());

    aliveLed.blink();

    temp = getTemp();
    Serial.println(temp);

    timeLastIter = millis();
}

float getTemp(){
    /* Fonction qui retourne la Temperature
       Entree : none
       Sortie : température
    */
    float temp = 0,1*(((1023 - analogRead(A0)) * 0.23) -50.0) + 0,9*temp;
    //on ajoute seulement 10% de la mesure afin de filtrer les interférences
    Serial.print("Temperature : ");Serial.println(temp);
    return temp;
}
