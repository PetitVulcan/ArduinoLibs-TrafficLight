
/*
  |\/|   | _  |
  |  |(|(|(/_ |)\/
                /
                  ___     _   _ _               _
                 / _ \___| |_(_) |_/\   /\_   _| | ___ __ _ _ __
                / /_)/ _ \ __| | __\ \ / / | | | |/ __/ _` | '_ \
               / ___/  __/ |_| | |_ \ V /| |_| | | (_| (_| | | | |
               \/    \___|\__|_|\__| \_/  \__,_|_|\___\__,_|_| |_|

              TRAFFIC LIGHT v1.0.0@09-2024 - www.petitvulcan.com
*/

#include <Arduino.h>
#include "TrafficLight.h"

// Definir les pins pour les LED et activation des logs
TrafficLight trafficLight(2, 3, 4, true);  // Rue 1


// Duree des differentes phases des cycles des feux
const int greenTime = 30000; // duree du feu vert
const int orangeTime = 5000; // duree du feu orange
const int redTime = 30000;   // duree du feu rouge
const int pauseTime = 3000;  // duree ou les deux rues sont au rouge


void setup()
{
    // Initialisation du moniteur serie
    Serial.begin(9600);

    // Initialisation et test du feux Tricolor
    trafficLight.init();
}

void loop()
{
    // Démarrage de la fonction clignotement du feu
    trafficLight.blinkOrange(10000);
}

