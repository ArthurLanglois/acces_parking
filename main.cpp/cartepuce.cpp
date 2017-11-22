#include "cartepuce.h"
#include "clavier.h"
#include "Arduino.h"
#include "fonction.h" 
#include "affiche.h"
#include <string.h>
#include <Wire.h>

boolean carteDetectee(void){
  boolean detect=false;
  if((lireDonnee(0x21)&0x01)==0){
    detect=true;
  }
  return detect;
}


int validationCarte(void){
  int resultat = 0;
  char codeValide[5]={51,52,53,54,'\0'};
  char codeCarte[5]={0,0,0,0,'\0'};
  if(carteDetectee()==true){
    ecrireDonnee(0x21,0x06);
    Wire.beginTransmission(0x50);
    for(int i=0;i<4;i++){
      Wire.requestFrom(0x50, 1);
      while(Wire.available()){
        codeCarte[i]=Wire.read();
        Serial.println(codeCarte[i]);
      }
    }
    Wire.endTransmission();
    ecrireDonnee(0x21,0x04);
    if(strcmp(codeCarte,codeValide)==0){
      resultat = 1;
    }
  }
  return resultat;
}

