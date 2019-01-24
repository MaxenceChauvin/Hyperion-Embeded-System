 // include

 void setup(){ // boucle d'initiatlisation du programme
    Serial.begin(9600);
 }

void loop(){ // boucle loop
    temp = getTemp();
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
