#ifndef FONCTION_H
#define FONCTION_H

#include "Arduino.h"

int lireDonnee(int adress);
void ouvrirBarriere(void);
void fermerBarriere(void);
int boucleAmont(void);
int boucleAval(void);
int testClavier(int adresse);
int toucheAppuyee(int adresse);
int tradClavier(int valeur);
int validation(void);
int entrerCode(void);

#endif
