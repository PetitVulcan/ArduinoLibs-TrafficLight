
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

#include "TrafficLight.h"

TrafficLight::TrafficLight(int orangePin, int greenPin, int redPin, bool logState)
{
  _redPin = redPin;
  _orangePin = orangePin;
  _greenPin = greenPin;
  _logState = logState;

  pinMode(_redPin, OUTPUT);
  pinMode(_orangePin, OUTPUT);
  pinMode(_greenPin, OUTPUT);

  allOff(); // Éteindre toutes les LEDs
  _previousMillis = 0;
  _previousLogMillis = 0;
  _orangeState = false;
}

// Fonction permettant l'allumage du feu rouge
void TrafficLight::red()
{
  setLights(true, false, false);
}

// Fonction permettant l'allumage du feu orange
void TrafficLight::orange()
{
  setLights(false, true, false);
}

// Fonction permettant l'allumage du feu vert
void TrafficLight::green()
{
  setLights(false, false, true);
}

// Fonction executant un cycle complet du feu de circulation
void TrafficLight::cycle(int redTime, int orangeTime, int greenTime)
{
  unsigned long currentMillis = millis();
  static int _currentStep = 0;
  

  switch (_currentStep)
  {
  case 0:
    green();
    if (currentMillis - _previousLogMillis >= 1000 && _logState)
    {
      logPhase("Phase 0: Feu Vert", greenTime / 1000 - computeRemainingTime());
      _previousLogMillis = currentMillis;
    }
    if (currentMillis - _previousMillis >= greenTime)
    {
      _previousMillis = currentMillis;
      _currentStep = 1;
    }
    break;

  case 1:
    orange();
    if (currentMillis - _previousLogMillis >= 1000 && _logState)
    {
      logPhase("Phase 1: Feu Orange", greenTime / 1000 - computeRemainingTime());
      _previousLogMillis = currentMillis;
    }
    if (currentMillis - _previousMillis >= orangeTime)
    {
      _previousMillis = currentMillis;
      _currentStep = 2;
    }
    break;

  case 2:
    red();
    if (currentMillis - _previousLogMillis >= 1000 && _logState)
    {
      logPhase("Phase 2: Feu Rouge", greenTime / 1000 - computeRemainingTime());
      _previousLogMillis = currentMillis;
    }
    if (currentMillis - _previousMillis >= redTime)
    {
      _previousMillis = currentMillis;
      _currentStep = 0;
    }
    break;
  }
}

// Fonction executant le fonctionnement syncronisé des feux d'intersection de deux rues
void TrafficLight::runIntersectionCycle(TrafficLight road1, TrafficLight road2, int redTime, int orangeTime, int greenTime, int pauseTime)
{
  unsigned long currentMillis = millis();
  static int _currentStep = 0;

  switch (_currentStep)
  {
  case 0: // Rue 1: Vert, Rue 2: Rouge
    road1.green();
    road2.red();

    if (currentMillis - _previousLogMillis >= 1000 && _logState)
    {
      logPhase("Phase 0: Rue 1 Vert, Rue 2 Rouge", greenTime / 1000 - computeRemainingTime());
      _previousLogMillis = currentMillis;
    }
    if (currentMillis - _previousMillis >= greenTime)
    {
      _previousMillis = currentMillis;
      _currentStep = 1;
    }
    break;

  case 1: // Rue 1: Orange, Rue 2: Rouge
    road1.orange();
    road2.red();

    if (currentMillis - _previousLogMillis >= 1000 && _logState)
    {
      logPhase("Phase 1: Rue 1 Orange, Rue 2 Rouge", orangeTime / 1000 - computeRemainingTime());
      _previousLogMillis = currentMillis;
    }
    if (currentMillis - _previousMillis >= orangeTime)
    {
      _previousMillis = currentMillis;
      _currentStep = 2;
    }
    break;

  case 2: // Les deux rues au rouge
    road1.red();
    road2.red();

    if (currentMillis - _previousLogMillis >= 1000 && _logState)
    {
      logPhase("Phase 2: Les deux rues Rouge", pauseTime / 1000 - computeRemainingTime());
      _previousLogMillis = currentMillis;
    }
    if (currentMillis - _previousMillis >= pauseTime)
    {
      _previousMillis = currentMillis;
      _currentStep = 3;
    }
    break;

  case 3: // Rue 1: Rouge, Rue 2: Vert
    road1.red();
    road2.green();

    if (currentMillis - _previousLogMillis >= 1000 && _logState)
    {
      logPhase("Phase 3: Rue 1 Rouge, Rue 2 Vert", greenTime / 1000 - computeRemainingTime());
      _previousLogMillis = currentMillis;
    }
    if (currentMillis - _previousMillis >= greenTime)
    {
      _previousMillis = currentMillis;
      _currentStep = 4;
    }
    break;

  case 4: // Rue 1: Rouge, Rue 2: Orange
    road1.red();
    road2.orange();

    if (currentMillis - _previousLogMillis >= 1000 && _logState)
    {
      logPhase("Phase 4: Rue 1 Rouge, Rue 2 Orange", orangeTime / 1000 - computeRemainingTime());
      _previousLogMillis = currentMillis;
    }

    if (currentMillis - _previousMillis >= orangeTime)
    {
      _previousMillis = currentMillis;
      _currentStep = 5;
    }
    break;

  case 5: // Les deux rues au rouge
    road1.red();
    road2.red();

    if (currentMillis - _previousLogMillis >= 1000 && _logState)
    {
      logPhase("Phase 5: Les deux rues Rouge", pauseTime / 1000 - computeRemainingTime());
      _previousLogMillis = currentMillis;
    }
    if (currentMillis - _previousMillis >= pauseTime)
    {
      _previousMillis = currentMillis;
      _currentStep = 0;
    }
    break;
  }
}

void TrafficLight::init()
{
  setLights(false, false, true);
  delay(500);
  setLights(false, true, false);
  delay(500);
  setLights(true, false, false);
  delay(500);
}

// Fonction utilitaire pour afficher l'état et le temps restant dans le moniteur série
void TrafficLight::logPhase(const char *phaseName, int remainingTime)
{
  Serial.print(phaseName);
  Serial.print(" - Restant : ");
  Serial.print(remainingTime);
  Serial.println(" sec");
}

void TrafficLight::blinkOrange(unsigned long duration)
{

  unsigned long currentMillis = millis();

  // Initialisation de la période de clignotement
  if (_startMillis == 0)
  {
    _startMillis = currentMillis;
  }

  // Clignotement tant que la durée n'est pas atteinte
  if (currentMillis - _startMillis < duration)
  {
    if (currentMillis - _previousMillis >= 1000)
    { 
      // Changer l'état toutes les secondes
      _previousMillis = currentMillis;
      _orangeState = !_orangeState; // Inverser l'état
      digitalWrite(_orangePin, _orangeState ? HIGH : LOW);
    }
  }
  else
  {
    // Éteindre la LED après la durée
    digitalWrite(_orangePin, LOW);
    _startMillis = 0; // Réinitialiser pour le prochain clignotement
  }
}
// Methode de calcul du temp ecoulé depuis le dernier log
int TrafficLight::computeRemainingTime()
{
  return (millis() - _previousMillis) / 1000;
}

void TrafficLight::setLights(bool redState, bool orangeState, bool greenState)
{
  digitalWrite(_redPin, redState ? HIGH : LOW);
  digitalWrite(_orangePin, orangeState ? HIGH : LOW);
  digitalWrite(_greenPin, greenState ? HIGH : LOW);
}

void TrafficLight::allOff()
{
  setLights(false, false, false);
}