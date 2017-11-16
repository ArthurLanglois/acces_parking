#ifndef CLAVIER_H
#define CLAVIER_H

#include "Arduino.h"


boolean testClavier(int adresse);
int toucheAppuyee(int adresse);
char tradClavier(int valeur);
int validation(void);
int validationClavier(void);
int validationCarte(void);

#endif
