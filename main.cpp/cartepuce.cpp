#include "cartepuce.h"
#include "clavier.h"
#include "Arduino.h"
#include "fonction.h" 
#include "affiche.h"
#include <string.h>
#include <Wire.h>

boolean carteDetectee(void){    //Fonction qui permet de detecter si la carte est inseree
  boolean detect=false;
  if((lireDonnee(0x21)&0x01)==0){ //On fait un filtre en utilisant le ET logique entre l'adresse et l'ecriture donnee
    detect=true;                  //pour obtenir un 0 qui doit deteceter la puce
  }
  return detect;
}


int validationCarte(void){    //Fonction qui permet de verifier si la carte rentree est correcte
  int resultat = 0, rang = 0;
  char codeValide[5]={'3','4','5','6','\0'};
  char codeCarte[5]={' ',' ',' ',' ','\0'};
  if(carteDetectee()==true){  //Si une carte est detectee, alors
    ecrireDonnee(0x21,0x06);
    Wire.beginTransmission(0x50);
    Wire.requestFrom(0x50, 5, true);
    Wire.read();
    while(Wire.available()){
      codeCarte[rang]=(char)Wire.read();
      //Serial.println(codeCarte[rang]);
      rang++;
    }
    Wire.endTransmission();
    ecrireDonnee(0x21,0x04);
    if(strcmp(codeCarte,codeValide)==0){
      resultat = 1;
    }
  }
  return resultat;
}

