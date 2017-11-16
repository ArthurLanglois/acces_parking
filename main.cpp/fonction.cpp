#include "Arduino.h"
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

