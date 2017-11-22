#ifndef FONCTION_H
#define FONCTION_H

#include "Arduino.h"

int lireDonnee(int adress);
void ecrireDonnee(int adress,int donnee);
void ouvrirBarriere(void);
void fermerBarriere(void);
int boucleAmont(void);
int boucleAval(void);
int validation(void);

#endif
