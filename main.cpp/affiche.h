//fichier d'entete
#ifndef AFFICHE_H
#define AFFICHE_H

#include "Arduino.h"

#define LIGNE1 0x00
#define LIGNE2 0x40

#define MESSAGE1 "    Bonjour     "
#define MESSAGE21 "Inserez carte ou"
#define MESSAGE22 "entrez code SVP "
#define MESSAGE3 "  Code correct  "
#define MESSAGE11 " Carte correcte "
#define MESSAGE4 "    Bienvenu    "
#define MESSAGE5 " Code incorrect "
#define MESSAGE6 " Reessayez SVP  "
#define MESSAGE7 "Carte non valide"
#define MESSAGE8 "Quittez la place"
#define MESSAGE9 "Code non valide "
#define MESSAGE10 " Trop lent XD  "
#define VALIDATION 1


void initAfficheur(int adress);
void effacerAfficheur (int adress);
void setEclairage(int adress,int valeur);

void activerAfficheur (int adress);
void desactiverAfficheur (int adress);

void envoyerCommande(int adress,int valeur);
void envoyerDonnee(int adress,int valeur);
void envoyerMessage(int adress,const char* maChaine,int ligne);
void blinkAfficheur(int adress,int nombre,unsigned long duree);
void shiftAfficheur(int adress, int valeur);


#endif
