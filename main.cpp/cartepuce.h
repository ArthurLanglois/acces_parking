#ifndef CARTEPUCE_H
#define CARTEPUCE_H

#include "Arduino.h"

#define CARTEAPUCE 0x50

boolean carteDetectee(void);          //fonction qui revoie "true" si une carte est détectee, sinon, renvoie "false"
int validationCarte(void);            //fonction qui renvoie 1 si le code de la carte est valide, sinon, renvoie 0


#endif
