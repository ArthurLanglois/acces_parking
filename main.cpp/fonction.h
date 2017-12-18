#ifndef FONCTION_H
#define FONCTION_H

#include "Arduino.h"

int lireDonnee(int adress);                     //fonction qui renvoie les données entières d'un peripherique I2C donc l'addresse est rentrée en paramètre
void ecrireDonnee(int adress,int donnee);       //fonction qui envoie des données entières (en paramètre) à un peripherique I2C donc l'addresse est passee en paramètre
void ouvrirBarriere(void);                      //fonction qui ouvre la barrière
void fermerBarriere(void);                      //fonction qui ferme la barrière
int boucleAmont(void);                          //fonction qui renvoie 1 si une voiture est détectée en amont, sinon renvoie 0
int boucleAval(void);                           //fonction qui renvoie 1 si une voiture est détectée en aval, sinon renvoie 0
int validation(void);                           //fonction de validation générale qui renvoie 1 si la carte ou le code est validée, sinon, renvoie 0
void incrementerCompteur(void);                 //fonction qui incrémente le compteur de voiture
void reinitialiserCompteur(void);               //fonction qui reinitialise le compteur de voiture

#endif
