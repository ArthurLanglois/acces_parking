#ifndef CLAVIER_H
#define CLAVIER_H

#include "Arduino.h"

#define CLAVIER 0x22

boolean testClavier();              //fonction qui revoie "true" si une carte est détectee, sinon, renvoie "false"
int toucheAppuyee(int adresse);     //foncttion qui renvoie 1 si une touche est appuyee sur le clavier matriciel à l'adresse entree en paramètre
char tradClavier(int valeur);       //fonction qui renvoie le caractère correspondant à l atouche appuyée sur le  clavier matriciel à l'adresse entree en paramètre

int validationClavier(void);        //fonction qui renvoie 1 si le code au clavier est valide, sinon, renvoie 0


#endif
