# TrafficLight Library Documentation

## Introduction

La bibliothèque **TrafficLight** permet de simuler un système de feux tricolores avec des LED contrôlées via une carte Arduino. Elle est conçue pour contrôler deux feux de circulation dans une intersection, avec des options pour le logging des états des feux via le moniteur série.

---

## Fichiers de la bibliothèque

- **TrafficLight.h** : Le fichier d'en-tête définissant la classe et les méthodes de la bibliothèque.
- **TrafficLight.cpp** : Implémentation des méthodes de la classe `TrafficLight`.
- **TrafficLight.ino** : Exemple de code Arduino pour utiliser la bibliothèque.

---

## Classe TrafficLight

### Constructeur
```cpp
TrafficLight(int orangePin, int greenPin, int redPin, bool logState);
```
#### Description
- Crée un nouvel objet `TrafficLight` en spécifiant les broches de connexion pour les LED rouges, oranges, et vertes.
- Active ou désactive également les logs via le moniteur série.

### Paramètres :

- `orangePin` : Broche de connexion de la LED orange.
- `greenPin` : Broche de connexion de la LED verte.
- `redPin` : Broche de connexion de la LED rouge.
- `logState` : Active (true) ou désactive (false) les logs d'état dans le moniteur série.

### Méthodes principales

```cpp
void init()
```
##### - Initialise les pins des LED et effectue un test en allumant successivement chaque couleur.

```cpp
void red()
```
##### - Allume uniquement la LED rouge.

```cpp
void orange()
```
##### - Allume uniquement la LED orange.

```cpp
void green()
```
##### - Allume uniquement la LED verte.

```cpp
void cycle(int redTime, int orangeTime, int greenTime)
```
##### - Exécute un cycle complet de feu en allumant successivement la LED rouge, orange, puis verte, en respectant les temps définis pour chaque couleur.

##### Paramètres :
- `redTime` : Durée du feu rouge en millisecondes.
- `orangeTime` : Durée du feu orange en millisecondes.
- `greenTime` : Durée du feu vert en millisecondes.

```cpp
void runIntersectionCycle(TrafficLight feuRue1, TrafficLight feuRue2, int redTime, int orangeTime, int greenTime, int pauseTime)
```
##### Synchronise deux feux tricolores pour une intersection, en s'assurant que les deux rues ne sont pas vertes simultanément.

##### Paramètres :
- `feuRue1` : Objet TrafficLight pour la rue 1.
- `feuRue2` : Objet TrafficLight pour la rue 2.
- `redTime` : Durée du feu rouge.
- `orangeTime` : Durée du feu orange.
- `greenTime` : Durée du feu vert.
- `pauseTime` : Durée de la pause où les deux rues sont au rouge.

```cpp
void blinkOrange(unsigned long duration)
```
##### - Fait clignoter la LED orange pendant une durée spécifiée.

##### Paramètres :
- `duration` : Durée du clignotement en millisecondes.

```cpp
void allOff()
```
##### - Éteint toutes les LED.

### Méthodes privées

Les méthodes suivantes sont utilisées en interne dans la classe TrafficLight :

```cpp
void setLights(bool redState, bool orangeState, bool greenState) 
```
##### - Modifie l'état des LED rouge, orange, et verte.


```cpp
void logPhase(const char *phaseName, int remainingTime) 
```
##### - Enregistre l'état des feux dans le moniteur série.


```cpp
int computeRemainingTime()
```
##### - Calcule le temps restant avant le prochain changement de phase.


### Exemple d'utilisation

`TrafficLight.ino`
```cpp 
#include <Arduino.h>
#include "TrafficLight.h"

// Définir les pins pour les LED des deux feux tricolores
TrafficLight road1(2, 3, 4, true);  // Rue 1
TrafficLight road2(8, 9, 10, true); // Rue 2

// Durée des phases des feux
const int greenTime = 30000; // durée du feu vert
const int orangeTime = 5000; // durée du feu orange
const int redTime = 30000;   // durée du feu rouge
const int pauseTime = 3000;  // durée où les deux rues sont au rouge

void setup()
{
    Serial.begin(9600);   // Initialisation du moniteur série
    road1.init();         // Initialisation des feux
    road2.init();
}

void loop()
{
    road1.runIntersectionCycle(road1, road2, greenTime, orangeTime, redTime, pauseTime);
}

```

### Licence
Version 1.0.0 - Septembre 2024

Pour plus d'informations, consultez [www.petitvulcan.com](http://petitculcan.com).
