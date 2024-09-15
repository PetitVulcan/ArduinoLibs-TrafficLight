
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

#ifndef TrafficLight_h
#define TrafficLight_h

#include "Arduino.h"

class TrafficLight
{
public:
  // Constructeur: definit les pins pour les LED orange, verte, et rouge et active/desactive les logs d'etat dans le moniteur serie
  TrafficLight(int orangePin, int greenPin, int redPin, bool logState);

  // Methodes pour allumer chaque couleur
  void red();
  void orange();
  void green();

  // Methode de test de toute les couleurs du feu
  void init();

  // Methode pour etablir un cycle de feu complet (prend en parametre la duree d'allumage pour chaque couleur)
  void cycle(int redTime, int orangeTime, int greenTime);

  // Methode pour syncroniser les feux de circulation d'une intersection entre deux rues
  void runIntersectionCycle(TrafficLight feuRue1, TrafficLight feuRue2, int redTime, int orangeTime, int greenTime, int pauseTime);

  // Methode pour faire clignoter la LED orange pour une duree donnee
  void blinkOrange(unsigned long duration);

  // Methode pour eteindre toutes les LED
  void allOff();

private:
  int _redPin;                     // pin de raccordement de la led rouge du feu a l'arduino
  int _orangePin;                  // pin de raccordement de la led orange du feu a l'arduino
  int _greenPin;                   // pin de raccordement de la led verte du feu a l'arduino

  unsigned long _previousMillis;    // Temps precedemment enregistre
  unsigned long _previousLogMillis; // Temps precedemment enregistre pour le dernier log
  unsigned long _startMillis;       // Temps de debut du clignotement
  bool _logState;                   // Activation des logs de l'etat du feu dans le moniteur serie
  bool _orangeState;                // Etat actuel de la LED orange

  // Methode pour modifier la couleur a afficher
  void setLights(bool redState, bool orangeState, bool greenState);

  // Methode pour loguer l'etat des feux dans le moniteur serie
  void logPhase(const char *phaseName, int remainingTime);

  // Methode de calcul du temp ecoulé depuis le dernier log
  int computeRemainingTime();
};

#endif
