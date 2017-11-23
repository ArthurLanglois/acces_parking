#include "Arduino.h"
#include "clavier.h"
#include "cartepuce.h"
#include "fonction.h" 
#include "affiche.h"
#include <string.h>
#include <Wire.h>

void ecrireDonnee(int adress,int donnee){   //Fonction qui permet d'envoyer une donnee a l'adresse rentree en parametre
    Wire.beginTransmission(adress);
  Wire.write(donnee);
  Wire.endTransmission();
}

int lireDonnee(int adress){                 //Fonction qui permet de lire une donnee ciblee à une adresse rentree en parametre
  int octet;
  Wire.beginTransmission(adress);
  Wire.requestFrom(adress, 1);
  while(Wire.available()){
    octet = Wire.read();
  }
  Wire.endTransmission();
  return octet;
}

void ouvrirBarriere(void){                  //Fonction qui ouvre la barriere avec l'adresse de la barriere 0x20 et
  ecrireDonnee(0x20,0xfd);                  //0xfd correspond a une demande de montee suivant la doc technique
}

void fermerBarriere(void){                  //Focntion fermante de la barriere
  ecrireDonnee(0x20,0xfe);                  //0xfe correspond a une demande de descente
}

int boucleAmont(void){                      //Fonction qui detecte si il y a presence d'une voiture sur la boucle amont
  if (((lireDonnee(0x20)&0x20)>>5)==1){     //filtre qui permet d'isoler le bit d'état de la boucle amont
    return 0;
  }
  else{
    return 1;
  }
}

int boucleAval(void){                       //Fonction qui detecte si il y a presence de vehicule sur la boucle aval
  if (((lireDonnee(0x20)&0x40)>>6)==1){     //filtre qui permet d'isoler le bit d'etat de la boucle aval
    return 0;
  }
  else{
    return 1;
  }
}

int validation(void){                       //Fonction qui permet de dire si le code du clavier est correct et si le code la
  int valid = 0;                            //carte est correct
  if(testClavier(0x22)==true){              //Clavier bon ou pas
    if(validationClavier()==1){
      valid = 1;
      effacerAfficheur (0x3b);              //Avec messages s'affichant sur l'afficheur LCD
      envoyerMessage(0x3b,MESSAGE3,LIGNE1);
      envoyerMessage(0x3b,MESSAGE4,LIGNE2);
    }
  }
  if(carteDetectee()==true){                //Carte rentree ou non
    if(validationCarte()==1){
      valid = 1;
      effacerAfficheur (0x3b);
      envoyerMessage(0x3b,MESSAGE11,LIGNE1);//Messages correspondant
      envoyerMessage(0x3b,MESSAGE4,LIGNE2);
    }
  }
  return valid;
}

