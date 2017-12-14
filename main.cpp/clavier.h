#ifndef CLAVIER_H
#define CLAVIER_H

#include "Arduino.h"

#define CLAVIER 0x22

boolean testClavier();
int toucheAppuyee(int adresse);
char tradClavier(int valeur);

int validationClavier(void);


#endif
