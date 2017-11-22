#include "Arduino.h"
#include "clavier.h"
#include "cartepuce.h"
#include "fonction.h" 
#include "affiche.h"
#include <string.h>
#include <Wire.h>

void ecrireDonnee(int adress,int donnee){
    Wire.beginTransmission(adress);
  Wire.write(donnee);
  Wire.endTransmission();
}

int lireDonnee(int adress){
  int octet;
  Wire.beginTransmission(adress);
  Wire.requestFrom(adress, 1);
  while(Wire.available()){
    octet = Wire.read();
  }
  Wire.endTransmission();
  return octet;
}

void ouvrirBarriere(void){
  ecrireDonnee(0x20,0xfd);
}

void fermerBarriere(void){
  ecrireDonnee(0x20,0xfe);
}

int boucleAmont(void){
  if (((lireDonnee(0x20)&0x20)>>5)==1){
    return 0;
  }
  else{
    return 1;
  }
}

int boucleAval(void){
  if (((lireDonnee(0x20)&0x40)>>6)==1){
    return 0;
  }
  else{
    return 1;
  }
}

int validation(void){
  int valid = 0;
  if(testClavier(0x22)==true){
    if(validationClavier()==1){
      valid = 1;
      effacerAfficheur (0x3b);
      envoyerMessage(0x3b,MESSAGE3,LIGNE1);
      envoyerMessage(0x3b,MESSAGE4,LIGNE2);
    }
  }
  if(carteDetectee()==true){
    if(validationCarte()==1){
      valid = 1;
      effacerAfficheur (0x3b);
      envoyerMessage(0x3b,MESSAGE11,LIGNE1);
      envoyerMessage(0x3b,MESSAGE4,LIGNE2);
    }
  }
  return valid;
}

